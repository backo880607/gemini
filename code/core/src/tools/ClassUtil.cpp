#include "../../public/message/Exception.h"
#include "../../public/tools/ClassUtil.h"

namespace gemini {

std::vector<const Field*> ClassUtil::getKeyFields(const Class& cls) {
  std::vector<const Field*> result;
  const Class* temp = &cls;
  do {
    for (const Field* field : temp->getKeyFields()) {
      result.push_back(field);
    }
    temp = temp->hasSuper() ? &temp->getSuperClass() : nullptr;
  } while (temp != nullptr);

  return result;
}

const Field& ClassUtil::getField(const Class& cls, const String& name) {
  const Class* temp = &cls;
  do {
    const Field* field = temp->getField(name);
    if (field != nullptr) {
      return *field;
    }
    temp = temp->hasSuper() ? &temp->getSuperClass() : nullptr;
  } while (temp != nullptr);

  THROW(NoSuchFieldException, name, " is not existed in class ", cls.getName())
}

Boolean ClassUtil::hasField(const Class& cls, const String& name) {
  const Class* temp = &cls;
  do {
    if (temp->hasField(name)) {
      return true;
    }
    temp = temp->hasSuper() ? &temp->getSuperClass() : nullptr;
  } while (temp != nullptr);

  return false;
}

const Method& ClassUtil::getMethod(const Class& cls, const String& name) {
  const Class* temp = &cls;
  do {
    const Method* method = temp->getMethod(name);
    if (method != nullptr) {
      return *method;
    }
    temp = temp->hasSuper() ? &temp->getSuperClass() : nullptr;
  } while (temp != nullptr);

  THROW(NoSuchMethodException, name, " is not existed in class ", cls.getName())
}

void ClassUtil::swap(const Field& field, const SmartPtr<Object>& src,
                     const SmartPtr<Object>& target) {
  field.getType()._holder->swap(field, src, target);
}

}  // namespace gemini