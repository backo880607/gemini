#ifndef GEMINI_SQL_SQLDao_INCLUDE
#define GEMINI_SQL_SQLDao_INCLUDE
#include "../public/Connection.h"
#include "dao/InnerDao.h"

namespace gemini {
namespace sql {

class Driver;
class GEMINI_SQL_API SQLDao : public BaseDao {
  DECLARE_ABSTRACT_CLASS(SQLDao, BaseDao)

  virtual void init(std::vector<DaoListener *> &listeners) override;

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
  std::shared_ptr<Driver> _driver;
};

class SQLInnerDaoListener;
class GEMINI_SQL_API SQLInnerDao : public InnerDao {
  DECLARE_ABSTRACT_CLASS(SQLInnerDao, InnerDao)

  virtual void init(std::vector<DaoListener *> &listeners) override;

  virtual void insert(EntityObject::SPtr entity) override;
  virtual void update(EntityObject::SPtr entity) override;
  virtual void erase(ID id) override;
  virtual void erase(EntityObject::SPtr entity) override;
  virtual void clear() override;

  virtual void sync() override;

 private:
  void syncErases();
  void syncUpdates();
  void syncInserts();

 private:
  SQLInnerDaoListener *_listener;
  std::set<ID> _erases;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLDao_INCLUDE