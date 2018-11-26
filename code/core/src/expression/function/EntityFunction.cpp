#include "expression/function/EntityFunction.h"

namespace gemini {

DECLARE_CLASS_IMPL(EntityFunction, BaseController)
Boolean EntityFunction::isType(const BaseEntity::SPtr& entity,
                               const String& clsName) {
  const Class& cls = Class::forName(clsName);
  return entity->getClass() == cls;
}

EXPRESSION_REGISTER(EntityFunction, asType)
EXPRESSION_RETURN(asType, 2)
BaseEntity::SPtr EntityFunction::asType(const BaseEntity::SPtr& entity,
                                          const String& clsName) {
  const Class& cls = Class::forName(clsName);
  return entity->getClass().isBase(cls) ? entity : nullptr;
}

}  // namespace gemini