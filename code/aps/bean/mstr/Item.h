#ifndef APS_Item_INCLUDE
#define APS_Item_INCLUDE
#include "../../common/Export.h"
#include "../../public/enums/mstr/ItemType.h"

namespace aps {

class Order;
class Route;
class RouteStepIn;
class RouteStepOut;
class APS_API Item : public gemini::EntityObject {
#define MODULE_API APS_API
	DECLARE_CLASS(Item, gemini::EntityObject)

	DECLARE_FIELD(gemini::String, code)
	DECLARE_FIELD(ItemType, type)
	DECLARE_FIELD(gemini::Int, level)
	DECLARE_FIELD(gemini::Int, priority)
	DECLARE_FIELD(gemini::String, purLT)
	DECLARE_FIELD(gemini::String, manufLT)
	DECLARE_FIELD(gemini::String, shipmentLT)
	DECLARE_FIELD(gemini::Int, unitPur)
	DECLARE_FIELD(gemini::Int, unitManuf)
	DECLARE_FIELD(gemini::Int, unitShipments)
	DECLARE_FIELD(gemini::Boolean, active)

	DECLARE_VECTOR(Order, orders)
	DECLARE_VECTOR(Route, routes)
	DECLARE_VECTOR(RouteStepIn, routeStepIns)
	DECLARE_VECTOR(RouteStepOut, routeStepOuts)
};

}
#endif // APS_Item_INCLUDE