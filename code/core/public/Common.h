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
 * @brief 以下定义基本类型，
 * 	可确保各类型在不同的平台下具有一致的字节数
 * 
 */
typedef bool Boolean;
typedef char Char;		/// 有符号，一字节
typedef unsigned char UChar;	/// 无符号，一字节
typedef wchar_t	WChar;		/// 由平台确定，不建议程序使用
typedef char16_t Char16;	/// 有符号，两字节
typedef char32_t Char32;	/// 有符号，四字节
typedef short Short;		/// 有符号，两字节
typedef unsigned short UShort;	/// 无符号，两字节
typedef int Int;			/// 有符号，四字节
typedef unsigned int UInt;	/// 无符号，四字节
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
typedef signed __int64 Long;	/// 有符号，八字节
typedef unsigned __int64 ULong; /// 无符号，八字节
#elif GEMINI_OS == GEMINI_OS_LINUX
typedef signed long long   Long;
typedef unsigned long long ULong;
#endif
typedef float Float;	/// 有符号，四字节
typedef double Double;	/// 有符号，八字节
typedef long double LDouble;	/// 有符号，
typedef std::string String;	/// utf-8字符串
typedef ULong ID;		/// 无符号，八字节

/** 
 * @brief 以下定义各基本类型的原子类型，用于多线程环境
 */
typedef std::atomic_bool		MT_Boolean;
typedef std::atomic_char		MT_Char;
typedef std::atomic_uchar		MT_UChar;
typedef std::atomic_wchar_t		MT_WChar;
typedef std::atomic_short		MT_Short;
typedef std::atomic_ushort		MT_UShort;
typedef std::atomic_int			MT_Int;
typedef std::atomic_uint		MT_UInt;
typedef std::atomic_llong		MT_Long;
typedef std::atomic_ullong		MT_ULong;


/**
 * @brief 以下定义各数据类型的最小值及最大值
 * 
 */
#define Boolean_MAX	((std::numeric_limits<Boolean>::max)())
#define Boolean_MIN	((std::numeric_limits<Boolean>::min)())
#define Char_MAX	((std::numeric_limits<Char>::max)())
#define Char_MIN	((std::numeric_limits<Char>::min)())
#define UChar_MAX	((std::numeric_limits<UChar>::max)())
#define UChar_MIN	((std::numeric_limits<UChar>::min)())
#define WChar_MAX	((std::numeric_limits<WChar>::max)())
#define WChar_MIN	((std::numeric_limits<WChar>::min)())
#define Short_MAX	((std::numeric_limits<Short>::max)())
#define Short_MIN	((std::numeric_limits<Short>::min)())
#define UShort_MAX	((std::numeric_limits<UShort>::max)())
#define UShort_MIN	((std::numeric_limits<UShort>::min)())
#define Int_MAX		((std::numeric_limits<Int>::max)())
#define Int_MIN		((std::numeric_limits<Int>::min)())
#define UInt_MAX	((std::numeric_limits<UInt>::max)()) 
#define UInt_MIN	((std::numeric_limits<UInt>::min)())
#define Long_MAX	((std::numeric_limits<Long>::max)())
#define Long_MIN	((std::numeric_limits<Long>::min)())
#define ULong_MAX	((std::numeric_limits<ULong>::max)())
#define ULong_MIN	((std::numeric_limits<ULong>::min)())
#define Float_MAX	((std::numeric_limits<Float>::max)())
#define Float_MIN	((std::numeric_limits<Float>::min)())
#define Double_MAX	((std::numeric_limits<Double>::max)())
#define Double_MIN	((std::numeric_limits<Double>::min)())
#define LDouble_MAX	((std::numeric_limits<LDouble>::max)())
#define LDouble_MIN	((std::numeric_limits<LDouble>::min)())

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