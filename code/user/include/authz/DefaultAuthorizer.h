#ifndef GEMINI_USER_DefaultAuthorizer_INCLUDE
#define GEMINI_USER_DefaultAuthorizer_INCLUDE
#include "Authorizer.h"

namespace gemini {
namespace user {

class Realm;
class DefaultAuthorizer : public Authorizer {
 public:
  DefaultAuthorizer();
  ~DefaultAuthorizer();

  virtual Boolean isPermitted(const String& principal,
                              const String& permission) override;

 private:
  std::vector<std::shared_ptr<Realm>> _realms;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DefaultAuthorizer_INCLUDE