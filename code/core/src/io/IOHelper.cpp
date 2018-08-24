#include "io/HandlerHelper.h"
#include "io/IOHelper.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace io {

IOHelper::IOHelper() {}
IOHelper::~IOHelper() {}

void IOHelper::write(Object::SPtr entity, const Field* field,
                     const String& value) {
  std::shared_ptr<DataHandler> handler =
      _dataHelper->getHandler(field->getClass(), field->index());
  if (handler) {
    handler->write(entity, field, value);
    return;
  }
  handler = _dataHelper->getHandler(field->getClass());
  if (handler) {
    handler->write(entity, field, value);
    return;
  }

  const Class& fieldCls = field->getClass();
  if (fieldCls == Class::forType<Boolean>()) {
    field->set(entity, StringUtil::convert<Boolean>(value.c_str()));
  } else if (fieldCls == Class::forType<Short>()) {
    field->set(entity, StringUtil::convert<Short>(value.c_str()));
  } else if (fieldCls == Class::forType<Int>()) {
    field->set(entity, StringUtil::convert<Int>(value.c_str()));
  } else if (fieldCls == Class::forType<Long>()) {
    field->set(entity, StringUtil::convert<Long>(value.c_str()));
  } else if (fieldCls == Class::forType<Float>()) {
    field->set(entity, StringUtil::convert<Float>(value.c_str()));
  } else if (fieldCls == Class::forType<Double>()) {
    field->set(entity, StringUtil::convert<Double>(value.c_str()));
  } else if (fieldCls == Class::forType<String>()) {
    field->set(entity, value);
  } else if (fieldCls.isEnum()) {
    field->set(entity, fieldCls.getEnum(value));
  } else if (fieldCls.isMultiEnum()) {
  } else if (fieldCls.isBase(Object::getClassStatic())) {
    std::shared_ptr<EntityHandler> entityHandler =
        _entityHelper->getHandler(fieldCls);
    Object::SPtr relaObj = entityHandler->get(value);
  }
}

void IOHelper::registerDataHandlerImpl(const Class& cls, DataHandler* handler) {
  _dataHelper->registerHandler(cls, std::shared_ptr<DataHandler>(handler));
}

void IOHelper::registerDataHandlerImpl(const Class& cls, Int sign,
                                       DataHandler* handler) {
  _dataHelper->registerHandler(cls, sign,
                               std::shared_ptr<DataHandler>(handler));
}

void IOHelper::registerEntityHandlerImpl(const Class& cls,
                                         EntityHandler* handler) {
  _entityHelper->registerHandler(cls, std::shared_ptr<EntityHandler>(handler));
}

void IOHelper::registerValidateHandlerImpl(const Class& cls,
                                           ValidateHandler* handler) {
  _validateHelper->registerHandler(cls,
                                   std::shared_ptr<ValidateHandler>(handler));
}

void IOHelper::registerValidateHandlerImpl(const Class& cls, Int sign,
                                           ValidateHandler* handler) {
  _validateHelper->registerHandler(cls, sign,
                                   std::shared_ptr<ValidateHandler>(handler));
}

DtoHelper::DtoHelper() {}

DtoHelper::~DtoHelper() {}

}  // namespace io
}  // namespace gemini