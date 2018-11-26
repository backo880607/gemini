#ifndef GEMINI_USER_IPermissionService_INCLUDE
#define GEMINI_USER_IPermissionService_INCLUDE

namespace gemini {
namespace user {

class IPermissionService {};

class IMenuPermissionService : public IPermissionService {};

class IOperationPermissionService : public IPermissionService {};

class IFilePermissionService : public IPermissionService {};

class IElementPermissionService : public IPermissionService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_IPermissionService_INCLUDE