#ifndef GEMINI_PRIMARY_JavaBeanMgr_INCLUDE
#define GEMINI_PRIMARY_JavaBeanMgr_INCLUDE
#include <jni.h>
#include "Reflect.h"

namespace gemini {
namespace primary {

class JavaBeanMgr final {
  JavaBeanMgr();
  JavaBeanMgr(const JavaBeanMgr&) {}
  JavaBeanMgr& operator=(const JavaBeanMgr&) { return *this; }

 public:
  static JavaBeanMgr& instance() {
    static JavaBeanMgr mgr;
    return mgr;
  }

  const Class* registerBean(JNIEnv* env, jclass beanCls, jmethodID class_name);

  const Class* getClass(JNIEnv* env, jclass beanCls);

 private:
  jmethodID _class_hashCode;
  jclass _cls_EntityObject;
  std::map<Int, const Class*> _clses;
};

}  // namespace primary
}  // namespace gemini

#endif  // GEMINI_PRIMARY_JavaBeanMgr_INCLUDE