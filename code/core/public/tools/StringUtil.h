#ifndef GEMINI_StringUtil_INCLUDE
#define GEMINI_StringUtil_INCLUDE
#include "../Object.h"

namespace gemini {

class CORE_API StringUtil final : public StringUtilBase {
  StringUtil() = delete;
  StringUtil(const StringUtil&) = delete;
  StringUtil& operator=(const StringUtil&) = delete;

 public:
  static void to_upper(String& str);
  static void to_lower(String& str);

  static void trim_lift(String& str);
  static void trim_right(String& str);
  static void trim(String& str);

  static Boolean starts_with(const Char* str, const Char* test);
  static Boolean istarts_with(const Char* str, const Char* test);
  static Boolean ends_with(const Char* str, const Char* test);
  static Boolean iends_with(const Char* str, const Char* test);
  static Boolean contains(const Char* str, const Char* test);
  static Boolean icontains(const Char* str, const Char* test);
  static Boolean equals(const Char* str, const Char* test);
  static Boolean iequals(const Char* str, const Char* test);
  static Int compare(const Char* str, const Char* test);
  static Int icompare(const Char* str, const Char* test);

  static String::size_type ifind_first(const Char* str, const Char* test);
  static String::size_type ifind_last(const Char* str, const Char* test);
  static String get_head(const Char* str, const Char* sep);
  static String iget_head(const Char* str, const Char* sep);
  static String get_tail(const Char* str, const Char* sep);
  static String iget_tail(const Char* str, const Char* sep);

  static void erase_all(String& str, const Char* dest);
  static void ierase_all(String& str, const Char* dest);
  static void erase_first(String& str, const Char* dest);
  static void ierase_first(String& str, const Char* dest);
  static String fetch_first(String& str, const Char* sep);
  static String fetch_end(String& str, const Char* sep);

  static const Char* increment(const Char* str);
  static const Char* descending(const Char* str);

  static void replace(String& str, const Char* origin, const Char* des);

  static void append(String& str) {}
  template <typename T, typename... Args>
  static void append(String& str, T val, Args... args) {
    str.append(format(val));
    append(str, args...);
  }

  template <typename T>
  static String join(const T& container, const Char* sep) {
    typename T::const_iterator fIter = container.begin();
    typename T::const_iterator lIter = container.end();
    return std::move(join(fIter, lIter, sep));
  }
  template <typename InputIter>
  static String join(InputIter fIter, InputIter lIter, const Char* sep) {
    String value;
    for (; fIter != lIter; ++fIter) {
      value += format(*fIter) += sep;
    }
    if (!value.empty()) {
      value.erase(value.size() - strlen(sep));
    }

    return std::move(value);
  }
  template <typename T, typename FUN>
  static String join(const T& container, const Char* sep, FUN fun) {
    typename T::const_iterator fIter = container.begin();
    typename T::const_iterator lIter = container.end();
    return std::move(join(fIter, lIter, sep, fun));
  }
  template <typename InputIter, typename FUN>
  static String join(InputIter fIter, InputIter lIter, const Char* sep,
                     FUN fun) {
    String value;
    for (; fIter != lIter; ++fIter) {
      value += fun(*fIter) += sep;
    }
    if (!value.empty()) {
      value.erase(value.size() - strlen(sep));
    }

    return std::move(value);
  }
  template <typename FUN>
  static String join(const IList& entities, const Char* sep, FUN fun) {
    String value;
    IList::Iterator iter = entities.iterator();
    while (iter.hasNext()) {
      BaseEntity::SPtr entity = iter.next<BaseEntity>();
      value += format(fun(entity)) += sep;
    }

    if (!value.empty()) {
      value.erase(value.size() - strlen(sep));
    }

    return std::move(value);
  }

  template <typename T>
  static void parse(std::vector<T>& vecVal, const String& str, const Char* sep,
                    std::size_t fPos = 0, std::size_t lPos = String::npos) {
    if (fPos >= lPos || str.empty()) return;

    const std::size_t sepLen = strlen(sep);
    std::size_t idx = str.find(sep, fPos);
    while (idx != String::npos && idx < lPos) {
      vecVal.push_back(convert<T>(str.c_str(), fPos, idx));
      idx += sepLen;
      fPos = idx;
      idx = str.find(sep, idx);
    }

    if (fPos <= lPos) vecVal.push_back(convert<T>(str.c_str(), fPos, lPos));
  }
  template <typename T, typename Fun>
  static void parse(const String& str, const Char* sep, Fun fun,
                    std::size_t fPos = 0, std::size_t lPos = String::npos) {
    if (fPos >= lPos || str.empty()) return;

    const std::size_t sepLen = strlen(sep);
    std::size_t idx = str.find(sep, fPos);
    while (idx != String::npos && idx < lPos) {
      fun(convert<T>(str.c_str(), fPos, idx));
      idx += sepLen;
      fPos = idx;
      idx = str.find(sep, idx);
    }

    if (fPos <= lPos) {
      fun(convert<T>(str.c_str(), fPos, lPos));
    }
  }
  template <typename T, typename Fun>
  static void parse(const String& str, const Char* sep, Fun fun,
                    const Char* lhs, const Char* rhs) {
    std::size_t fPos = str.find(lhs);
    if (fPos != String::npos) {
      std::size_t lPos = str.find(rhs, ++fPos);
      if (lPos != String::npos) parse<T>(str, sep, fun, fPos, lPos);
    }
  }

  static String SPrintf(const Char* pFormat, ...);

  static String getField(const Object::SPtr& object, const Field& field);
  static void setField(Object::SPtr object, const Field& field,
                       const Char* value);

  static std::wstring utf8_to_unicode(const Char* src);

  static String uuid();
};

}  // namespace gemini
#endif  // GEMINI_StringUtil_INCLUDE