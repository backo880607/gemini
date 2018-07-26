#ifndef GEMINI_User_INCLUDE
#define GEMINI_User_INCLUDE
#include "../../../public/Object.h"

namespace gemini {

/**
 * @brief
 *
 */
class User : public EntityObject {
  DECLARE_CLASS(User, EntityObject)

  DECLARE_FIELD(Boolean, blocked)
  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, nickName)
  DECLARE_FIELD(String, password)
  DECLARE_FIELD(String, salt)
  DECLARE_FIELD(String, mobile)
  DECLARE_FIELD(String, email)
  DECLARE_FIELD(DateTime, loginTime)
  DECLARE_FIELD(DateTime, logoutTime)
  DECLARE_FIELD(Int, loginCount)
};

}  // namespace gemini
#endif  // GEMINI_User_INCLUDE