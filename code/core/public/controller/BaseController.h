#ifndef GEMINI_BaseController_INCLUDE
#define GEMINI_BaseController_INCLUDE
#include "../Object.h"

namespace gemini {

class CORE_API DtoBase : public Object {
 public:
  DtoBase() {}
  virtual ~DtoBase() {}

  static const gemini::Class& getClassStatic() { return _class; }
  virtual const gemini::Class& getClass() const { return _class; }

 private:
  static const Class _class;
};

class CORE_API BaseController : public Object, public EntityHelper {
  DECLARE_CLASS(BaseController, Object)
};

namespace exp {
class CORE_API RegisterFunction {
 public:
  RegisterFunction(const Class& cls, const String& methodName);
  ~RegisterFunction();
};
class CORE_API RegisterReturn {
 public:
  RegisterReturn(const String& methodName, Int index);
  ~RegisterReturn();
};
class CORE_API RegisterArgs {
 public:
  RegisterArgs(const String& methodName, const String& args);
  ~RegisterArgs();
};
}  // namespace exp

#define CONTROLLER_METHOD(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD(RETURN_TYPE, METHOD_NAME, METHOD_ARGS)

#define EXPRESSION_RETURN(METHOD_NAME, ARG_INDEX)                        \
  gemini::exp::RegisterReturn gemini_afx_expression_return(#METHOD_NAME, \
                                                           ARG_INDEX);

#define EXPRESSION_ARGS(METHOD_NAME, METHOD_ARGS)                    \
  gemini::exp::RegisterArgs gemini_afx_expression_args(#METHOD_NAME, \
                                                       #METHOD_ARGS);

#define EXPRESSION_REGISTER(CLASS_NAME, METHOD_NAME)            \
  gemini::exp::RegisterFunction gemini_afx_expression_function( \
      CLASS_NAME::getClassStatic(), #METHOD_NAME);

}  // namespace gemini
#endif  // GEMINI_BaseController_INCLUDE