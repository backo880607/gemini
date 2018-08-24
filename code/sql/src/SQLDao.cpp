#include "../include/Driver.h"
#include "../include/SQLTransmit.h"
#include "../public/SQLDao.h"
#include "../public/SQLModule.h"
//#include "entities/RefVector.h"

namespace gemini {
namespace sql {

// thread_local RefVector tl_ref_dynamic;
DECLARE_CLASS_IMPL(SQLDao, BaseDao)

void SQLDao::init(std::vector<DaoListener *> &listeners) {
  _driver = afx_getSQLModule().getDriver("SQLDao");
}

const IList &SQLDao::select(){THROW(ClassCastException)}

EntityObject::SPtr SQLDao::select(ID id) {
  return nullptr;
}

void SQLDao::insert(EntityObject::SPtr entity) {}

void SQLDao::update(EntityObject::SPtr entity) {}

void SQLDao::erase(ID id) {
  EraseStatement stmt(_driver->getConn(), getClass());
  stmt << id;
  stmt.done().execute();
}

void SQLDao::erase(EntityObject::SPtr entity) {}

void SQLDao::clear() {}

void SQLDao::insert(const std::vector<EntityObject::SPtr> &entities) {}

void SQLDao::update(const std::vector<EntityObject::SPtr> &entities) {}

void SQLDao::erase(const std::vector<EntityObject::SPtr> &entities) {}

DECLARE_CLASS_IMPL(SQLInnerDao, InnerDao)
class SQLInnerDaoListener : public DaoListener {
 public:
  SQLInnerDaoListener() {}
  ~SQLInnerDaoListener() {}

  virtual void startSync() override {
    if (_driver == nullptr) {
      _driver = afx_getSQLModule().getDriver("SQLInnerDao");
    }
    _stmts.reset(new SQLTransmit::data_type());
    _stmts->conn = _driver->getConn();
  }
  virtual void endSync() override { SQLTransmit::instance().push(*_stmts); }

  Connection getConn() { return _stmts->conn; }
  void push(Statement stmt) { _stmts->stmts.push_back(stmt); }

  std::shared_ptr<Driver> getDriver() {
    if (_driver == nullptr) {
      _driver = afx_getSQLModule().getDriver("SQLInnerDao");
    }
    return _driver;
  }

 private:
  std::shared_ptr<Driver> _driver;
  typedef std::shared_ptr<SQLTransmit::data_type> stmts_type;
  stmts_type _stmts;
};
DAO_LISTENER_REGISTER(SQLInnerDaoListener)

void SQLInnerDao::init(std::vector<DaoListener *> &listeners) {
  _listener = nullptr;
  for (DaoListener *listener : listeners) {
    if (typeid(SQLInnerDaoListener) == typeid(*listener)) {
      _listener = (SQLInnerDaoListener *)listener;
      break;
    }
  }

  CreateStatement stmt(_listener->getDriver()->getConn(), getEntityClass());
  stmt.done().execute();
}

void SQLInnerDao::insert(EntityObject::SPtr entity) {
  InnerDao::insert(entity);
  entity->getFlag().created = true;
}

void SQLInnerDao::update(EntityObject::SPtr entity) {
  entity->getFlag().modified = true;
}

void SQLInnerDao::erase(ID id) {
  InnerDao::erase(id);
  std::unique_lock<std::mutex> locker(_mutex);
  _erases.insert(id);
}

void SQLInnerDao::erase(EntityObject::SPtr entity) {
  SQLInnerDao::erase(entity->getID());
}

void SQLInnerDao::clear() {
  {
    std::unique_lock<std::mutex> locker(_mutex);
    const IList &entities = select();
    IList::Iterator iter = entities.iterator();
    while (iter.hasNext()) {
      EntityObject::SPtr entity = iter.next<EntityObject>();
      _erases.insert(entity->getID());
    }
  }
  InnerDao::clear();
}

thread_local SQLTransmit::data_type ttl_stmts;
void SQLInnerDao::sync() {
  THROW_IF(_listener == nullptr, Exception,
           "not found listener for SQLInnerDao")
  syncErases();
  syncUpdates();
  syncInserts();
}

void SQLInnerDao::syncErases() {
  if (_erases.empty()) return;

  EraseStatement stmt(_listener->getConn(), getClass());
  for (ID id : _erases) {
    stmt << id;
  }
  _listener->push(stmt.done());
}

void SQLInnerDao::syncUpdates() {
  UpdateStatement stmt(_listener->getConn(), getClass());
  for (entities_type::const_iterator iter = _entities.begin();
       iter != _entities.end(); ++iter) {
    EntityObject::Flag flag = iter->second->getFlag();
    if (!flag.created && flag.modified) {
      stmt << iter->second;
    }
  }
  _listener->push(stmt.done());
}

void SQLInnerDao::syncInserts() {
  InsertStatement stmt(_listener->getConn(), getClass());
  for (entities_type::const_iterator iter = _entities.begin();
       iter != _entities.end(); ++iter) {
    if (iter->second->getFlag().created) {
      stmt << iter->second;
    }
  }
  _listener->push(stmt.done());
}

}  // namespace sql
}  // namespace gemini