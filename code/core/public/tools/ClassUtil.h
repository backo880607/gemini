#ifndef GEMINI_ClassUtil_INCLUDE
#define GEMINI_ClassUtil_INCLUDE
#include "../Reflect.h"

namespace gemini {

class CORE_API ClassUtil {
 public:
  template <typename FUN>
  static void foreach_fields(const Class& cls, FUN fun) {
    const Class* temp = &cls;
    do {
      temp->foreach_fields(fun);
      temp = temp->hasSuper() ? &temp->getSuperClass() : nullptr;
    } while (temp != nullptr);
  }

  static std::vector<const Field*> getKeyFields(const Class& cls);

  static const Field& getField(const Class& cls, const String& name);
  static Boolean hasField(const Class& cls, const String& name);

  static const Method& getMethod(const Class& cls, const String& name);

  static void swap(const Field& field, const SmartPtr<Object>& src,
                   const SmartPtr<Object>& target);
};

}  // namespace gemini
#endif  // GEMINI_ClassUtil_INCLUDE