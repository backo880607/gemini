#pragma once
#include "../../../include/session/entities/User.h"
#include "../../../public/service/IBaseService.h"

namespace gemini {

class IUserService : public IBaseService {
 public:
  virtual User::SPtr login(const String& principal,
                           const String& password) const = 0;
};

}  // namespace gemini