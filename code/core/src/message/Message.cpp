#include "message/Message.h"
#include "cache/Cache.h"

namespace gemini {

DECLARE_CLASS_IMPL(Message, EntityObject)

Message::SPtr Message::createImpl(Type type, log_info& msg, Boolean bTemp /* = false */)
{
	Message::SPtr result = bTemp ? Cache::createTemp(Message::getClassStatic()) : Cache::create(Message::getClassStatic(), 0);
	result->_type = type;
	result->_name = msg.getName();
	result->_detail = msg.detail();
	return result;
}

}