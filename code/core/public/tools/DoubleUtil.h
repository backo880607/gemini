#ifndef GEMINI_DoubleUtil_INCLUDE
#define GEMINI_DoubleUtil_INCLUDE
#include "../Common.h"

namespace gemini {

class CORE_API DoubleUtil final {
  DoubleUtil() = delete;
  DoubleUtil(const DoubleUtil&) = delete;
  DoubleUtil& operator=(const DoubleUtil&) = delete;

 public:
  static void setPrecision(Double precision);

  static Boolean isZero(Double value);
  static Boolean isZero(Double value, Double precision);

  static Boolean equal(Double lhs, Double rhs);
  static Boolean equal(Double lhs, Double rhs, Double precision);
  static Boolean notEqual(Double lhs, Double rhs) {
    return !DoubleUtil::equal(lhs, rhs);
  }
  static Boolean notEqual(Double lhs, Double rhs, Double precision) {
    return !DoubleUtil::equal(lhs, rhs, precision);
  }
  static Boolean less(Double lhs, Double rhs);
  static Boolean less(Double lhs, Double rhs, Double precision);
  static Boolean lessEqual(Double lhs, Double rhs) {
    return !DoubleUtil::less(rhs, lhs);
  }
  static Boolean lessEqual(Double lhs, Double rhs, Double precision) {
    return !DoubleUtil::less(rhs, lhs, precision);
  }
  static Boolean greater(Double lhs, Double rhs) {
    return DoubleUtil::less(rhs, lhs);
  }
  static Boolean greater(Double lhs, Double rhs, Double precision) {
    return DoubleUtil::less(rhs, lhs, precision);
  }
  static Boolean greaterEqual(Double lhs, Double rhs) {
    return !DoubleUtil::less(lhs, rhs);
  }
  static Boolean greaterEqual(Double lhs, Double rhs, Double precision) {
    return !DoubleUtil::less(lhs, rhs, precision);
  }

  //////////////////////////////////////////////////////////////////////////
  //  以下部分用到的索引表示：小数点为索引0，小数部分索引为负值，整数部分索引为正值

  // 将浮点数分割成两部分，函数返回前部分，fraction返回后部分
  static Double split(Double& fraction, Int index = 0);
  // 舍掉index以后的值，前一位加1
  static Double ceil(Double value, Int index = 0);
  // 舍掉index以后的值
  static Double floor(Double value, Int index = 0);
  // 对index后的值四舍五入
  static Double round(Double value, Int index = 0);
};

}  // namespace gemini
#endif  // GEMINI_DoubleUtil_INCLUDE