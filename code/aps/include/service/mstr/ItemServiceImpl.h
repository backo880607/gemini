#ifndef APS_ItemServiceImpl_INCLUDE
#define APS_ItemServiceImpl_INCLUDE
#include "../../../public/service/mstr/ItemService.h"
#include "service/BaseService.h"

namespace aps
{
class ItemServiceImpl : public gemini::BaseService, ItemService
{
public:
  SERVICE_METHOD(Item, calcLevel)
};
} // namespace aps

#endif // APS_ItemServiceImpl_INCLUDE