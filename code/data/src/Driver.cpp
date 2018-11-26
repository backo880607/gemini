#include "../include/ConnectionImpl.h"
#include "../include/Driver.h"
#include "IApplication.h"
#include "tools/File.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace sql {

SQLStringHandler::SQLStringHandler() {}

SQLStringHandler::~SQLStringHandler() {}

String SQLStringHandler::read(Object::SPtr entity, const Field* field) {
  String value = "'";
  value += StringUtil::getField(entity, *field) += "'";
  return value;
}

void SQLStringHandler::write(Object::SPtr entity, const Field* field,
                             const String& value) {}

/*SQLEntityHandler::SQLEntityHandler(const Class& cls) : io::EntityHandler(cls)
{}

SQLEntityHandler::~SQLEntityHandler() {}

EntityObject::SPtr SQLEntityHandler::get(const String& primary) { return
nullptr; }

EntityObject::SPtr SQLEntityHandler::require(const String& primary) {
  const ID id = StringUtil::convert<ID>(primary.c_str());
  return createTemp(id);
}*/

Driver::Driver() : _shutdown(false), _curConns(0) {
  _config.maxTotal = 1;
  _config.autoCreate = true;
  _config.connectionTimeout = 3;
  registerDataHandler(
      Class::forType<String>(),
      std::shared_ptr<api::DataHandler>(new SQLStringHandler()));
}

Driver::~Driver() { shutdown(); }

Connection Driver::getConn() {
  std::unique_lock<std::mutex> locker(_mutex);
  THROW_IF(_shutdown, AccessException, "Session pool has been shut down.")

  if (_idleConns.empty()) {
    THROW_IF(_curConns >= _config.maxTotal, AccessException,
             "Session pool has been full.")

    Connection conn;
    conn.open(_type, _config);
    if (conn.valid()) {
      conn.setDriver(this);
      _activeConns.push_back(conn._impl);
      ++_curConns;
    }
    return conn;
  }

  Connection conn;
  conn._impl = _idleConns.back();
  _idleConns.pop_back();
  _activeConns.push_back(conn._impl);
  return conn;
}

void Driver::setType(const String& type) {
  if (StringUtil::icompare(type.c_str(), "SQLite") == 0) {
    _type = SQL_TYPE::SQLite;
  } else if (StringUtil::icompare(type.c_str(), "MySQL") == 0) {
    _type = SQL_TYPE::MySQL;
  } else if (StringUtil::icompare(type.c_str(), "Oracle") == 0) {
    _type = SQL_TYPE::Oracle;
  } else if (StringUtil::icompare(type.c_str(), "SQLServer") == 0) {
    _type = SQL_TYPE::SQLServer;
  } else if (StringUtil::icompare(type.c_str(), "Access") == 0) {
    _type = SQL_TYPE::Access;
  } else if (StringUtil::icompare(type.c_str(), "Excel") == 0) {
    _type = SQL_TYPE::Excel;
  }
}

void Driver::changeDataBase() {
  if (!_config.autoCreate) {
    return;
  }
  CheckDatabase check;
  check.execute(_type, _config);
}

void Driver::registerDataHandler(const Class& cls, data_handler handler) {
  auto iter = _clsHandlers.find(&cls);
  THROW_IF(iter != _clsHandlers.end(), RegisterException, cls.getName(),
           " has registed")
  _clsHandlers.insert(std::make_pair(&cls, handler));
}

void Driver::registerDataHandler(const Class& cls, const Field& field,
                                 data_handler handler) {
  std::map<const Field*, data_handler>& handlers = _fieldHandlers[&cls];
  if (handlers.empty()) {
    THROW_IF(handlers.find(&field) != handlers.end(), RegisterException,
             "the field ", field.getName(), " of ", cls.getName(),
             " has registed")

    handlers.insert(std::make_pair(&field, handler));
  }
}

Driver::data_handler Driver::getDataHandler(const Class& cls) {
  auto iter = _clsHandlers.find(&cls);
  return iter != _clsHandlers.end() ? iter->second : nullptr;
}

Driver::data_handler Driver::getDataHandler(const Field& field) {
  auto iter = _fieldHandlers.find(&field.getClass());
  if (iter == _fieldHandlers.end()) {
    return nullptr;
  }
  auto iterField = iter->second.find(&field);
  return iterField != iter->second.end() ? iterField->second : nullptr;
}

/*void Driver::registerEntityHandler(const Class& cls, entity_handler handler) {
  auto iter = _entityHandlers.find(&cls);
  THROW_IF(iter != _entityHandlers.end(), RegisterException, cls.getName(),
           " has registed")
  _entityHandlers.insert(std::make_pair(&cls, handler));
}

Driver::entity_handler Driver::getEntityHandler(const Class& cls) {
  auto iter = _entityHandlers.find(&cls);
  if (iter != _entityHandlers.end()) {
    return iter->second;
  }
  return entity_handler(new io::IDEntityHandler(cls));
}*/

void Driver::shutdown() {
  std::lock_guard<std::mutex> locker(_mutex);
  if (_shutdown) return;
  _shutdown = true;
  for (std::shared_ptr<ConnectionImpl> idleConn : _idleConns) {
    try {
      idleConn->close();
    } catch (...) {
    }
  }
  _idleConns.clear();
  _curConns = 0;
}

void Driver::pushBack(std::shared_ptr<ConnectionImpl>& conn) {
  std::lock_guard<std::mutex> locker(_mutex);
  if (_shutdown) return;
  for (auto iter = _activeConns.begin(); iter != _activeConns.end(); ++iter) {
    if ((*iter).lock() == conn) {
      _idleConns.push_back((*iter).lock());
      _activeConns.erase(iter);
      break;
    }
  }
}

void Driver::purgeDeadSessions() {
  std::lock_guard<std::mutex> locker(_mutex);
  if (_shutdown) return;

  for (auto iter = _idleConns.begin(); iter != _idleConns.end();) {
    if ((*iter)->isConnected()) {
      ++iter;
    } else {
      iter = _idleConns.erase(iter);
      --_curConns;
    }
  }
}

}  // namespace sql
}  // namespace gemini