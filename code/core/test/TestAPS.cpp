#include <boost/test/unit_test.hpp>
#include "aps/bean/mstr/Item.h"
#include "aps/public/service/mstr/IItemService.h"

#include <iostream>
#include "InitApplication.h"
BOOST_FIXTURE_TEST_SUITE(s_test_aps, InitApplication)

BOOST_AUTO_TEST_CASE(t_test_aps)
{
	try {
		gemini::ServiceHelper<aps::IItemService> itemService;
		aps::Item::SPtr item;
		item->getID();
		item->_level;
		itemService->calcLevel(item);
	} catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
		BOOST_FAIL("ÖÂÃü´íÎó£¬²âÊÔÖÕÖ¹");
	}
}

BOOST_AUTO_TEST_SUITE_END()