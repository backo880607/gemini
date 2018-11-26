#include "../../../include/api/handler/HandlerHelper.h"
#include "message/Exception.h"

namespace gemini {
namespace api {

DataHandlerHelper::DataHandlerHelper() {}

DataHandlerHelper::~DataHandlerHelper() {}

void DataHandlerHelper::registerHandler(const Class& cls,
                                        handler_type handler) {
  auto iter = _clsHandlers.find(&cls);
  THROW_IF(iter != _clsHandlers.end(), RegisterException, cls.getName(),
           " has registed")
  _clsHandlers.insert(std::make_pair(&cls, handler));
}

void DataHandlerHelper::registerHandler(const Class& cls, const Field& field,
                                        handler_type handler) {
  std::map<const Field*, handler_type>& handlers = _fieldHandlers[&cls];
  if (handlers.empty()) {
    THROW_IF(handlers.find(&field) != handlers.end(), RegisterException,
             "the field ", field.getName(), " of ", cls.getName(),
             " has registed")

    handlers.insert(std::make_pair(&field, handler));
  }
}

DataHandlerHelper::handler_type DataHandlerHelper::getHandler(
    const Class& cls) {
  auto iter = _clsHandlers.find(&cls);
  return iter != _clsHandlers.end() ? iter->second : nullptr;
}

DataHandlerHelper::handler_type DataHandlerHelper::getHandler(
    const Class& cls, const Field& field) {
  auto iter = _fieldHandlers.find(&cls);
  if (iter == _fieldHandlers.end()) {
    return nullptr;
  }
  auto iterField = iter->second.find(&field);
  return iterField != iter->second.end() ? iterField->second : nullptr;
}

ObjectHandlerHelper::ObjectHandlerHelper() {}

ObjectHandlerHelper::~ObjectHandlerHelper() {}

void ObjectHandlerHelper::registerHandler(const Class& cls,
                                          handler_type handler) {
  auto iter = _handlers.find(&cls);
  THROW_IF(iter != _handlers.end(), RegisterException, cls.getName(),
           " has registed")
  _handlers.insert(std::make_pair(&cls, handler));
}

ObjectHandlerHelper::handler_type ObjectHandlerHelper::getHandler(
    const Class& cls) {
  auto iter = _handlers.find(&cls);
  return iter != _handlers.end() ? iter->second : nullptr;
}

ValidateHandlerHelper::ValidateHandlerHelper() {}

ValidateHandlerHelper::~ValidateHandlerHelper() {}

void ValidateHandlerHelper::registerHandler(const Class& cls,
                                            handler_type handler) {
  auto iter = _clsHandlers.find(&cls);
  THROW_IF(iter != _clsHandlers.end(), RegisterException, cls.getName(),
           " has registed")
  _clsHandlers.insert(std::make_pair(&cls, handler));
}

void ValidateHandlerHelper::registerHandler(const Class& cls,
                                            const Field& field,
                                            handler_type handler) {
  std::map<const Field*, handler_type>& handlers = _fieldHandlers[&cls];
  if (handlers.empty()) {
    THROW_IF(handlers.find(&field) != handlers.end(), RegisterException,
             "the field ", field.getName(), " of ", cls.getName(),
             " has registed")

    handlers.insert(std::make_pair(&field, handler));
  }
}

ValidateHandlerHelper::handler_type ValidateHandlerHelper::getHandler(
    const Class& cls) {
  auto iter = _clsHandlers.find(&cls);
  return iter != _clsHandlers.end() ? iter->second : nullptr;
}

ValidateHandlerHelper::handler_type ValidateHandlerHelper::getHandler(
    const Class& cls, const Field& field) {
  auto iter = _fieldHandlers.find(&cls);
  if (iter == _fieldHandlers.end()) {
    return nullptr;
  }
  auto iterField = iter->second.find(&field);
  return iterField != iter->second.end() ? iterField->second : nullptr;
}

}  // namespace api
}  // namespace gemini