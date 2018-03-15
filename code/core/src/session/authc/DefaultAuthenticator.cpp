#include "../../../include/session/authc/DefaultAuthenticator.h"
#include "../../../include/session/realm/DefaultRealm.h"

namespace gemini {

DefaultAuthenticator::DefaultAuthenticator()
{
	_realms.push_back(new DefaultRealm());
}

DefaultAuthenticator::~DefaultAuthenticator()
{
}

void DefaultAuthenticator::authenticate(const AuthenticationToken& token)
{
    for (Realm* realm : _realms) {
        if (!realm->supports(token)) {
            continue;
        }

        realm->authenticate(token);
    }
}

}