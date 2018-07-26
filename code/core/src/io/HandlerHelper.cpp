#include "io/HandlerHelper.h"
#include "message/Exception.h"

namespace gemini {
namespace io {

DataHandlerHelper::DataHandlerHelper() {}

DataHandlerHelper::~DataHandlerHelper() {}

void DataHandlerHelper::registerHandler(const Class& cls,
                                        handler_type handler) {
  auto iter = _clsHandlers.find(&cls);
  THROW_IF(iter != _clsHandlers.end(), RegisterException, cls.getName(),
           " has registed")
  _clsHandlers.insert(std::make_pair(&cls, handler));
}

void DataHandlerHelper::registerHandler(const Class& cls, Int sign,
                                        handler_type handler) {
  std::vector<handler_type>& handlers = _fieldHandlers[&cls];
  if (handlers.empty()) {
    handlers.resize(cls.maxIndex());
  }
}

DataHandlerHelper::handler_type DataHandlerHelper::getHandler(
    const Class& cls) {
  auto iter = _clsHandlers.find(&cls);
  return iter != _clsHandlers.end() ? iter->second : nullptr;
}

DataHandlerHelper::handler_type DataHandlerHelper::getHandler(const Class& cls,
                                                              Int sign) {
  auto iter = _fieldHandlers.find(&cls);
  if (iter == _fieldHandlers.end() || iter->second.size() >= sign) {
    return nullptr;
  }
  return iter->second[sign];
}

EntityHandlerHelper::EntityHandlerHelper() {}

EntityHandlerHelper::~EntityHandlerHelper() {}

void EntityHandlerHelper::registerHandler(const Class& cls,
                                          handler_type handler) {
  auto iter = _handlers.find(&cls);
  THROW_IF(iter != _handlers.end(), RegisterException, cls.getName(),
           " has registed")
  _handlers.insert(std::make_pair(&cls, handler));
}

EntityHandlerHelper::handler_type EntityHandlerHelper::getHandler(
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

void ValidateHandlerHelper::registerHandler(const Class& cls, Int sign,
                                            handler_type handler) {
  std::vector<handler_type>& handlers = _fieldHandlers[&cls];
  if (handlers.empty()) {
    handlers.resize(cls.maxIndex());
  }
}

ValidateHandlerHelper::handler_type ValidateHandlerHelper::getHandler(
    const Class& cls) {
  auto iter = _clsHandlers.find(&cls);
  return iter != _clsHandlers.end() ? iter->second : nullptr;
}

ValidateHandlerHelper::handler_type ValidateHandlerHelper::getHandler(
    const Class& cls, Int sign) {
  auto iter = _fieldHandlers.find(&cls);
  if (iter == _fieldHandlers.end() || iter->second.size() >= sign) {
    return nullptr;
  }
  return iter->second[sign];
}

}  // namespace io
}  // namespace gemini