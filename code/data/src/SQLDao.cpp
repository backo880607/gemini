#include "../include/Driver.h"
#include "../include/SQLTransmit.h"
#include "../public/SQLDao.h"
#include "../public/SQLModule.h"
#include "IApplication.h"
//#include "entities/RefVector.h"

namespace gemini {
namespace sql {

// thread_local RefVector tl_ref_dynamic;
DECLARE_CLASS_IMPL(SQLDao, BaseDao)

void SQLDao::init(std::vector<DaoListener *> &listeners) {
  _driver = afx_getSQLModule().getDriver("SQLDao");

  Connection conn = _driver->getConn();
  if (!conn.valid()) {
    return;
  }
  CreateStatement stmt(conn, getEntityClass());
  Statement createStmt = stmt.done();
  if (createStmt.valid()) {
    createStmt.execute();
    createStmt.reset();
  }

  CheckFieldStatement checkFieldStmt(conn, getEntityClass());
  checkFieldStmt.execute();

  SelectStatement selectStmt(conn, getEntityClass());
  selectStmt.execute();
}

const IList &SQLDao::select(){THROW(ClassCastException)}

BaseEntity::SPtr SQLDao::select(ID id) {
  SelectStatement selectStmt(_driver->getConn(), getEntityClass());
  return selectStmt.execute(id);
}

void SQLDao::insert(BaseEntity::SPtr entity) {
  InsertStatement stmt(_driver->getConn(), getEntityClass());
  stmt << entity;
  stmt.done().execute();
}

void SQLDao::update(BaseEntity::SPtr entity) {}

void SQLDao::erase(ID id) {
  EraseStatement stmt(_driver->getConn(), getClass());
  stmt << id;
  stmt.done().execute();
}

void SQLDao::erase(BaseEntity::SPtr entity) { erase(entity->getID()); }

void SQLDao::clear() {
  ClearStatement stmt(_driver->getConn(), getEntityClass());
  stmt.done().execute();
}

void SQLDao::insert(const std::vector<BaseEntity::SPtr> &entities) {
  InsertStatement stmt(_driver->getConn(), getEntityClass());
  const Int maxInsert = stmt.maxInsert();
  Int count = 0;
  for (BaseEntity::SPtr entity : entities) {
    stmt << entity;

    ++count;
    if (count >= maxInsert) {
      stmt.done().execute();
      stmt = InsertStatement(_driver->getConn(), getEntityClass());
      count = 0;
    }
  }
  if (count > 0) {
    stmt.done().execute();
  }
}

void SQLDao::update(const std::vector<BaseEntity::SPtr> &entities) {}

void SQLDao::erase(const std::vector<BaseEntity::SPtr> &entities) {
  EraseStatement stmt(_driver->getConn(), getClass());
  for (BaseEntity::SPtr entity : entities) {
    stmt << entity->getID();
  }
  stmt.done().execute();
}

DECLARE_CLASS_IMPL(SQLInnerDao, InnerDao)
class SQLInnerDaoListener : public DaoListener {
 public:
  SQLInnerDaoListener() : _driver(nullptr) {}
  ~SQLInnerDaoListener() {}

  virtual void startSync() override {
    getDriver();
    _stmts.reset(new SQLTransmit::data_type());
    _stmts->conn = _driver->getConn();
  }
  virtual void endSync() override { SQLTransmit::instance().push(*_stmts); }

  Connection getConn() { return _stmts->conn; }
  void push(Statement stmt) { _stmts->stmts.push_back(stmt); }

  Driver *getDriver() {
    if (_driver == nullptr) {
      _driver = afx_getSQLModule().getDriver("SQLInnerDao");
    }
    return _driver;
  }

 private:
  Driver *_driver;
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

  Connection conn = _listener->getDriver()->getConn();
  CreateStatement stmt(conn, getEntityClass());
  Statement createStmt = stmt.done();
  if (createStmt.valid()) {
    createStmt.execute();
    createStmt.reset();
  }

  CheckFieldStatement checkFieldStmt(conn, getEntityClass());
  checkFieldStmt.execute();

  SelectStatement selectStmt(conn, getEntityClass());
  selectStmt.execute();
}

void SQLInnerDao::insert(BaseEntity::SPtr entity) {
  InnerDao::insert(entity);
}

void SQLInnerDao::update(BaseEntity::SPtr entity) {
}

void SQLInnerDao::erase(ID id) {
  InnerDao::erase(id);
  std::unique_lock<std::mutex> locker(_mutex);
  _erases.insert(id);
}

void SQLInnerDao::erase(BaseEntity::SPtr entity) {
  SQLInnerDao::erase(entity->getID());
}

void SQLInnerDao::clear() {
  {
    std::unique_lock<std::mutex> locker(_mutex);
    const IList &entities = select();
    IList::Iterator iter = entities.iterator();
    while (iter.hasNext()) {
      BaseEntity::SPtr entity = iter.next<BaseEntity>();
      _erases.insert(entity->getID());
    }
  }
  InnerDao::clear();
}

thread_local SQLTransmit::data_type ttl_stmts;
void SQLInnerDao::sync() {
  LocaleSwitch locSwitch;
  THROW_IF(_listener == nullptr, Exception,
           "not found listener for SQLInnerDao")
  syncErases();
  syncModifies();
}

void SQLInnerDao::syncErases() {
  if (_erases.empty()) return;

  EraseStatement stmt(_listener->getConn(), getEntityClass());
  for (ID id : _erases) {
    stmt << id;
  }
  _listener->push(stmt.done());
}

void SQLInnerDao::syncModifies() {
  Boolean bFind = false;
  UpdateStatement stmt(_listener->getConn(), getEntityClass());
  for (entities_type::const_iterator iter = _entities.begin();
       iter != _entities.end(); ++iter) {
    if (iter->second->getModified()) {
      stmt << iter->second;
      bFind = true;
    }
  }
  if (bFind) {
    _listener->push(stmt.done());
  }
}

}  // namespace sql
}  // namespace gemini