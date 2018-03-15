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
	* @brief 获得消息队列的消息类型
	*
	* @return 返回消息类型，参见MsgType枚举类型
	*
	* @see MsgType
	*
	*/
	MsgData::T_TYPE getMsgType() const { return _msgType; }

	/**
	* @brief 向消息队列存入消息
	* @param [in] msg 需存入的消息
	*
	*/
	void push(const MsgData& msg);

	/**
	* @brief 从消息队列中获取消息
	* @param [in] bPop 从消息队列中弹出消息标示
	*
	* @return 返回消息队列中最早的消息
	* @retval XQS_NULL 消息队列中没有消息
	* @retval XQSMsgData::SPtr  最早的消息
	*/
	MsgData get(Boolean bPop = false);

	/**
	* @brief 弹出消息队列中最早的消息
	*/
	void pop();

private:
	MsgData::T_TYPE _msgType;		///< 消息类型
	value_type _value;		///< 消息队列
	mutex_type _mutex;
};

}

#endif // GEMINI_MsgQueue_INCLUDE
