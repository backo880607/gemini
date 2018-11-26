#ifndef GEMINI_Common_INCLUDE
#define GEMINI_Common_INCLUDE

#include "Platform.h"

#include <atomic>
#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>

#include <functional>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace gemini {

/**
 * @brief 以下定义基本数据类型。
 *  数字类型不再区分无符号与有符合，全为有符号类型。
 * 	可确保各类型在不同的平台下具有一致的字节数
 *
 */
typedef bool Boolean;
typedef char Char;        /// 一字节
typedef wchar_t WChar;    /// 由平台确定，不建议程序使用
typedef char16_t Char16;  /// 两字节
typedef char32_t Char32;  /// 四字节
typedef short Short;      /// 两字节
typedef int Int;          /// 四字节
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
typedef signed __int64 Long;  /// 八字节
#elif GEMINI_OS == GEMINI_OS_LINUX
typedef signed long long Long;
#elif GEMINI_OS == GEMINI_OS_MAC_OS_X
typedef signed long long Long;
#endif
typedef float Float;         /// 四字节
typedef double Double;       /// 八字节
typedef std::string String;  /// utf-8字符串
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
typedef unsigned __int64 ID;  /// 八字节
#elif GEMINI_OS == GEMINI_OS_LINUX
typedef unsigned long long ID;
#elif GEMINI_OS == GEMINI_OS_MAC_OS_X
typedef unsigned long long ID;
#endif

/**
 * @brief 以下定义各基本类型的原子类型，用于多线程环境
 */
typedef std::atomic_bool MT_Boolean;
typedef std::atomic_char MT_Char;
typedef std::atomic_wchar_t MT_WChar;  /// 由平台确定，不建议程序使用
typedef std::atomic_char16_t MT_Char16;
typedef std::atomic_char32_t MT_Char32;
typedef std::atomic_short MT_Short;
typedef std::atomic_int MT_Int;
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
typedef volatile std::atomic_int64_t MT_Long;
#elif GEMINI_OS == GEMINI_OS_LINUX
typedef volatile std::atomic_llong MT_Long;
#elif GEMINI_OS == GEMINI_OS_MAC_OS_X
typedef volatile std::atomic_llong MT_Long;
#endif

/**
 * @brief 以下定义各数据类型的最小值及最大值
 *
 */
#define Boolean_MAX ((std::numeric_limits<Boolean>::max)())
#define Boolean_MIN ((std::numeric_limits<Boolean>::min)())
#define Char_MAX ((std::numeric_limits<Char>::max)())
#define Char_MIN ((std::numeric_limits<Char>::min)())
#define WChar_MAX \
  ((std::numeric_limits<WChar>::max)())  /// 由平台确定，不建议程序使用
#define WChar_MIN \
  ((std::numeric_limits<WChar>::min)())  /// 由平台确定，不建议程序使用
#define Short_MAX ((std::numeric_limits<Short>::max)())
#define Short_MIN ((std::numeric_limits<Short>::min)())
#define Int_MAX ((std::numeric_limits<Int>::max)())
#define Int_MIN ((std::numeric_limits<Int>::min)())
#define Long_MAX ((std::numeric_limits<Long>::max)())
#define Long_MIN ((std::numeric_limits<Long>::min)())
#define Float_MAX ((std::numeric_limits<Float>::max)())
#define Float_MIN ((std::numeric_limits<Float>::min)())
#define Double_MAX ((std::numeric_limits<Double>::max)())
#define Double_MIN ((std::numeric_limits<Double>::min)())

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

class CORE_API StringUtilBase : public noncopyable {
 public:
  template <typename T>
  static String format(T val) {
    return formatImpl(val);
  }
  static String format(Float val, Int precision);
  static String format(Double val, Int precision);

  template <typename T>
  static T convert(const Char* str) {
    typename std::remove_const<T>::type val;
    convertImpl(val, str);
    return val;
  }
  template <typename T>
  static T convert(const Char* str, std::size_t fPos, std::size_t lPos) {
    typename std::remove_const<T>::type val;
    convertImpl(val, str, fPos, lPos);
    return val;
  }

 protected:
  static std::ostringstream& getOSStream();
  static std::istringstream& getISStream(const Char* str);

