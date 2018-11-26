#include "../include/JavaBeanMgr.h"
#include "../public/com_pisces_core_Initializer.h"
#include "IApplication.h"
#include "../public/tools/JavaTools.h"
#include "Object.h"

using namespace gemini::primary;

void initSign(JNIEnv* env, jclass beanCls) {
  if (beanCls == nullptr) {
    return;
  }
  const gemini::Class* cls = JavaBeanMgr::instance().getClass(env, beanCls);
  if (cls == nullptr) {
    return;
  }

  if (*cls == gemini::BaseEntity::getClassStatic()) {
    return;
  } else {
    initSign(env, env->GetSuperclass(beanCls));
  }



}

void Java_com_pisces_core_Initializer_load(JNIEnv* env, jclass cls,
                                           jobject clses) {
  /* get the list class */
  jclass cls_list = env->GetObjectClass(clses);
  if (cls_list == nullptr) {
    // printf("%s", "not find class\n");
    return;
  }

  /* method in class List  */
  jmethodID list_get =
      env->GetMethodID(cls_list, "get", "(I)Ljava/lang/Object;");
  jmethodID list_size = env->GetMethodID(cls_list, "size", "()I");
  if (list_get == nullptr) {
    // printf("%s", "not find get method\n");
    return;
  }
  if (list_size == nullptr) {
    // printf("%s", "not find size method\n");
    return;
  }

  jclass cls_class = env->FindClass("java/lang/Class");
  if (cls_class == nullptr) {
    return;
  }

  jmethodID class_name =
      env->GetMethodID(cls_class, "getSimpleName", "()Ljava/lang/String;");
  if (class_name == nullptr) {
    return;
  }

  /* jni invoke list.get to get points count */
  gemini::Int len = static_cast<int>(env->CallIntMethod(clses, list_size));
  for (gemini::Int i = 0; i < len; i++) {
    // get list the element -- float[]
    jclass element = (jclass)(env->CallObjectMethod(clses, list_get, i));
    if (element == NULL) {
      // printf("%s", "fetch list element failure\n");
      continue;
    }
    JavaBeanMgr::instance().registerBean(env, element, class_name);
  }

  gemini::getApp().init();
}
