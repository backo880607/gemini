#include <boost/test/unit_test.hpp>

#include "ServerUtil.h"

BOOST_AUTO_TEST_CASE(t_test_http)
{
	gemini::ServerUtil::startHTTPServer();
}