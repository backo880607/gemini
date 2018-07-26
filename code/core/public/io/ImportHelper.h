#ifndef GEMINI_IO_ImportHelper_INCLUDE
#define GEMINI_IO_ImportHelper_INCLUDE
#include "IOHelper.h"

namespace gemini {
namespace io {

class IOScheme;
class CORE_API ImportHelper : public IOHelper {
 public:
  ImportHelper();
  ~ImportHelper();

  void execute();

 private:
  Boolean parseIOScheme(SmartPtr<IOScheme> scheme);
  std::map<Int, const Field*> parsePrimaries(SmartPtr<IOScheme> scheme);
  String obtainValue(Int index, const Field* field);
  String obtainPrimary(const std::map<Int, const Field*>& primaries);
  void write(EntityObject::SPtr entity, const Field* field,
             const String& value);
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_ImportHelper_INCLUDE