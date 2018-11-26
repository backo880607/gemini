#ifndef GEMINI_EntityFunction_INCLUDE
#define GEMINI_EntityFunction_INCLUDE
#include "../../../public/controller/BaseController.h"

namespace gemini {

class EntityFunction : public BaseController {
  DECLARE_CLASS(EntityFunction, BaseController)

  METHOD(Boolean, isType,
         (const BaseEntity::SPtr& entity, const String& clsName))
  METHOD(BaseEntity::SPtr, asType,
         (const BaseEntity::SPtr& entity, const String& clsName))
};

}  // namespace gemini
#endif  // !GEMINI_EntityFunction_INCLUDE