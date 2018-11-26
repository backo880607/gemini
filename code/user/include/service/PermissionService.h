#ifndef GEMINI_USER_PermissionService_INCLUDE
#define GEMINI_USER_PermissionService_INCLUDE
#include "../../public/service/IPermissionService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class PermissionService : public BaseService, public IPermissionService {};

class MenuPermissionService : public PermissionService,
                              public IMenuPermissionService {};

class OperationPermissionService : public PermissionService,
                                   public IOperationPermissionService {};

class FilePermissionService : public PermissionService,
                              public IFilePermissionService {};

class ElementPermissionService : public PermissionService,
                          public IElementPermissionService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_PrivilegeService_INCLUDE