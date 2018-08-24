#ifndef GEMINI_IO_IOHelper_INCLUDE
#define GEMINI_IO_IOHelper_INCLUDE
#include "DataSource.h"

namespace gemini {
namespace io {

class DataHandler;
class EntityHandler;
class ValidateHandler;
class IOScheme;
class DataHandlerHelper;
class EntityHandlerHelper;
class ValidateHandlerHelper;
class CORE_API IOHelper {
 public:
  IOHelper();
  virtual ~IOHelper();

  template <typename T, class HANDLER>
  void registerDataHandler() {
    registerDataHandlerImpl(Class::forType<T>(), new HANDLER());
  }

  template <class CLS, typename FIELD, class HANDLER>
  void registerDataHandler() {
    registerDataHandlerImpl(Class::forType<CLS>(), FIELD::index(),
                            new HANDLER());
  }

  template <class CLS, class HANDLER>
  void registerEntityHandler() {
    registerEntityHandlerImpl(Class::forType<CLS>(), new HANDLER());
  }

  template <typename T, class HANDLER>
  void registerValidateHandler() {
    registerValidateHandlerImpl(Class::forType<T>(), new HANDLER());
  }

  template <class CLS, typename FIELD, class HANDLER>
  void registerValidateHandler() {
    registerValidateHandlerImpl(Class::forType<CLS>(), FIELD::index(),
                                new HANDLER());
  }

 protected:
  void write(Object::SPtr entity, const Field* field,
             const String& value);

 private:
  void registerDataHandlerImpl(const Class& cls, DataHandler* handler);
  void registerDataHandlerImpl(const Class& cls, Int sign,
                               DataHandler* handler);

  void registerEntityHandlerImpl(const Class& cls, EntityHandler* handler);

  void registerValidateHandlerImpl(const Class& cls, ValidateHandler* handler);
  void registerValidateHandlerImpl(const Class& cls, Int sign,
                                   ValidateHandler* handler);

 protected:
  std::shared_ptr<DataSource> _dataSource;
  std::shared_ptr<DataHandlerHelper> _dataHelper;
  std::shared_ptr<EntityHandlerHelper> _entityHelper;
  std::shared_ptr<ValidateHandlerHelper> _validateHelper;
};

class CORE_API DtoHelper : public IOHelper {
 public:
  DtoHelper();
  virtual ~DtoHelper();
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_IOHelper_INCLUDE