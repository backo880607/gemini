#include "../../public/message/Message.h"
#include "../../include/cache/Cache.h"

namespace gemini {

DECLARE_CLASS_IMPL(Message, EntityObject)
Message::Message()
{
}

Message::~Message()
{

}

Message::SPtr Message::createImpl(Type type, log_info& msg, Boolean bTemp /* = false */)
{
	Message::SPtr result = bTemp ? Message::SPtr(true) : Cache::create(Message::getClassStatic(), 0);
	result->_type = type;
	return result;
}

}