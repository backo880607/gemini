#include "dao/Memory.h"
#include "message/Message.h"

namespace gemini {

DECLARE_CLASS_IMPL(Message, EntityObject)

Message::SPtr Message::createImpl(Type type, log_info& msg,
                                  Boolean bTemp /* = false */) {
  Message::SPtr result = bTemp ? Memory::createTemp(Message::getClassStatic())
                               : Memory::create(Message::getClassStatic(), 0);
  result->_type = type;
  result->_name = msg.getName();
  result->_detail = msg.detail();
  return result;
}

}  // namespace gemini