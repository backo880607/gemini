#ifndef GEMINI_AuthenticationToken_INCLUDE
#define GEMINI_AuthenticationToken_INCLUDE
#include "../Common.h"

namespace gemini {

class CORE_API AuthenticationToken {
 public:
  AuthenticationToken(const String& principal, const String& credentials);
  virtual ~AuthenticationToken();

  Boolean getRememberMe() const { return _rememberMe; }
  void setRememberMe(Boolean bOK) { _rememberMe = bOK; }

  const String& getHost() const { return _host; }
  void setHost(const String& host) { _host = host; }

  const String& getPrincipal() const { return _principal; }
  const String& getCredentials() const { return _credentials; }

 private:
  Boolean _rememberMe;
  String _host;
  String _principal;
  String _credentials;
};

}  // namespace gemini
#endif  // GEMINI_AuthenticationToken_INCLUDE