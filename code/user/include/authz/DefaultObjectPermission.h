#ifndef GEMINI_USER_DefaultObjectPermission_INCLUDE
#define GEMINI_USER_DefaultObjectPermission_INCLUDE
#include "ObjectPermission.h"

namespace gemini {
namespace user {

class DefaultObjectPermission : public ObjectPermission {
 public:
  DefaultObjectPermission(const String& value);
  ~DefaultObjectPermission();

  virtual Boolean implies(const std::shared_ptr<ObjectPermission>& p);

 private:
  void setParts(const String& value);

 private:
  std::vector<std::set<String>> _parts;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DefaultObjectPermission_INCLUDE