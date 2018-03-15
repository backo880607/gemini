#include <boost/test/unit_test.hpp>

#include "Any.h"

struct ddddData : public gemini::AnyAbstract {
	ddddData() {}
	ddddData(int v, double d) : value(v), vvvvv(d) {}
	int value;
	double vvvvv;
};

gemini::Any getData(){
	return ddddData{10, 2.3};
}

BOOST_AUTO_TEST_CASE(t_test_any)
{
	using namespace gemini;
	Any value;
	value = nullptr;
	value = 1;
	UInt dddd = 2;
	value = dddd;

	value = getData();

	UInt result = value.cast<UInt>();

	ddddData exVal;
	exVal.vvvvv = 2.2;
	value = exVal;
}