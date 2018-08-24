#include <boost/test/unit_test.hpp>

#include "aps/public/service/mstr/ItemService.h"

#include "ServerUtil.h"

BOOST_AUTO_TEST_CASE(t_test_http) {
  // gemini::ServerUtil::startHTTPServer();
  gemini::ServiceHelper<aps::ItemService> itemService;
  if (itemService) {
    itemService->test();
  }
}