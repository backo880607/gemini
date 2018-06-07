#ifndef GEMINI_IO_DataHandler_INCLUDE
#define GEMINI_IO_DataHandler_INCLUDE
#include "../Object.h"

namespace gemini
{
namespace io
{
class CORE_API DataHandler
{
public:
  virtual String read(EntityObject::SPtr entity, const Field *field) = 0;
  virtual void write(EntityObject::SPtr entity, const Field *field, const String &value) = 0;
};
} // namespace io
} // namespace gemini
#endif // !GEMINI_IO_DataHandler_INCLUDE