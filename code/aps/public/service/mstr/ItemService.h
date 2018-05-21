#ifndef APS_ItemService_INCLUDE
#define APS_ItemService_INCLUDE
#include "service/IBaseService.h"

namespace aps
{
class Item;
class ItemService : public gemini::IBaseService
{
public:
  SERVICE_INTERFACE_METHOD(Item, calcLevel)
};
} // namespace aps

#endif // APS_ItemService_INCLUDE