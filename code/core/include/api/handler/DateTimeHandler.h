#ifndef GEMINI_API_DateTimeHandler_INCLUDE
#define GEMINI_API_DateTimeHandler_INCLUDE
#include "../../../public/api/Handler.h"

namespace gemini {
namespace api {

class DateTimeHandler : public DataHandler {
 public:
  virtual String read(Object::SPtr entity, const Field *field) override;
  virtual void write(Object::SPtr entity, const Field *field,
                     const String &value) override;
};

}  // namespace api
}  // namespace gemini
#endif  // !GEMINI_API_DateTimeHandler_INCLUDE