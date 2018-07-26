#include "io/HandlerHelper.h"
#include "io/IOHelper.h"

namespace gemini {
namespace io {

IOHelper::IOHelper() {}
IOHelper::~IOHelper() {}

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

}  // namespace io
}  // namespace gemini