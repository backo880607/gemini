#include "../../include/service/PermissionService.h"

namespace gemini {
namespace user {

gemini::ServiceRegister<PermissionService, IPermissionService>
    permission_service_register;

gemini::ServiceRegister<MenuPermissionService, IMenuPermissionService>
    menuPermission_service_register;

gemini::ServiceRegister<OperationPermissionService, IOperationPermissionService>
    operationPermission_service_register;

gemini::ServiceRegister<FilePermissionService, IFilePermissionService>
    filePermission_service_register;

gemini::ServiceRegister<ElementPermissionService, IElementPermissionService>
    elementPermission_service_register;

}  // namespace user
}  // namespace gemini