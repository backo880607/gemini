#pragma once
#include "../include/ConnectionImpl.h"
#include "../include/StatementImpl.h"
#include "../public/SQLModule.h"
#include "../public/Statement.h"

namespace gemini {
namespace sql {

Statement::Statement() : _binderPos(0), _extractorPos(0) {}
Statement::Statement(Connection conn) : _binderPos(0), _extractorPos(0) {
  reset(conn);
}
Statement::~Statement() {}

void Statement::reset() {
  if (_impl != nullptr) {
    _impl->reset();
  }
}

void Statement::reset(Connection conn) {
  if (conn.isConnected()) {
    _impl = conn._impl->createStatement();
  }
}

Statement& Statement::operator<<(const Char* str) {
  *_impl << str;
  return *this;
}

ResultSet Statement::query() {
  execute();
  return this;
}

Int Statement::execute(Boolean reset /* = true */) {
  Boolean isDone = done();
  if (initialized() || paused() || isDone) {
    if (isDone) _impl->reset();

    do {
      _impl->compile();
    } while (_impl->canCompile());

    _impl->execute();
    return _impl->affectedRowCount();
  }
  return -1;
}

Int Statement::executeAsync(Boolean reset /* = true */) { return -1; }

Boolean Statement::initialized() {
  return _impl->getState() == StatementImpl::State::ST_INITIALIZED;
}

Boolean Statement::paused() {
  return _impl->getState() == StatementImpl::State::ST_PAUSED;
}

Boolean Statement::done() {
  return _impl->getState() == StatementImpl::State::ST_DONE;
}

const MetaColumn& Statement::metaColumn(Int pos) {
  return _impl->metaColumn(pos);
}

std::shared_ptr<Binder> Statement::getBinder() { return _impl->getBinder(); }
std::shared_ptr<Extractor> Statement::getExtractor() {
  return _impl->getExtractor();
}

Boolean Statement::existed(const String& tblName) {
  _impl->prepareExisted(tblName);
  ResultSet result = query();
  Int count = 0;
  into(count);
  ++result.begin();
  return count > 0;
}

PreparedStatement::PreparedStatement(Connection conn) { reset(conn); }

PreparedStatement::~PreparedStatement() {}

void PreparedStatement::reset(Connection conn) {}

CallableStatement::CallableStatement(Connection conn) { reset(conn); }

CallableStatement::~CallableStatement() {}

void CallableStatement::reset(Connection conn) {}

EraseStatement::EraseStatement(Connection conn, const Class& cls)
    : _stmt(conn), _cls(cls) {}

EraseStatement::~EraseStatement() {}

Statement EraseStatement::done() { return _stmt; }

InsertStatement::InsertStatement(Connection conn, const Class& cls)
    : _stmt(conn), _cls(cls) {}

InsertStatement::~InsertStatement() {}

InsertStatement& InsertStatement::operator<<(SmartPtr<EntityObject> entity) {
  return *this;
}

Statement InsertStatement::done() { return _stmt; }

UpdateStatement::UpdateStatement(Connection conn, const Class& cls)
    : _stmt(conn), _cls(cls) {}

UpdateStatement::~UpdateStatement() {}

UpdateStatement& UpdateStatement::operator<<(SmartPtr<EntityObject> entity) {
  return *this;
}

Statement UpdateStatement::done() { return _stmt; }

CreateStatement::CreateStatement(Connection conn, const Class& cls)
    : _stmt(conn), _cls(cls) {}

CreateStatement::~CreateStatement() {}

Statement CreateStatement::done() {
  String tblName = "T_";
  tblName.append(_cls.getName());
  if (_stmt.existed(tblName)) {
    return Statement();
  }
  _stmt.reset();
  const Class& entityCls = Class::forName("EntityObject");
  SQLModule& sqlModule = afx_getSQLModule();
  _stmt << "CREATE TABLE " << tblName << " (";

  const Class* cls = &_cls;
  do {
    cls->foreach_fields([&](const Field& field) {
      if (field.getType().isBase(entityCls)) {
        return;
      }
      _stmt << field.getName() << " ";
      Types type = sqlModule.getColumnType(*cls, field.index());
      if (type == Types::UNKNOW) {
        type = sqlModule.getColumnType(field.getType());
      }
      _stmt << _stmt._impl->getColumnType(type) << ",";
    });
    if (cls->hasSuper()) {
      cls = &cls->getSuperClass();
    } else {
      cls = nullptr;
    }
  } while (cls != nullptr);

  _stmt << "PRIMARY KEY (id)";
  _stmt << ")";
  return _stmt;
}

}  // namespace sql
}  // namespace gemini