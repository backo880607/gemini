#ifndef GEMINI_USER_Errors_INCLUDE
#define GEMINI_USER_Errors_INCLUDE
#include "message/Exception.h"

namespace gemini {
namespace user {

class AccountError : public log_info {
  virtual String getName() override { return "Account"; }
};
class ExpiredCredentialsError : public log_info {
  virtual String getName() override { return "ExpiredCredentials"; }
};
class LockedAccountError : public log_info {
  virtual String getName() override { return "LockedAccount"; }
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Errors_INCLUDE