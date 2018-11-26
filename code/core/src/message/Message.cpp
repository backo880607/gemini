#include "dao/DaoUtil.h"
#include "message/Message.h"

namespace gemini {

DECLARE_CLASS_IMPL(Message, Entity)

Message::SPtr Message::createImpl(Type type, log_info& msg,
                                  Boolean bTemp /* = false */) {
  Message::SPtr result = bTemp ? DaoUtil::createTemp(Message::getClassStatic())
                               : DaoUtil::create(Message::getClassStatic(), 0);
  result->_type = type;
  result->_name = msg.getName();
  result->_detail = msg.detail();
  return result;
}

}  // namespace gemini