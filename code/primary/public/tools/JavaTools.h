#ifndef GEMINI_PRIMARY_JavaTools_INCLUDE
#define GEMINI_PRIMARY_JavaTools_INCLUDE
#include <jni.h>
#include "Common.h"

namespace gemini {
namespace primary {

static const jint PUBLIC = 0x00000001;
static const jint PRIVATE = 0x00000002;
static const jint PROTECTED = 0x00000004;
static const jint STATIC = 0x00000008;
static const jint FINAL = 0x00000010;
class JavaTools {
 public:
  static jstring str2jstring(JNIEnv* env, const Char* pat);
  static String jstring2str(JNIEnv* env, jstring jstr);

  static Boolean isPublic(jint mod);
  static Boolean isPrivate(jint mod);
  static Boolean isProtected(jint mod);
  static Boolean isStatic(jint mod);
  static Boolean isFinal(jint mod);
};

}  // namespace primary
}  // namespace gemini
#endif  // GEMINI_PRIMARY_JavaTools_INCLUDE