#ifndef GEMINI_IO_DateTimeHandler_INCLUDE
#define GEMINI_IO_DateTimeHandler_INCLUDE
#include "io/DataHandler.h"

namespace gemini
{
namespace io
{
class DateTimeHandler : public DataHandler
{
  public:
    virtual String read(EntityObject::SPtr entity, const Field *field);
    virtual void write(EntityObject::SPtr entity, const Field *field, const String &value);
};
} // namespace io
} // namespace gemini
#endif // !GEMINI_IO_DateTimeHandler_INCLUDE