#ifndef GEMINI_USER_Subject_INCLUDE
#define GEMINI_USER_Subject_INCLUDE
#include "Session.h"
#include "UserExport.h"

namespace gemini {
namespace user {

class AuthenticationToken;
class GEMINI_USER_API Subject {
 public:
  Subject();
  ~Subject();

  static const Subject& get();

  Boolean isAuthenticated() const;

  void login(const AuthenticationToken& token) const;
  void logout() const;

  Boolean isPermitted(const Char* permission) const;

  Session::SPtr getSession() const { return _session; }

 private:
  Session::SPtr _session;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Subject_INCLUDE