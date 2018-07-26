#ifndef GEMINI_ExpressionCallable_INCLUDE
#define GEMINI_ExpressionCallable_INCLUDE
#include "../../Any.h"

namespace gemini {

#if _ArgNum_ == 0
#define CONVERT_ARG0
#elif _ArgNum_ == 1
#define CONVERT_ARG1 CONVERT_ARG0 << TmplArgOV1
#elif _ArgNum_ == 2
#define CONVERT_ARG2 CONVERT_ARG1 << TmplArgOV2
#elif _ArgNum_ == 3
#define CONVERT_ARG3 CONVERT_ARG2 << TmplArgOV3
#elif _ArgNum_ == 4
#define CONVERT_ARG4 CONVERT_ARG3 << TmplArgOV4
#elif _ArgNum_ == 5
#define CONVERT_ARG5 CONVERT_ARG4 << TmplArgOV5
#elif _ArgNum_ == 6
#define CONVERT_ARG6 CONVERT_ARG5 << TmplArgOV6
#elif _ArgNum_ == 7
#define CONVERT_ARG7 CONVERT_ARG6 << TmplArgOV7
#elif _ArgNum_ == 8
#define CONVERT_ARG8 CONVERT_ARG7 << TmplArgOV8
#elif _ArgNum_ == 9
#define CONVERT_ARG9 CONVERT_ARG8 << TmplArgOV9
#elif _ArgNum_ == 10
#define CONVERT_ARG10 CONVERT_ARG9 << TmplArgOV10
#endif

#define CONVERT_ARG _YNAME_(CONVERT_ARG, _ArgNum_)

struct Callable {
  virtual Any invoke(const Method* method, const std::vector<Any>& params) = 0;
};
template <Sim_TmplArgList COMMA typename _INT = int>
struct CallableBase : public Callable {
  Any invoke(const Method* method, const std::vector<Any>& params) {
    return method->invoke(CONVERT_ARG);
  }
};

}
#endif