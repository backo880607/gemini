#ifndef GEMINI_SESSION_Errors_INCLUDE
#define GEMINI_SESSION_Errors_INCLUDE
#include "../../public/message/Exception.h"

namespace gemini {

class AccountError : public log_info {
 public:
  virtual String getName() override { return u8"Account"; }
};

class ExpiredCredentialsError : public log_info {
 public:
  virtual String getName() override { return u8"ExpiredCredentials"; }
};

class LockedAccountError : public log_info {
 public:
  virtual String getName() override { return u8"LockedAccount"; }
};

}  // namespace gemini
#endif  // GEMINI_SESSION_Errors_INCLUDE