#ifndef APS_IItemService_INCLUDE
#define APS_IItemService_INCLUDE
#include "service\IBaseService.h"

namespace aps {

class Item;
class IItemService : public gemini::IBaseService
{
public:
	virtual gemini::Boolean calcLevel(const gemini::SmartPtr<Item>& item) const = 0;
};

}
#endif // APS_IItemService_INCLUDE
