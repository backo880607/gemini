#ifndef GEMINI_Expression_INCLUDE
#define GEMINI_Expression_INCLUDE
#include "../../public/tools/ExpressionUtil.h"

namespace gemini {

struct Node;
class Calculate;
class Expression final : public IExpression {
 public:
  Expression();
  ~Expression();
  virtual Boolean parse(const String &str) override;

  virtual Any getValue() override;
  virtual Any getValue(const SmartPtr<BaseEntity> &entity) override;
  virtual Boolean getBoolean() override;
  virtual Boolean getBoolean(const SmartPtr<BaseEntity> &entity) override;
  virtual String getText() override;
  virtual String getText(const SmartPtr<BaseEntity> &entity) override;
  virtual const Class *getClass() override;

 private:
  Any getValue(Node *node, const SmartPtr<BaseEntity> &entity);
  Node *create(const Char *&str, Boolean bFun);
  Calculate *getNumberCalculate(const Char *&str);
  Calculate *getFunOrFieldCalculate(const Char *&str);
  void clear(Node *node);

 private:
  Boolean _hasField;
  Node *_root;
  friend class FunctionCalculate;
  friend class FieldCalculate;
  friend class BracketCalculate;
};

}  // namespace gemini
#endif  // GEMINI_Expression_INCLUDE