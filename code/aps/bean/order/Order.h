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

	DECLARE_ENTITY(Item, item)
	DECLARE_VECTOR(Work, works)
};
} // namespace aps
#endif // !APS_Order_INCLUDE