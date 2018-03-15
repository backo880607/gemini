#ifndef GEMINI_NETWORK_Socket_INCLUDE
#define GEMINI_NETWORK_Socket_INCLUDE
#include "../public/NetworkExport.h"
#include "../../core/public/api/MsgData.h"

#include <boost/asio.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/thread.hpp>
#include <deque>

namespace gemini {

class TCPConnection;
class Socket
{
	Socket(const Socket&) = delete;
	Socket& operator= (const Socket&) = delete;
public:
	typedef boost::asio::ip::tcp::socket socket_type;
	typedef boost::asio::io_service service_type;
	typedef std::deque<MsgData> msg_queue;

	/**
	* @brief 连接状态
	*/
	enum class Status {
		S_OffLine, 		///< 已连接但未登录
		S_OnLine, 		///< 已连接并已登录
		S_Opering,  	///< 正在进行网络同步操作
		S_Termination 	///< 未连接
	};

	Socket(service_type& ios, TCPConnection* conn, UInt hbTimeout);
	~Socket();

	socket_type& getSocket() { return _socket; }
	service_type& getService() { return _socket.get_io_service(); }

	/** 
	* @brief 异步写入数据消息
	* @param [in] pData    数据首地址
	* @param [in] size     写入数据大小,Byte为单位
	* @param [in] msgType  消息类型
	* @param [in] priority 消息优先级
	* @param [in] dataType 数据的序列化类型
	* @param [in] cpt      压缩类型
	*
	* @return 返回是否异步写入成功
	*        -<em>false</em> 异步写入失败
	*        -<em>true</em> 异步写入成功
	*/
	Boolean asyncWrite(const void* pData, std::size_t size, UChar msgType = MSG_TYPE_NORMAL, UChar funcID = 0,
		UShort priority = 0, DataType dataType = DataType::DT_MEMSEQ, CompressType cpt = CompressType::CPT_ZLIB) {
		MsgData msg;
		msg.setType(msgType);
		msg.setFunctionID(funcID);
		msg.setPriority((UChar)priority);
		msg.setDataType(dataType);
		msg.setCompressType(cpt);
		msg.setCompressType(CompressType::CPT_NONE);
		msg.setEncryption(Encryption::Encry_AES);
		if (!msg.format(pData, size))
			return false;
		return asyncWrite(msg);
	}

	/**
	 * 异步写入消息
	 * @param [in] msg 消息数据
	 * @return 返回是否异步写入成功
	*        -<em>false</em> 异步写入失败
	*        -<em>true</em> 异步写入成功
	 */
	Boolean asyncWrite(MsgData& msg);

	/**
	 * @brief 启用socket连接。
	 * 
	 * @return Boolean 
	 */
	Boolean start();

	/**
	 * @brief 停止socket连接
	 * 
	 */
	void stop();

protected:
	boost::asio::io_service::strand& getStrand() { return _strand; }
	virtual void do_read();

	std::shared_ptr<Socket> shared_from_this() {
		std::shared_ptr<Socket> p(weak_help);
		return p;
	}

	template <class T>
	std::shared_ptr<T> ddddddd() {
		std::shared_ptr<T> p = std::static_pointer_cast<T>(shared_from_this());
		return p;
	}

private:
	Boolean async_read_head();
	Boolean async_read_body();
	void async_handle_read_head(const boost::system::error_code& err, std::size_t len);
	void async_handle_read_body(const boost::system::error_code& err, std::size_t len);

	Boolean write(MsgData msg);
	Boolean writeImpl(const Char* data, UInt size);

	void do_write(MsgData msg);
	void async_handle_write(const boost::system::error_code& err, UInt pos);

	/**
	 * @brief 心跳回调函数
	 */
	void checkHeartBeat(const boost::system::error_code& err);

	/** 
	* @brief TCP连接错误处理
	*
	* @return 是否已中断连接
	* @retval false 连接未中断
	* @retval true  中断连接
	*
	*/
	Boolean proError(const boost::system::error_code& err);

private:
	Status _status; 	///< socket状态
	UInt _heartbeatTimeout;	///< ������ʱʱ�䣬��λΪ��
	boost::asio::deadline_timer _heartbeat;	///< ������ʱ��
	socket_type _socket;
	boost::asio::io_service::strand _strand;

	MsgData _readMsg;		///< 读取消息缓冲区
	msg_queue _writeMsg;	///< 写入消息队列

	friend class TCPConnection;
	TCPConnection* _conn;		///< 会话连接
	mutable std::weak_ptr<Socket> weak_help;	///< 用于boost的shared_from_this函数
};

}
#endif // GEMINI_NETWORK_Socket_INCLUDE
