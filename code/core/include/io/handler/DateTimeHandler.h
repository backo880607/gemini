#ifndef GEMINI_IO_DateTimeHandler_INCLUDE
#define GEMINI_IO_DateTimeHandler_INCLUDE
#include "../../../public/io/Handler.h"

namespace gemini {
namespace io {

class DateTimeHandler : public DataHandler {
 public:
  virtual String read(Object::SPtr entity, const Field *field);
  virtual void write(Object::SPtr entity, const Field *field,
                     const String &value);
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_DateTimeHandler_INCLUDE