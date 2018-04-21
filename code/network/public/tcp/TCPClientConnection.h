#ifndef GEMINI_NETWORK_TCPClientConnection_INCLUDE
#define GEMINI_NETWORK_TCPClientConnection_INCLUDE
#include "TCPConnection.h"

namespace gemini {

class GEMINI_NETWORK_API TCPClientConnection : public TCPConnection
{
	/**
	* @brief TCP���ӵ�������Ϣ�ṹ��
	*/
	struct ClientConfig {
		String ip;					///< ������IP
		Int port;					///< �������˿ں�
		Int connectionTimeout;		///< ���ӳ�ʱ
		Int readTimeout;			///< ����TCP���ݳ�ʱ
		Int writeTimeout;			///< ����TCP���ݳ�ʱ
	};

public:
	TCPClientConnection();
	virtual ~TCPClientConnection();

	/**
	* @brief ��¼TCP������
	* @param [in] user     �û���
	* @param [in] password ��¼����
	*
	* @return �����Ƿ�ɹ���¼
	* @retval false ��¼ʧ��
	* @retval true  ��¼�ɹ�
	*
	* @note ��¼ʧ����Ϣд��log
	*/
	Boolean login(const String& user, const String& password);
	/**
	* @brief ��¼TCP������
	* @param [in] user      �û���
	* @param [in] password  ��¼����
	* @param [out] errMsg   ���ص�¼ʧ����Ϣ
	*
	* @return �����Ƿ�ɹ���¼
	* @retval false ��¼ʧ��
	* @retval true  ��¼�ɹ�
	*
	* @note ��¼ʧ����Ϣд��log
	*/
	Boolean login(const String& user, const String& password, String& errMsg);
	/**
	* @brief �˳�TCP������
	*
	* @return �����Ƿ�ɹ��ǳ�
	* @retval false �ǳ�ʧ��
	* @retval true  �ǳ��ɹ�
	*
	* @note �˳�TCP�������������ж�TCP����
	*/
	Boolean logout();

protected:
	virtual std::shared_ptr<Socket> createSocket(boost::asio::io_service& ios);
	virtual Boolean execute(const MsgData& msg);
	virtual void close();
	virtual Boolean proHeartBeatTimeout();

private:
	ClientConfig _clientConfig;	///< TCP����������Ϣ
};

}
#endif // GEMINI_NETWORK_TCPClientConnection_INCLUDE
