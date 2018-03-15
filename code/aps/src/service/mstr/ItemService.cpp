#include "../../../include/service/mstr/ItemService.h"
#include "../../../bean/mstr/Item.h"
#include "../../../bean/tech/RouteStepIn.h"
#include "../../../bean/tech/RouteStep.h"
#include "../../../bean/tech/Route.h"

#include <algorithm>

void initAPS() {}
namespace aps {

gemini::ServiceRegister<ItemService, IItemService> item_service_register();
gemini::Boolean ItemService::calcLevel(const gemini::SmartPtr<Item>& item) const
{
	if (item->_type == ItemType::SRC_MATERIALS) {
		item->_level = 255;
	}
	else {
		gemini::UInt maxLevel = 0;
		foreach<Item, Item::routeStepIns, RouteStepIn::routeStep, RouteStep::route, Route::item>(item,
			[&maxLevel](Item::SPtr upItem) {
			maxLevel = std::max((gemini::UInt)upItem->_level, maxLevel);
		});
		item->_level = maxLevel;
	}
	return true;
}
}