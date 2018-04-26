#include "api/Process.h"
#include "message/Exception.h"

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/thread.hpp>

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include "api/Process_WIN32.h"
#elif GEMINI_OS == GEMINI_OS_LINUX
#include "api/Process_UNIX.h"
#endif


namespace gemini {

struct ProcessBuffer {
	boost::interprocess::interprocess_mutex    mutex;
	boost::interprocess::interprocess_condition  cond_empty;
	boost::interprocess::interprocess_condition  cond_full;
	Boolean message_in;
	Boolean bHeader;
	Char  datas[MsgData::s_maxBlock];

	ProcessBuffer() : message_in(false) {}
	~ProcessBuffer() {}
};

Boolean Process::SharedMemory::open(Long id /* = 0 */)
{
	using namespace boost::interprocess;
	String strSharedMemName = "Process_Shared_";
	//strSharedMemName += m_bServer ? "Server_" : "Client_";
	try
	{
		if (id > 0) {
			strSharedMemName += StringUtil::format(id);
			_smem = smem_ptr(new shared_memory_object(create_only, strSharedMemName.c_str(), read_write));
			_smem->truncate(sizeof(ProcessBuffer));
			_region = region_ptr(new mapped_region(*_smem.get(), read_write));
			void* addr = _region->get_address();
			std::memset(addr, 1, _region->get_size());
			_buffer = new (addr)ProcessBuffer();
		} else {
			strSharedMemName += StringUtil::format(Process::currentId());
			_smem = smem_ptr(new shared_memory_object(open_only, strSharedMemName.c_str(), read_write));
			_region = region_ptr(new mapped_region(*_smem.get(), read_write));
			void* addr = _region->get_address();
			_buffer = static_cast<ProcessBuffer*>(addr);
		}
	} catch (interprocess_exception& ex) {
		THROW(Exception, ex.what());
		return false;
	}

	_sharedMemName = strSharedMemName;
	return true;
}

void Process::SharedMemory::close()
{
	boost::interprocess::shared_memory_object::remove(_sharedMemName.c_str());
	_sharedMemName.clear();
	_buffer = nullptr;
	_region.reset();
	_smem.reset();
}

Process::Process(std::shared_ptr<ProcessImpl> impl)
	: _impl(impl)
{

}

Process::Process()
{

}

Process::~Process()
{

}

Long Process::currentId()
{
	return ProcessImpl::currentId();
}

Process Process::launch(const String& command)
{
	return launch(command, {});
}

Process Process::launch(const String& command, const Args& args)
{
	return ProcessImpl::launch(command, args);
}

Long Process::id() const
{
	return _impl->id();
}

Boolean Process::running() const
{
	return _impl ? _impl->running() : false;
}

Int Process::wait() const
{
	return _impl->wait();
}

void Process::kill()
{
	_impl->killImpl();
}

ProcessPool::ProcessPool()
{
	readConfig();
	if (_config.size <= 0) {
		_config.size = 4;
	}

	_freeNodes.resize(_config.size);
}

ProcessPool::~ProcessPool()
{
	_cond.notify_all();
	if (_threadHeartBeat) {
		_threadHeartBeat->interrupt();
		_threadHeartBeat->join();
		_threadHeartBeat = nullptr;
	}

	std::unique_lock<std::mutex> locker(_mutex);
	for (std::vector<Process>::iterator iter = _processes.begin();
		iter != _processes.end(); ++iter)
	{
		(*iter).kill();
	}
	_processes.clear();
}

Process ProcessPool::create()
{
	std::unique_lock<std::mutex> locker(_mutex);
	if (_freeNodes.empty())
		_cond.wait(locker);

	if (!_freeNodes.empty()) {
		Process process = _freeNodes.back();
		if (!process.valid()) {
			process = createImpl();
			_freeNodes.pop_back();
			return process;
		}

		_freeNodes.pop_back();
		return process;
	}
	return Process();
}

Process ProcessPool::createImpl()
{
	Process process = Process::launch(_config.path);
	if (!process.valid())
		return Process();

	std::unique_lock<std::mutex> locker(_mutex);
	_processes.push_back(process);
	return process;
}

void ProcessPool::destory(Process proc)
{
}

void ProcessPool::readConfig()
{
}

void ProcessPool::startHeartBeat()
{
	using namespace boost::interprocess;
	_threadHeartBeat = thread_type(new boost::thread([&]() {
		try {
			do {
				boost::this_thread::interruption_point();

				_mutex.lock();
				for (std::vector<Process>::iterator iter = _processes.begin();
					iter != _processes.end(); )
				{
					Process proc = *iter;
					if (!proc.valid()) {
						iter = _processes.erase(iter);
					}
					else if (!proc.running()) {
						++iter;
					}
					/*else if (ptr->GetAccessTime().IsElapsed(m_autoTime)) {
						// �������ݵ��ļ�������ֹ���̡�
						YKSmartPtr<YKCMDSaveSQL> saveCmd(true);
						ptr->Write(saveCmd);
						ptr->Terminate();
						ptr->Close();
						++iter;
					}*/
					else {
						++iter;
					}
				}
				_mutex.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(5));
			} while (true);
		}
		catch (interprocess_exception& err) {
			THROW(Exception, err.what());
		}
	}));
}

}