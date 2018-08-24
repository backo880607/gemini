#ifndef APS_RouteServiceImpl_INCLUDE
#define APS_RouteServiceImpl_INCLUDE
#include "../../../public/service/tech/RouteService.h"
#include "service/BaseService.h"

namespace aps {

class RouteServiceImpl : public gemini::BaseService, public RouteService {};

}  // namespace aps
#endif  // APS_RouteServiceImpl_INCLUDE