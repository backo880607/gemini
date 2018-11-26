#include "../../include/api/handler/HandlerHelper.h"
#include "../../public/api/IOHelper.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace api {

IOHelper::IOHelper() {}
IOHelper::~IOHelper() {}

std::shared_ptr<ObjectHandler> IOHelper::getObjectHandler(const Class& cls) {
  std::shared_ptr<ObjectHandler> objectHandler = _objectHelper->getHandler(cls);
  if (objectHandler == nullptr) {
    objectHandler = _defaultObjectHandler;
  }
  if (objectHandler != nullptr) {
    objectHandler->setClass(cls);
  }
  return objectHandler;
}

std::shared_ptr<ValidateHandler> IOHelper::getValidateHandler(
    const Field& field) {
  std::shared_ptr<ValidateHandler> validateHandler =
      _validateHelper->getHandler(field.getClass(), field);
  return validateHandler != nullptr
             ? validateHandler
             : _validateHelper->getHandler(field.getType());
}

void IOHelper::write(Object::SPtr entity, const Field* field,
                     const String& value) {
  std::shared_ptr<DataHandler> handler =
      _dataHelper->getHandler(field->getClass(), *field);
  if (handler == nullptr) {
    handler = _dataHelper->getHandler(field->getClass());
  }
  if (handler) {
    handler->write(entity, field, value);
    return;
  }

  StringUtil::setField(entity, *field, value.c_str());
}

void IOHelper::registerDataHandlerImpl(const Class& cls, DataHandler* handler) {
  _dataHelper->registerHandler(cls, std::shared_ptr<DataHandler>(handler));
}

void IOHelper::registerDataHandlerImpl(const Class& cls, const Field& field,
                                       DataHandler* handler) {
  _dataHelper->registerHandler(cls, field,
                               std::shared_ptr<DataHandler>(handler));
}

void IOHelper::registerObjectHandlerImpl(const Class& cls,
                                         ObjectHandler* handler) {
  _objectHelper->registerHandler(cls, std::shared_ptr<ObjectHandler>(handler));
}

void IOHelper::registerDefaultObjectHandlerImpl(const Class& cls,
                                                ObjectHandler* handler) {
  _defaultObjectHandler.reset(handler);
}

void IOHelper::registerValidateHandlerImpl(const Class& cls,
                                           ValidateHandler* handler) {
  _validateHelper->registerHandler(cls,
                                   std::shared_ptr<ValidateHandler>(handler));
}

void IOHelper::registerValidateHandlerImpl(const Class& cls, const Field& field,
                                           ValidateHandler* handler) {
  _validateHelper->registerHandler(cls, field,
                                   std::shared_ptr<ValidateHandler>(handler));
}

}  // namespace api
}  // namespace gemini