#ifndef GEMINI_DefaultAuthorizer_INCLUDE
#define GEMINI_DefaultAuthorizer_INCLUDE
#include "Authorizer.h"

namespace gemini {

class Realm;
class DefaultAuthorizer : public Authorizer
{
public:
	DefaultAuthorizer();
	~DefaultAuthorizer();

    virtual Boolean isPermitted(const String& principal, const String& permission) override;
private:
	std::vector<std::shared_ptr<Realm>> _realms;
};

}
#endif // GEMINI_DefaultAuthorizer_INCLUDE