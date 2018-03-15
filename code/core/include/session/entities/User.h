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
public:
	User() {}
	~User() {}

	DECLARE_FIELD(Boolean, blocked)
	DECLARE_FIELD(String, name)
	DECLARE_FIELD(String, nickName)
	DECLARE_FIELD(String, password)
	DECLARE_FIELD(String, salt)
};

}
#endif // GEMINI_User_INCLUDE

