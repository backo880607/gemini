#ifndef GEMINI_RelationUtil_INCLUDE
#define GEMINI_RelationUtil_INCLUDE
#include "Reflect.h"

namespace gemini {

class CORE_API RelationUtil {
 public:
  static Int getRelaType(const Class& cls, Int sign);
  static Int getRelaReverseSign(const Class& cls, Int sign);
  static const Class* getRelaClass(const Class& cls, Int sign);
  static const Class* getRelaClassByName(const Class& cls, const String& name);
};

}  // namespace gemini
#endif  // GEMINI_RelationUtil_INCLUDE