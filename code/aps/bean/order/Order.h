#ifndef APS_Order_INCLUDE
#define APS_Order_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Work;
class Item;
class APS_API Order : public gemini::EntityObject
{
	DECLARE_CLASS(Order, gemini::EntityObject)

	DECLARE_FIELD(gemini::String, code)  ///< 订单代码
	DECLARE_FIELD(gemini::Double, qty)   ///< 数量
	DECLARE_FIELD(gemini::DateTime, let) ///< 最晚结束时刻

	DECLARE_ENTITY(Item, item) ///< 物品
	DECLARE_VECTOR(Work, works)
};
} // namespace aps
#endif // !APS_Order_INCLUDE