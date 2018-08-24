#include "io/handler/DateTimeHandler.h"

namespace gemini {
namespace io {

String DateTimeHandler::read(Object::SPtr entity, const Field *field) {
  return "";
}

void DateTimeHandler::write(Object::SPtr entity, const Field *field,
                            const String &value) {}

}  // namespace io
}  // namespace gemini