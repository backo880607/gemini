#ifndef GEMINI_NETWORK_TCPClientConnection_INCLUDE
#define GEMINI_NETWORK_TCPClientConnection_INCLUDE
#include "TCPConnection.h"

namespace gemini {

class GEMINI_NETWORK_API TCPClientConnection : public TCPConnection
{
	/**
	* @brief TCP连接的配置信息结构体
	*/
	struct ClientConfig {
		String ip;					///< 服务器IP
		Int port;					///< 服务器端口号
		Int connectionTimeout;		///< 连接超时
		Int readTimeout;			///< 接收TCP数据超时
		Int writeTimeout;			///< 发送TCP数据超时
	};

public:
	TCPClientConnection();
	virtual ~TCPClientConnection();

	/**
	* @brief 登录TCP服务器
	* @param [in] user     用户名
	* @param [in] password 登录密码
	*
	* @return 返回是否成功登录
	* @retval false 登录失败
	* @retval true  登录成功
	*
	* @note 登录失败信息写入log
	*/
	Boolean login(const String& user, const String& password);
	/**
	* @brief 登录TCP服务器
	* @param [in] user      用户名
	* @param [in] password  登录密码
	* @param [out] errMsg   返回登录失败信息
	*
	* @return 返回是否成功登录
	* @retval false 登录失败
	* @retval true  登录成功
	*
	* @note 登录失败信息写入log
	*/
	Boolean login(const String& user, const String& password, String& errMsg);
	/**
	* @brief 退出TCP服务器
	*
	* @return 返回是否成功登出
	* @retval false 登出失败
	* @retval true  登出成功
	*
	* @note 退出TCP服务器，不会中断TCP连接
	*/
	Boolean logout();

protected:
	virtual std::shared_ptr<Socket> createSocket(boost::asio::io_service& ios);
	virtual Boolean execute(const MsgData& msg);
	virtual void close();
	virtual Boolean proHeartBeatTimeout();

private:
	ClientConfig _clientConfig;	///< TCP连接配置信息
};

}
#endif // GEMINI_NETWORK_TCPClientConnection_INCLUDE
