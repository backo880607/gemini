#include "../../include/realm/Realm.h"

namespace gemini {
namespace user {

Boolean Realm::supports(const AuthenticationToken& token) { return true; }

}  // namespace user
}  // namespace gemini