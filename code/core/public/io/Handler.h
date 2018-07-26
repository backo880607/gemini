#ifndef GEMINI_IO_Handler_INCLUDE
#define GEMINI_IO_Handler_INCLUDE
#include "../Object.h"

namespace gemini {
namespace io {

class CORE_API DataHandler {
 public:
  virtual String read(EntityObject::SPtr entity, const Field *field) = 0;
  virtual void write(EntityObject::SPtr entity, const Field *field,
                     const String &value) = 0;
};

class CORE_API EntityHandler {
 public:
  EntityHandler(const Class &cls) : _cls(cls) {}
  virtual ~EntityHandler() {}

  virtual EntityObject::SPtr get(const String &primary) = 0;
  virtual EntityObject::SPtr require(const String &primary) = 0;

 private:
  const Class &_cls;
};

class CORE_API ValidateHandler {
 public:
  ValidateHandler() {}
  virtual ~ValidateHandler() {}
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_Handler_INCLUDE