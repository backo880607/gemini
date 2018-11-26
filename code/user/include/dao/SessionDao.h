#ifndef GEMINI_USER_SessionDao_INCLUDE
#define GEMINI_USER_SessionDao_INCLUDE
#include "dao/InnerDao.h"

namespace gemini {
namespace user {

class SessionDao : public InnerDao {
  DECLARE_CLASS(SessionDao, InnerDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_SessionDao_INCLUDE