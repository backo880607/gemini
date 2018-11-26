#include "../../public/tools/JavaTools.h"

namespace gemini {
namespace primary {

jstring JavaTools::str2jstring(JNIEnv* env, const Char* pat) {
  //����java String�� strClass
  jclass strClass = (env)->FindClass("Ljava/lang/String;");
  //��ȡString(byte[],String)�Ĺ�����,���ڽ�����byte[]����ת��Ϊһ����String
  jmethodID ctorID =
      (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
  //����byte����
  jbyteArray bytes = (env)->NewByteArray(strlen(pat));
  //��char* ת��Ϊbyte����
  (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
  // ����String, ������������,����byte����ת����Stringʱ�Ĳ���
  jstring encoding = (env)->NewStringUTF("utf8");
  //��byte����ת��Ϊjava String,�����
  return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}

String JavaTools::jstring2str(JNIEnv* env, jstring jstr) {
  char* rtn = NULL;
  jclass clsstring = env->FindClass("java/lang/String");
  jstring strencode = env->NewStringUTF("GB2312");
  jmethodID mid =
      env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
  jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
  jsize alen = env->GetArrayLength(barr);
  jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
  if (alen > 0) {
    rtn = new char[alen + 1];
    memcpy(rtn, ba, alen);
    rtn[alen] = 0;
  }
  env->ReleaseByteArrayElements(barr, ba, 0);
  std::string stemp(rtn);
  delete[] rtn;
  return stemp;
}

Boolean JavaTools::isPublic(jint mod) { return (mod & PUBLIC) != 0; }

Boolean JavaTools::isPrivate(jint mod) { return (mod & PRIVATE) != 0; }

Boolean JavaTools::isProtected(jint mod) { return (mod & PROTECTED) != 0; }

Boolean JavaTools::isStatic(jint mod) { return (mod & STATIC) != 0; }

Boolean JavaTools::isFinal(jint mod) { return (mod & FINAL) != 0; }

}  // namespace primary
}  // namespace gemini