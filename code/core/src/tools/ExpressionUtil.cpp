#include "../../include/expression/Expression.h"
#include "tools/ExpressionUtil.h"

namespace gemini {

ExpressionUtil::ExpressionUtil() {}

ExpressionUtil::~ExpressionUtil() {}

std::shared_ptr<IExpression> ExpressionUtil::create(const String& str) {
  std::shared_ptr<IExpression> exp(new Expression());
  return exp->parse(str) ? exp : nullptr;
}

}  // namespace gemini