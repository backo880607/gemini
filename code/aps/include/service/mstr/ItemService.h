#ifndef APS_ItemService_INCLUDE
#define APS_ItemService_INCLUDE
#include "../../../public/service/mstr/IItemService.h"
#include "service\BaseService.h"

namespace aps {

class ItemService : public gemini::BaseService, IItemService
{
public:
	//virtual gemini::Boolean calcLevel(const gemini::SmartPtr<Item>& item) const override;
	SERVICE_METHOD(Item, calcLevel)
};

}

#endif // APS_ItemService_INCLUDE
