#include "../../include/dao/SessionDao.h"
#include "Session.h"

namespace gemini {
namespace user {
DECLARE_CLASS_IMPL(SessionDao, InnerDao)
DAO_GLOBAL_REGISTER(SessionDao, Session)
}  // namespace user
}  // namespace gemini