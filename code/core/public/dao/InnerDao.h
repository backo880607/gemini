#ifndef GEMINI_InnerDao_INCLUDE
#define GEMINI_InnerDao_INCLUDE
#include "BaseDao.h"

#include <mutex>

namespace gemini {

class CORE_API InnerDao : public BaseDao {
  DECLARE_CLASS(InnerDao, BaseDao)

  virtual const IList &select() override;
  virtual EntityObject::SPtr select(ID id) override;
  virtual void insert(EntityObject::SPtr entity) override;
  virtual void update(EntityObject::SPtr entity) override;
  virtual void erase(ID id) override;
  virtual void erase(EntityObject::SPtr entity) override;
  virtual void clear() override;

  virtual void insert(const std::vector<EntityObject::SPtr> &entities) override;
  virtual void update(const std::vector<EntityObject::SPtr> &entities) override;
  virtual void erase(const std::vector<EntityObject::SPtr> &entities) override;

 protected:
  friend class DaoMgr;
  typedef std::map<ID, EntityObject::SPtr> entities_type;
  entities_type _entities;
  std::mutex _mutex;
};

}  // namespace gemini
#endif  // GEMINI_InnerDao_INCLUDE