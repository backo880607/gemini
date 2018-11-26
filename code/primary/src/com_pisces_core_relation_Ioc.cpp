#include "../include/JavaBeanMgr.h"
#include "../public/com_pisces_core_relation_Ioc.h"
#include "../public/tools/JavaTools.h"
#include "tools/RelationUtil.h"

jint Java_com_pisces_core_relation_Ioc_getRelationType(JNIEnv* env, jclass cls,
                                                       jclass beanCls,
                                                       jint sign) {
  const gemini::Class* cppCls =
      gemini::primary::JavaBeanMgr::instance().getClass(env, beanCls);
  return gemini::RelationUtil::getRelaType(*cppCls, sign);
}

jint Java_com_pisces_core_relation_Ioc_getRelationReverseSign(JNIEnv* env,
                                                              jclass cls,
                                                              jclass beanCls,
                                                              jint sign) {
  const gemini::Class* cppCls =
      gemini::primary::JavaBeanMgr::instance().getClass(env, beanCls);
  return gemini::RelationUtil::getRelaReverseSign(*cppCls, sign);
}

jclass Java_com_pisces_core_relation_Ioc_getEntityClass(JNIEnv* env, jclass cls,
                                                        jclass beanCls,
                                                        jint sign) {
  const gemini::Class* cppCls =
      gemini::primary::JavaBeanMgr::instance().getClass(env, beanCls);

  const gemini::Class* relaCls =
      gemini::RelationUtil::getRelaClass(*cppCls, sign);
  return nullptr;
}

jclass Java_com_pisces_core_relation_Ioc_getEntityClassByName(JNIEnv* env,
                                                              jclass cls,
                                                              jclass beanCls,
                                                              jstring sign) {
  const gemini::Class* cppCls =
      gemini::primary::JavaBeanMgr::instance().getClass(env, beanCls);
  const gemini::Class* relaCls = gemini::RelationUtil::getRelaClassByName(
      *cppCls, gemini::primary::JavaTools::jstring2str(env, sign));
  return nullptr;
}