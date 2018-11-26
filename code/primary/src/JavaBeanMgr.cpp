#include "../include/JavaBeanMgr.h"
#include "../public/tools/JavaTools.h"
#include "Object.h"

namespace gemini {
namespace primary {

JavaBeanMgr::JavaBeanMgr()
    : _class_hashCode(nullptr), _cls_EntityObject(nullptr) {}

const Class* JavaBeanMgr::registerBean(JNIEnv* env, jclass beanCls,
                                       jmethodID class_name) {
  if (_class_hashCode == nullptr) {
    jclass cls_class = env->FindClass("java/lang/Class");
    _class_hashCode = env->GetMethodID(cls_class, "hashCode", "()I");
  }
  if (_cls_EntityObject == nullptr) {
    _cls_EntityObject = env->FindClass("com/pisces/core/entity/EntityObject");
  }
  if (env->IsSameObject(beanCls, _cls_EntityObject)) {
    return &BaseEntity::getClassStatic();
  }

  const Class* superCls = nullptr;
  jclass superJCls = env->GetSuperclass(beanCls);
  if (superJCls != nullptr) {
    superCls = registerBean(env, superJCls, class_name);
  } else {
    return &Object::getClassStatic();
  }

  const Int hashCode = env->CallIntMethod(beanCls, _class_hashCode);
  std::map<Int, const Class*>::iterator iter = _clses.find(hashCode);
  if (iter != _clses.end()) {
    return iter->second;
  }

  jstring beanName = (jstring)env->CallObjectMethod(beanCls, class_name);
  if (beanName == nullptr) {
    // continue;
  }
  const Class* cls = new Class(JavaTools::jstring2str(env, beanName).c_str(),
                               superCls, nullptr, nullptr);
  _clses.insert(std::make_pair(hashCode, cls));

  jclass cls_class = env->FindClass("java/lang/Class");
  jmethodID class_fields = env->GetMethodID(cls_class, "getDeclaredFields",
                                            "()[Ljava/lang/reflect/Field;");

  jclass cls_field = env->FindClass("java/lang/reflect/Field");
  jmethodID field_modifiers =
      env->GetMethodID(cls_field, "getModifiers", "()I");
  jmethodID field_getInt = env->GetMethodID(
      cls_field, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");

  jclass cls_sign = env->FindClass("com/pisces/core/relation/Sign");
  jmethodID sign_setValue = env->GetMethodID(cls_sign, "setValue", "(I)V");

  jobjectArray fields =
      (jobjectArray)env->CallObjectMethod(beanCls, class_fields);
  jint arr_len = env->GetArrayLength(fields);
  for (jint i = 0; i < arr_len; ++i) {
    jobject field = env->GetObjectArrayElement(fields, i);
    if (field == nullptr) {
      continue;
    }
    jint modifiers = env->CallIntMethod(field, field_modifiers);
    if (JavaTools::isStatic(modifiers) && JavaTools::isFinal(modifiers)) {
      jobject sign = env->CallObjectMethod(field, field_getInt, beanCls);
      env->CallVoidMethod(sign, sign_setValue, 1);
    }
  }
  return cls;
}

const Class* JavaBeanMgr::getClass(JNIEnv* env, jclass beanCls) {
  const Int hashCode = env->CallIntMethod(beanCls, _class_hashCode);
  std::map<Int, const Class*>::iterator iter = _clses.find(hashCode);
  return iter != _clses.end() ? iter->second : nullptr;
}

}  // namespace primary
}  // namespace gemini