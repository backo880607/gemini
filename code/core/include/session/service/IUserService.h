#pragma once
#include "../../../public/service/IBaseService.h"
#include "../../../include/session/entities/User.h"

namespace gemini {

class IUserService : public IBaseService
{
public:
	virtual User::SPtr login(const String& principal, const String& password) const = 0;
};

}