#ifndef GEMINI_MsgTransmit_INCLUDE
#define GEMINI_MsgTransmit_INCLUDE
#include "MsgQueue.h"
#include <thread>

namespace gemini {

class MsgTransmit
{
	typedef std::shared_ptr<std::thread> thread_type;
public:
	MsgTransmit(MsgQueue& request, MsgQueue& response);
	~MsgTransmit();

	/**
	* @brief ���������̺߳���Ӧ�߳̽�����Ϣ����
	*/
	void start();

	/**
	* @brief ֹͣ�����̺߳���Ӧ�̵߳���Ϣ����
	*/
	void stop();

private:
	static void proRequest(MsgTransmit* transmit);
	static void proResponse(MsgTransmit* transmit);

private:
	MsgQueue& _request;				///< �������
	MsgQueue& _response;			///< Ӧ�����
	thread_type _threadRequest;		///< �����߳�
	thread_type _threadResponse;		///< ��Ӧ�߳�
};

}
#endif // GEMINI_MsgTransmit_INCLUDE
