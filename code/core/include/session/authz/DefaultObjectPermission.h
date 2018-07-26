#ifndef GEMINI_DefaultObjectPermission_INCLUDE
#define GEMINI_DefaultObjectPermission_INCLUDE
#include "ObjectPermission.h"

namespace gemini {

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

}  // namespace gemini
#endif  // GEMINI_DefaultObjectPermission_INCLUDE
