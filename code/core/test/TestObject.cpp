#include <boost/test/unit_test.hpp>

#include "base/Root.h"
#include "bean/plan/Work.h"
#include "bean/order/Order.h"
#include "bean/mstr/Item.h"
#include "bean/tech/Route.h"
#include "bean/tech/RouteStep.h"

template<typename... A> class BMW {};
template<typename Head, typename... Tail>
class BMW<Head, Tail...> : public BMW<Tail...>
{
public:
	typedef typename BMW<Tail...>::value_type value_type;
	static void collect(std::vector<gemini::UInt>& vals) {
		vals.push_back(Head::index());
		BMW<Tail...>::collect(vals);
	}
};
template<typename Tail> class BMW<Tail> {
public:
	typedef typename Tail value_type;
	static void collect(std::vector<gemini::UInt>& vals) {
		vals.push_back(Tail::index());
	}
};
template<> class BMW<> {};  // ±ß½çÌõ¼þ

BOOST_AUTO_TEST_CASE(t_test_string_property)
{
	using namespace gemini;
	using namespace aps;
	const Class& workCls = Work::getClassStatic();
	Work* work = (Work*)workCls.newInstance();

	UInt index = Order::item::index();
	index = Order::works::index();

	std::vector<UInt> indexs;
	BMW<Item::routes, Route::routeSteps>::collect(indexs);
}

#include "aes.h"
BOOST_AUTO_TEST_CASE(t_test_string_aes)
{


}