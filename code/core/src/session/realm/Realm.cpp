#include "../../../include/session/realm/Realm.h"

namespace gemini {

Boolean Realm::supports(const AuthenticationToken& token)
{
    return true;
}

}