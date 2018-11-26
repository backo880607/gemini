#ifndef GEMINI_Property_INCLUDE
#define GEMINI_Property_INCLUDE
#include "Object.h"

namespace gemini {

class CORE_API Property : public Entity {
  DECLARE_CLASS(Property, Entity)

  DECLARE_FIELD(Boolean, isReference)
  DECLARE_FIELD(Boolean, canModify)
  DECLARE_FIELD(Boolean, canNull)
  DECLARE_FIELD(Short, precision)
  DECLARE_FIELD(String, showName)
  DECLARE_FIELD(String, bkColor)
  DECLARE_FIELD(String, textColor)
  DECLARE_FIELD(String, tips)
  DECLARE_FIELD(String, expression)

  const Field* getField() const { return _field; }

 private:
  const Field* _field;
};

}  // namespace gemini
#endif  // GEMINI_Property_INCLUDE