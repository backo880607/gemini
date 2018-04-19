#include "../include/Socket.h"
#include "../public/tcp/TCPConnection.h"
#include "../public/NetworkError.h"
#include "../../core/public/message/Log.h"
#include "../../core/public/tools/StringUtil.h"

using namespace boost::asio;
namespace gemini {

Socket::Socket(service_type& ios, TCPConnection* conn, UInt hbTimeout)
	: _strand(ios)
	, _heartbeatTimeout(hbTimeout)
	//, _msgIDMax(0)
	, _heartbeat(ios)
	, _socket(ios)
	, _conn(conn)
{

}

Socket::~Socket()
{

}

Boolean Socket::start()
{
	boost::system::error_code set_option_err;
	boost::asio::ip::tcp::no_delay no_delay(true);
	_socket.set_option(no_delay, set_option_err);
	if (set_option_err) {
		_status = Status::S_Termination;
		return false;
	}

	do_read();
	return true;
}

void Socket::stop()
{
	_heartbeat.cancel();
	boost::system::error_code ignored_ec;
	_socket.shutdown(ip::tcp::socket::shutdown_both, ignored_ec);
	_socket.close(ignored_ec);
}

void Socket::do_read()
{
	async_read_head();
	_heartbeat.async_wait(boost::bind(&Socket::checkHeartBeat, shared_from_this(), boost::asio::placeholders::error));
}

Boolean Socket::async_read_head()
{
	if (_status == Status::S_Termination)
		return false;

	_heartbeat.expires_from_now(boost::posix_time::seconds(_heartbeatTimeout));
	_readMsg.reset();
	Char* buf = _readMsg.getHeadBuffer();
	UInt headSize = _readMsg.getHeadSize();
	async_read(_socket, buffer(buf, headSize), transfer_all(),
		_strand.wrap(boost::bind(&Socket::async_handle_read_head, shared_from_this(), 
			placeholders::error, placeholders::bytes_transferred)));

	return true;
}

Boolean Socket::async_read_body()
{
	if (_status == Status::S_Termination)
		return false;

	_heartbeat.expires_from_now(boost::posix_time::seconds(_heartbeatTimeout));
	MsgData::mutable_buffer buf = _readMsg.prepare();
 	async_read(_socket, buffer(buf.data_, buf.size_), transfer_all(),
		_strand.wrap(boost::bind(&Socket::async_handle_read_body, shared_from_this(),
			placeholders::error, placeholders::bytes_transferred)));
	return true;
}


void Socket::async_handle_read_head( const boost::system::error_code& err, std::size_t len )
{
	if (err && proError(err))
		return;

	// 消息头读取完毕，准备消息体缓冲区
	_readMsg.networkToHost();
	async_read_body();
}

void Socket::async_handle_read_body( const boost::system::error_code& err, std::size_t len )
{
	if (err && proError(err))
		return;

	// 数据未读取完，继续读取数据
	if (!_readMsg.commit(len)) {
		async_read_body();
		return;
	}

	try {
		MsgData msg = _readMsg;
		if (msg.parse()) {
			//msg.setSessionID(m_session->GetID());
			_conn->execute(msg);
		}
	} catch (NetworkException& exc) {
		LOG_ERROR.log(exc);
	} catch (Exception& exc) {

	} catch (std::exception& exc) {
		LOG_ERROR.log(exc);
	} catch (...) {
		LOG_ERROR.log("未知异常");
	}
	async_read_head();
}

Boolean Socket::write(MsgData msg)
{
	if (_status == Status::S_Termination)
		return false;

	// 写入头部
	if (!writeImpl(msg.getHeadBuffer(), msg.getHeadSize()))
		return false;

	// 写入消息体
	UInt pos = 0;
	const Char* data = nullptr;
	UInt size = 0;
	while (msg.step(pos, data, size)) {
		if (!writeImpl(data, size)) {
			return false;
		}

		pos += size;
	}

	return true;
}

Boolean Socket::writeImpl(const Char* data, UInt size)
{
	boost::system::error_code err;
	boost::asio::write(_socket, buffer(data, size), transfer_all(), err);
	return true;
}

Boolean Socket::asyncWrite(MsgData& msg)
{
	if (_status == Status::S_Termination)
		return false;

	/*if (msg.getMsgID() == 0)
		msg.setMsgID(GetMsgID());*/

	msg.hostToNetwork();
	_strand.post(_strand.wrap(boost::bind(&Socket::do_write, shared_from_this(), msg)));
	return true;
}

void Socket::do_write(MsgData msg)
{
	Boolean write_in_progress = !_writeMsg.empty();
    _writeMsg.push_back(msg);
    if (!write_in_progress) {
    	_heartbeat.expires_from_now(boost::posix_time::seconds(_heartbeatTimeout));
      	async_write(_socket, buffer(_writeMsg.front().getHeadBuffer(),
            _writeMsg.front().getHeadSize()),
          	_strand.wrap(boost::bind(&Socket::async_handle_write, shared_from_this(),
            boost::asio::placeholders::error, 0)));
    }
}

void Socket::async_handle_write(const boost::system::error_code& err, UInt pos)
{
	if (err && proError(err)) {
		return;
	}

	const Char* data = nullptr;
	UInt size = 0;
	if (_writeMsg.front().step(pos, data, size)) {
		_heartbeat.expires_from_now(boost::posix_time::seconds(_heartbeatTimeout));
		async_write(_socket, buffer(data, size),
           	_strand.wrap(boost::bind(&Socket::async_handle_write, shared_from_this(),
           	boost::asio::placeholders::error, pos+size)));
	} else {
		_writeMsg.pop_front();
		if (!_writeMsg.empty()) {
			_heartbeat.expires_from_now(boost::posix_time::seconds(_heartbeatTimeout));
	        async_write(_socket, buffer(_writeMsg.front().getHeadBuffer(),
            	_writeMsg.front().getHeadSize()),
          		_strand.wrap(boost::bind(&Socket::async_handle_write, shared_from_this(),
            	boost::asio::placeholders::error, 0)));
	    }
	}
}

void Socket::checkHeartBeat(const boost::system::error_code& err)
{
	// TCP连接已终止或取消了心跳定时器
	if (_status == Status::S_Termination)
		return;

	// 真正的等待超时
	if (_heartbeat.expires_at() <= deadline_timer::traits_type::now()) {
    	if (_conn->proHeartBeatTimeout()) {
			_conn->close();
    		_heartbeat.expires_at(boost::posix_time::pos_infin);// 定时器 设定为永不超时/不可用状态  
    	}
    }
  
    // 如果不是真正的超时，定是其操作已成功/用户重新设置了定时器
    // 重新启动定时器
	_heartbeat.async_wait(boost::bind(&Socket::checkHeartBeat, shared_from_this(), boost::asio::placeholders::error));
}

Boolean Socket::proError(const boost::system::error_code& err)
{
	if (!err)
		return false;
	
	using namespace boost::asio;
	switch (err.value()) {
	case error::eof:
	default:
		{
			_status = Status::S_OffLine;
			_conn->close();
		}
		return true;
	}

	return false;
}

}