 private:
  template <typename T>
  static String formatImpl(const T& value) {
    return value.toString();
  }
  static String formatImpl(Boolean value);
  static String formatImpl(Short value);
  static String formatImpl(Int value);
  static String formatImpl(Long value);
  static String formatImpl(Float value);
  static String formatImpl(Double value);
  static String formatImpl(Char value);
  static String formatImpl(Char16 value);
  static String formatImpl(Char32 value);
  static String formatImpl(Char* value) { return value; }
  static String formatImpl(const Char* value) { return value; }
  static String formatImpl(WChar* value);
  static String formatImpl(const WChar* value);
  static String formatImpl(const String& value) { return value; }
  static String formatImpl(ID value);

  template <typename T>
  static void convertImpl(T& value, const Char* str) {
    value = T::valueOf(str);
  }
  static void convertImpl(Boolean& value, const Char* str) {
    value = strtol(str, nullptr, 0) != 0;
  }
  static void convertImpl(Short& value, const Char* str);
  static void convertImpl(Int& value, const Char* str);
  static void convertImpl(Long& value, const Char* str);
  static void convertImpl(Float& value, const Char* str);
  static void convertImpl(Double& value, const Char* str);
  static void convertImpl(Char& value, const Char* str);
  static void convertImpl(String& value, const Char* str) { value = str; }
  static void convertImpl(ID& value, const Char* str);

  template <typename T>
  static void convertImpl(T& value, const Char* str, std::size_t fPos,
                          std::size_t lPos) {
    value = T::valueOf(String(str + fPos, lPos - fPos));
  }
  static void convertImpl(Boolean& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
  static void convertImpl(Short& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
  static void convertImpl(Int& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
  static void convertImpl(Long& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
  static void convertImpl(Float& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
  static void convertImpl(Double& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
  static void convertImpl(String& value, const Char* str, std::size_t fPos,
                          std::size_t lPos) {
    value = String(str + fPos, lPos - fPos);
  }
  static void convertImpl(ID& value, const Char* str, std::size_t fPos,
                          std::size_t lPos);
};

template <typename T>
class Vector : public std::vector<T> {
 public:
  String toString() { return ""; }
  static Vector valueOf(const Char* str) { return Vector(); }
};
template <typename T>
class List : public std::list<T> {
 public:
  String toString() { return ""; }
  static List valueOf(const Char* str) { return List(); }
};
template <typename T>
class Deque : public std::deque<T> {
 public:
  String toString() { return ""; }
  static Deque valueOf(const Char* str) { return Deque(); }
};
template <typename T>
class Stack : public std::stack<T> {
 public:
  String toString() { return ""; }
  static Stack valueOf(const Char* str) { return Stack(); }
};
template <typename T>
class Queue : public std::queue<T> {
 public:
  String toString() { return ""; }
  static Queue valueOf(const Char* str) { return Queue(); }
};
template <typename T>
class Set : public std::set<T> {
 public:
  String toString() { return ""; }
  static Set valueOf(const Char* str) { return Set(); }
};
template <typename T>
class MultiSet : public std::multiset<T> {
 public:
  String toString() { return ""; }
  static MultiSet valueOf(const Char* str) { return MultiSet(); }
};
template <typename T>
class HashSet : public std::unordered_set<T> {
 public:
  String toString() { return ""; }
  static HashSet valueOf(const Char* str) { return HashSet(); }
};
template <typename KEY, typename VALUE>
class Map : public std::map<KEY, VALUE> {
 public:
  String toString() { return ""; }
  static Map valueOf(const Char* str) { return Map(); }
};
template <typename KEY, typename VALUE>
class MultiMap : public std::multimap<KEY, VALUE> {
 public:
  String toString() { return ""; }
  static MultiMap valueOf(const Char* str) { return MultiMap(); }
};
template <typename KEY, typename VALUE>
class HashMap : public std::unordered_map<KEY, VALUE> {
 public:
  String toString() { return ""; }
  static HashMap valueOf(const Char* str) { return HashMap(); }
};

class CORE_API Platform {
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

class CORE_API SpinMutex {
  MT_Long m_count;

 public:
  SpinMutex() { m_count.store(0); }
  SpinMutex(const SpinMutex& rhs) { m_count.store(rhs.m_count); }
  ~SpinMutex() {}

  void lock();
  void lock(Long milliseconds) { try_lock(milliseconds); }
  Boolean try_lock() { return m_count.exchange(1) == 0; }
  Boolean try_lock(Long milliseconds);
  void unlock() { m_count = 0; }
};

}  // namespace gemini
#endif