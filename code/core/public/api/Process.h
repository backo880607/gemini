#ifndef GEMINI_Process_INCLUDE
#define GEMINI_Process_INCLUDE
#include "MsgData.h"

#include <mutex>
#include <condition_variable>

namespace boost {
	class thread;
namespace interprocess {
	class shared_memory_object;
	class mapped_region;
}
}
namespace gemini {

class ProcessImpl;
class ProcessBuffer;
class CORE_API Process final
{
	struct SharedMemory {
		ProcessBuffer* _buffer;
		String _sharedMemName;
		typedef std::shared_ptr<boost::interprocess::shared_memory_object> smem_ptr;
		smem_ptr _smem;
		typedef std::shared_ptr<boost::interprocess::mapped_region> region_ptr;
		region_ptr _region;

		// 共享内存应由主进程创建，id应为创建的子进程id，子进程只打开共享内存
		Boolean open(Long id = 0);
		void close();
	};

	typedef std::vector<String> Args;
	Process(std::shared_ptr<ProcessImpl> impl);
public:
	Process();
	~Process();

	static Long currentId();
	static Process launch(const String& command);
	static Process launch(const String& command, const Args& args);

	Boolean valid() const { return _impl != nullptr; }

	Long id() const;
	Boolean running() const;
	Int wait() const;
	void kill();
private:
	std::shared_ptr<ProcessImpl> _impl;
};

class CORE_API ProcessPool : public noncopyable
{
	struct Config {
		Int size;
		String path;
	};
public:
	ProcessPool();
	~ProcessPool();

	const Config& getConfig() const { return _config; }

	Process create();
	void destory(Process proc);

private:
	void readConfig();
	void startHeartBeat();
	Process createImpl();

private:
	Config _config;
	std::vector<Process> _processes;
	std::vector<Process> _freeNodes;

	typedef std::shared_ptr<boost::thread> thread_type;
	thread_type _threadHeartBeat;

	std::mutex _mutex;
	std::condition_variable _cond;
};

}
#endif // GEMINI_Process_INCLUDE
