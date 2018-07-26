#ifndef GEMINI_MultiEnum_INCLUDE
#define GEMINI_MultiEnum_INCLUDE
#include "Any.h"

namespace gemini {

class CORE_API MultiEnum : public AnyAbstract {
 protected:
  MultiEnum(Int value);

 public:
  MultiEnum();
  ~MultiEnum() {}

  Boolean contains(Int value);
  Boolean contains(const MultiEnum& rhs);

  void operator+=(Int rhs);
  void operator+=(const MultiEnum& rhs);
  void operator-=(Int rhs);
  void operator-=(const MultiEnum& rhs);
  Boolean operator==(const MultiEnum& rhs);

  virtual void operator+=(const Any& rhs);
  virtual void operator-=(const Any& rhs);
  virtual Boolean operator==(const Any& rhs) const;
  virtual String str() const;

 protected:
  Int add(const Any& rhs) const;
  Int sub(const Any& rhs) const;
  static Int valudOfImpl(const Char* str);

 private:
  Int _value;
};

#define DEFINE_MULTI_ENUM(enum_type, ...)                     \
  \
class enum_type final : public gemini::MultiEnum {            \
  \
public:                                                       \
    enum value_type { __VA_ARGS__ };                          \
    \
enum_type() {}                                                \
    \
enum_type(value_type value)                                   \
        : gemini::MultiEnum((gemini::Int)value){};            \
    \
~enum_type() {}                                               \
    \
virtual gemini::Any                                           \
    operator+(const gemini::Any& rhs) const {                 \
      return enum_type((value_type)add(rhs));                 \
    \
}                                                        \
    \
virtual gemini::Any                                           \
    operator-(const gemini::Any& rhs) const {                 \
      return enum_type((value_type)sub(rhs));                 \
    \
}                                                        \
    \
static enum_type                                              \
    valueOf(const gemini::Char* str) {                        \
      return (value_type)gemini::MultiEnum::valudOfImpl(str); \
    \
}                                                        \
  \
};                                                            \
  \
const gemini::Char gemini_enum_##enum_type[] = #__VA_ARGS__;

#define DEFINE_MULTI_ENUM_IMPL(enum_type)                                 \
  const gemini::EnumHelper::Register<enum_type> geminiAfxEnum##enum_type( \
      gemini_enum_##enum_type);

}  // namespace gemini
#endif  // GEMINI_MultiEnum_INCLUDE