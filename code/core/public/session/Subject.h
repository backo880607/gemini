#ifndef GEMINI_Subject_INCLUDE
#define GEMINI_Subject_INCLUDE
#include "Session.h"

namespace gemini {

class AuthenticationToken;
class CORE_API Subject {
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

}  // namespace gemini
#endif  // GEMINI_Subject_INCLUDE