#ifndef GEMINI_DoubleUtil_INCLUDE
#define GEMINI_DoubleUtil_INCLUDE
#include "../Common.h"

namespace gemini {

class CORE_API DoubleUtil final
{
	DoubleUtil() = delete;
	DoubleUtil(const DoubleUtil&) = delete;
	DoubleUtil& operator=(const DoubleUtil&) = delete;
public:
	static void setPrecision(Double precision);

	static Boolean isZero(Double value);
	static Boolean isZero(Double value, Double precision);

	static Boolean equal(Double lhs, Double rhs);
	static Boolean equal(Double lhs, Double rhs, Double precision);
	static Boolean notEqual(Double lhs, Double rhs) { return !DoubleUtil::equal(lhs, rhs); }
	static Boolean notEqual(Double lhs, Double rhs, Double precision) { return !DoubleUtil::equal(lhs, rhs, precision); }
	static Boolean less(Double lhs, Double rhs);
	static Boolean less(Double lhs, Double rhs, Double precision);
	static Boolean lessEqual(Double lhs, Double rhs) { return !DoubleUtil::less(rhs, lhs); }
	static Boolean lessEqual(Double lhs, Double rhs, Double precision) { return !DoubleUtil::less(rhs, lhs, precision); }
	static Boolean greater(Double lhs, Double rhs) { return DoubleUtil::less(rhs, lhs); }
	static Boolean greater(Double lhs, Double rhs, Double precision) { return DoubleUtil::less(rhs, lhs, precision); }
	static Boolean greaterEqual(Double lhs, Double rhs) { return !DoubleUtil::less(lhs, rhs); }
	static Boolean greaterEqual(Double lhs, Double rhs, Double precision) { return !DoubleUtil::less(lhs, rhs, precision); }

	//////////////////////////////////////////////////////////////////////////
	//  ���²����õ���������ʾ��С����Ϊ����0��С����������Ϊ��ֵ��������������Ϊ��ֵ

	// ���������ָ�������֣���������ǰ���֣�fraction���غ󲿷�
	static Double split(Double& fraction, Int index = 0);
	// ���index�Ժ��ֵ��ǰһλ��1
	static Double ceil(Double value, Int index = 0);
	// ���index�Ժ��ֵ
	static Double floor(Double value, Int index = 0);
	// ��index���ֵ��������
	static Double round(Double value, Int index = 0);
};

}
#endif // GEMINI_DoubleUtil_INCLUDE