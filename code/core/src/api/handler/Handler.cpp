#include "../../../include/dao/DaoUtil.h"
#include "api/Handler.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace api {

Object::SPtr ObjectHandler::require() {
  Object *pObject = (Object *)_cls->newInstance();
  Object::SPtr object;
  object.wrapRawPointer(pObject);
  return object;
}

IDEntityHandler::IDEntityHandler() {}

IDEntityHandler::~IDEntityHandler() {}

Object::SPtr IDEntityHandler::get(const String &primary) {
  const ID id = StringUtil::convert<ID>(primary.c_str());
  return DaoUtil::get(*_cls, id);
}

Object::SPtr IDEntityHandler::require(const String &primary) {
  const ID id = StringUtil::convert<ID>(primary.c_str());
  return DaoUtil::create(*_cls, id);
}

Object::SPtr IDEntityHandler::require() { return DaoUtil::createTemp(*_cls); }

/*PrimaryKeyHandler::PrimaryKeyHandler() { init(); }

PrimaryKeyHandler::~PrimaryKeyHandler() {}

Object::SPtr PrimaryKeyHandler::get(const String &primary) {
  const ID id = StringUtil::convert<ID>(primary.c_str());
  return DaoUtil::get(*_cls, id);
}

Object::SPtr PrimaryKeyHandler::require(const String &primary) {
  const ID id = StringUtil::convert<ID>(primary.c_str());
  return DaoUtil::create(*_cls, id);
}

Object::SPtr PrimaryKeyHandler::require() { return DaoUtil::createTemp(*_cls); }

void PrimaryKeyHandler::init() {
  const IList &entities = DaoUtil::getList(*_cls);
  const std::vector<const Field *> fields = _cls->getPrimaryFields();
  for (const Field *field : fields) {
  }
}*/

}  // namespace api
}  // namespace gemini