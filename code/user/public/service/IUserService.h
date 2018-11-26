#ifndef GEMINI_USER_IUserService_INCLUDE
#define GEMINI_USER_IUserService_INCLUDE
#include "service/IBaseService.h"
#include "../../bean/User.h"

namespace gemini {
namespace user {

class IUserService {
 public:
  virtual User::SPtr login(const String& principal,
                           const String& password) const = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_IUserService_INCLUDE