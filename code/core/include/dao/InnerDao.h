#ifndef GEMINI_InnerDao_INCLUDE
#define GEMINI_InnerDao_INCLUDE
#include "BaseDao.h"

#include <boost/thread/shared_mutex.hpp>
#include <shared_mutex>

namespace gemini {

class InnerDao : public BaseDao {
  typedef std::map<ID, EntityObject::SPtr> entities_type;

 public:
  InnerDao();
  virtual ~InnerDao();

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

 private:
  entities_type _entities;
  boost::shared_mutex _mutex;
};

}  // namespace gemini
#endif  // GEMINI_InnerDao_INCLUDE