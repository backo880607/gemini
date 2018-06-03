#include "../../../include/service/mstr/ItemServiceImpl.h"
#include "../../../bean/mstr/Item.h"
#include "../../../bean/tech/RouteStepIn.h"
#include "../../../bean/tech/RouteStep.h"
#include "../../../bean/tech/Route.h"

#include <algorithm>

void initAPS() {}
namespace aps
{
gemini::ServiceRegister<ItemServiceImpl, ItemService> item_service_register();
gemini::Boolean ItemServiceImpl::calcLevel(const gemini::SmartPtr<Item> &item) const
{
	if (item->_type == ItemType::SRC_MATERIALS)
	{
		item->_level = 255;
	}
	else
	{
		gemini::Int maxLevel = 0;
		foreach
			<Item, Item::routeStepIns, RouteStepIn::routeStep, RouteStep::route, Route::item>(item,
																							  [&maxLevel](Item::SPtr upItem) {
																								  maxLevel = std::max((gemini::Int)upItem->_level, maxLevel);
																							  });
		item->_level = maxLevel;
	}
	return true;
}
} // namespace aps