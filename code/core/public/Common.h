#ifndef GEMINI_Common_INCLUDE
#define GEMINI_Common_INCLUDE

#include "Platform.h"

#include <cassert>
#include <type_traits>
#include <memory>
#include <string>
#include <atomic>

#include <map>
#include <list>
#include <vector>
#include <set>
#include <functional>

namespace gemini {

/**
 * @brief 以下定义基本数据类型。
 *  数字类型不再区分无符号与有符合，全为有符号类型。
 * 	可确保各类型在不同的平台下具有一致的字节数
 * 
 */
typedef bool Boolean;
typedef char Char;			/// 一字节
typedef wchar_t	WChar;		/// 由平台确定，不建议程序使用
typedef char16_t Char16;	/// 两字节
typedef char32_t Char32;	/// 四字节
typedef short Short;		/// 两字节
typedef int Int;			/// 四字节
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
typedef signed __int64 Long;	/// 八字节
#elif GEMINI_OS == GEMINI_OS_LINUX
typedef signed long long   Long;
#endif
typedef float Float;		/// 四字节
typedef double Double;		/// 八字节
typedef std::string String;	/// utf-8字符串
typedef Long ID;			/// 八字节

/** 
 * @brief 以下定义各基本类型的原子类型，用于多线程环境
 */
typedef std::atomic_bool		MT_Boolean;
typedef std::atomic_char		MT_Char;
typedef std::atomic_wchar_t		MT_WChar;/// 由平台确定，不建议程序使用
typedef std::atomic_char16_t	MT_Char16;
typedef std::atomic_char32_t	MT_Char32;
typedef std::atomic_short		MT_Short;
typedef std::atomic_int			MT_Int;
typedef std::atomic_int64_t		MT_Long;

/**
 * @brief 以下定义各数据类型的最小值及最大值
 * 
 */
#define Boolean_MAX	((std::numeric_limits<Boolean>::max)())
#define Boolean_MIN	((std::numeric_limits<Boolean>::min)())
#define Char_MAX	((std::numeric_limits<Char>::max)())
#define Char_MIN	((std::numeric_limits<Char>::min)())
#define WChar_MAX	((std::numeric_limits<WChar>::max)())/// 由平台确定，不建议程序使用
#define WChar_MIN	((std::numeric_limits<WChar>::min)())/// 由平台确定，不建议程序使用
#define Short_MAX	((std::numeric_limits<Short>::max)())
#define Short_MIN	((std::numeric_limits<Short>::min)())
#define Int_MAX		((std::numeric_limits<Int>::max)())
#define Int_MIN		((std::numeric_limits<Int>::min)())
#define Long_MAX	((std::numeric_limits<Long>::max)())
#define Long_MIN	((std::numeric_limits<Long>::min)())
#define Float_MAX	((std::numeric_limits<Float>::max)())
#define Float_MIN	((std::numeric_limits<Float>::min)())
#define Double_MAX	((std::numeric_limits<Double>::max)())
#define Double_MIN	((std::numeric_limits<Double>::min)())

/**
 * @brief 不包含任何数据成员的类
 * 
 */
class EmptyType {};

/**
 * @brief 当某个类不允许被拷贝时，继承noncopyable
 * 
 */
class noncopyable {
protected:
	noncopyable() = default;
	~noncopyable() = default;

	noncopyable(const noncopyable&) = delete;
	noncopyable& operator=(const noncopyable&) = delete;
};

class CORE_API Platform
{
public:
  static String getEnv(const Char* name);
  static Boolean hasEnv(const Char* name);
  static void setEnv(const Char* name, const Char* value);
  static String osName();
  static String osDisplayName();
  static String osVersion();
  static String osArchitecture();
  static String nodeName();
  static String osID();
  static String CPUID();
  static String mainDiskID();
  static String mainBoardID();
  static String macAddress();
};

}
#endif