#pragma once
#include "../../../public/service/BaseService.h"
#include "IPermissionService.h"

namespace gemini {

class PermissionService : public BaseService, IPermissionService {};

}  // namespace gemini