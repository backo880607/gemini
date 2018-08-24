#ifndef GEMINI_SESSION_Errors_INCLUDE
#define GEMINI_SESSION_Errors_INCLUDE
#include "../../public/message/Exception.h"

namespace gemini {

class AccountError : public log_info {
  virtual String getName() override { return "Account"; }
};
class ExpiredCredentialsError : public log_info {
  virtual String getName() override { return "ExpiredCredentials"; }
};
class LockedAccountError : public log_info {
  virtual String getName() override { return "LockedAccount"; }
};

}  // namespace gemini
#endif  // GEMINI_SESSION_Errors_INCLUDE