#ifndef GEMINI_ExpressionUtil_INCLUDE
#define GEMINI_ExpressionUtil_INCLUDE
#include "../Any.h"

namespace gemini {

class IExpression {
 public:
  virtual Boolean parse(const String& str) = 0;
  virtual Any getValue() = 0;
  virtual Any getValue(const SmartPtr<BaseEntity>& entity) = 0;
  virtual Boolean getBoolean() = 0;
  virtual Boolean getBoolean(const SmartPtr<BaseEntity>& entity) = 0;
  virtual String getText() = 0;
  virtual String getText(const SmartPtr<BaseEntity>& entity) = 0;
  virtual const Class* getClass() = 0;
};

class CORE_API ExpressionUtil final {
  ExpressionUtil();

 public:
  ~ExpressionUtil();

  static std::shared_ptr<IExpression> create(const String& str);
};

}  // namespace gemini
#endif  // !GEMINI_ExpressionUtil_INCLUDE