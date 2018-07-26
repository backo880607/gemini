#ifndef GEMINI_BaseDao_INCLUDE
#define GEMINI_BaseDao_INCLUDE
#include "../../public/Object.h"

namespace gemini {

class CORE_API BaseDao : noncopyable {
 protected:
  BaseDao() {}

 public:
  virtual ~BaseDao() {}

  virtual const IList &select() = 0;
  virtual EntityObject::SPtr select(ID id) = 0;
  virtual void insert(EntityObject::SPtr entity) = 0;
  virtual void update(EntityObject::SPtr entity) = 0;
  virtual void erase(ID id) = 0;
  virtual void erase(EntityObject::SPtr entity) = 0;
  virtual void clear() = 0;

  virtual void insert(const std::vector<EntityObject::SPtr> &entities) = 0;
  virtual void update(const std::vector<EntityObject::SPtr> &entities) = 0;
  virtual void erase(const std::vector<EntityObject::SPtr> &entities) = 0;

  virtual void sync() {}
};

}  // namespace gemini
#endif  // GEMINI_BaseDao_INCLUDE