#ifndef GEMINI_MsgQueue_INCLUDE
#define GEMINI_MsgQueue_INCLUDE
#include "MsgData.h"

#include <queue>
#include <mutex>

namespace gemini {

class MsgQueue : public noncopyable
{
	typedef std::queue<MsgData> value_type;
	typedef std::mutex	mutex_type;

public:
	MsgQueue();
	~MsgQueue();

	/**
	* @brief �����Ϣ���е���Ϣ����
	*
	* @return ������Ϣ���ͣ��μ�MsgTypeö������
	*
	* @see MsgType
	*
	*/
	MsgData::T_TYPE getMsgType() const { return _msgType; }

	/**
	* @brief ����Ϣ���д�����Ϣ
	* @param [in] msg ��������Ϣ
	*
	*/
	void push(const MsgData& msg);

	/**
	* @brief ����Ϣ�����л�ȡ��Ϣ
	* @param [in] bPop ����Ϣ�����е�����Ϣ��ʾ
	*
	* @return ������Ϣ�������������Ϣ
	* @retval XQS_NULL ��Ϣ������û����Ϣ
	* @retval XQSMsgData::SPtr  �������Ϣ
	*/
	MsgData get(Boolean bPop = false);

	/**
	* @brief ������Ϣ�������������Ϣ
	*/
	void pop();

private:
	MsgData::T_TYPE _msgType;		///< ��Ϣ����
	value_type _value;		///< ��Ϣ����
	mutex_type _mutex;
};

}

#endif // GEMINI_MsgQueue_INCLUDE
