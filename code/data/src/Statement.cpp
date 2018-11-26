#include "../include/ConnectionImpl.h"
#include "../include/Driver.h"
#include "../include/StatementImpl.h"
#include "../public/SQLModule.h"
#include "../public/Statement.h"
#include "IApplication.h"
#include "api/Handler.h"
#include "tools/ClassUtil.h"
#include "tools/File.h"

namespace gemini {
namespace sql {

Statement::Statement() {}
Statement::Statement(Connection conn) { reset(conn); }
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
  Long affectRows = 0;
  return _impl->execute(affectRows);
}

Long Statement::execute() {
  Long affectRows = 0;
  _impl->execute(affectRows);
  return affectRows;
}

Binder* Statement::getBinder() { return _impl->getBinder(); }

Boolean Statement::existed(const String& tblName) {
  *this << _impl->tableExisted(tblName);
  return execute() > 0;
}

PreparedStatement::PreparedStatement(Connection conn) { reset(conn); }

PreparedStatement::~PreparedStatement() {}

void PreparedStatement::reset(Connection conn) {}

CallableStatement::CallableStatement(Connection conn) { reset(conn); }

CallableStatement::~CallableStatement() {}

void CallableStatement::reset(Connection conn) {}

CheckDataBase::CheckDataBase() {}

CheckDataBase::~CheckDataBase() {}

void CheckDataBase::execute() {
  SQLConfig config = _config;
  config.database = "";

  Connection conn;
  conn.open(_type, config);
  if (conn.valid()) {
    Statement stmt(conn);
  }
}

std::map<const Class*, std::vector<AbstractStatement::Column>>
    AbstractStatement::s_columns;
AbstractStatement::AbstractStatement(Connection conn, const Class& cls)
    : _driver(conn.getDriver()), _stmt(conn), _cls(&cls) {}

AbstractStatement::~AbstractStatement() {}

String AbstractStatement::getTableName() {
  String tableName = afx_getSQLModule().getTableName(*_cls);
  if (tableName.empty()) {
    tableName = "T_";
    tableName.append(_cls->getName());
  }
  return tableName;
}

const std::vector<AbstractStatement::Column>& AbstractStatement::getColumns() {
  auto iter = s_columns.find(_cls);
  if (iter != s_columns.end()) {
    return iter->second;
  }
  std::vector<Column>& columns = s_columns[_cls];
  SQLModule& sqlModule = afx_getSQLModule();
  ClassUtil::foreach_fields(*_cls, [&](const Field& field) {
    if (field.getRefKind() != RefKind::None) {
      if (!getApp().isFieldStoraged(*_cls, field)) {
        return;
      }
    }
    if (sqlModule.disableColumn(*_cls, field)) {
      return;
    }
    Types type = sqlModule.getColumnType(*_cls, field);
    if (type == Types::UNKNOW) {
      switch (field.getRefKind()) {
        case RefKind::None:
          type = sqlModule.getColumnType(field.getType());
          break;
        case RefKind::Entity:
          type = Types::LONG;
          break;
        case RefKind::Vector:
        case RefKind::Sequence:
        case RefKind::Set:
          type = Types::LONGVARCHAR;
          break;
      }
    }
    Column column;
    column.field = &field;
    column.type = type;
    columns.push_back(column);
  });
  return columns;
}

SelectStatement::SelectStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls) {
  const std::vector<Column>& columns = getColumns();
  if (columns.empty()) {
    return;
  }
  _stmt << "SELECT ";
  Boolean bFind = false;
  for (Column column : columns) {
    if (bFind) {
      _stmt << ",";
    }

    if (column.field->getRefKind() != RefKind::None) {
      _stmt << column.field->getName() << "Id";
    } else {
      _stmt << column.field->getName();
    }
    bFind = true;
  }

  _stmt << " FROM ";
  _stmt << getTableName();
}

SelectStatement::~SelectStatement() {}

void SelectStatement::execute() {
  /*std::shared_ptr<io::EntityHandler> entityHandler =
      _driver->getEntityHandler(*_cls);*/
  std::vector<AbstractStatement::Column> columns = getColumns();
  ResultSet result = _stmt.query();
  if (!result.valid()) {
    return;
  }

  for (RowIterator iter = result.begin(); iter != result.end(); ++iter) {
    Row row = *iter;
    if (!row.valid()) {
      continue;
    }

    BaseEntity::SPtr entity =
        nullptr;  // entityHandler->require(row.getText("id"));
    writeEntity(row, entity);
    /*Int index = 0;
    for (AbstractStatement::Column column : columns) {
      std::shared_ptr<io::DataHandler> dataHandler =
          _driver->getDataHandler(*column.field);
      if (dataHandler == nullptr) {
        dataHandler = _driver->getDataHandler(column.field->getType());
      }

      String value = row.getText(index);
      if (dataHandler != nullptr) {
        dataHandler->write(object, column.field, value);
      } else {
        StringUtil::setField(object, *column.field, value.c_str());
      }

      ++index;
    }*/
  }
}

BaseEntity::SPtr SelectStatement::execute(ID id) {
  _stmt << "WHERE id=" << id;
  /*std::shared_ptr<io::EntityHandler> entityHandler =
      _driver->getEntityHandler(*_cls);*/
  ResultSet result = _stmt.query();
  if (!result.valid()) {
    return nullptr;
  }
  Row row = *result.begin();
  if (!row.valid()) {
    return nullptr;
  }

  BaseEntity::SPtr entity = nullptr;
  // entityHandler->createTemp(row.get<ID>("id"));
  writeEntity(row, entity);
  return entity;
}

Statement SelectStatement::done() { return _stmt; }

void SelectStatement::writeEntity(Row row, BaseEntity::SPtr entity) {
  std::vector<AbstractStatement::Column> columns = getColumns();
  Int index = 0;
  for (AbstractStatement::Column column : columns) {
    std::shared_ptr<api::DataHandler> dataHandler =
        _driver->getDataHandler(*column.field);
    if (dataHandler == nullptr) {
      dataHandler = _driver->getDataHandler(column.field->getType());
    }

    String value = row.getText(index);
    if (dataHandler != nullptr) {
      dataHandler->write(entity, column.field, value);
    } else {
      StringUtil::setField(entity, *column.field, value.c_str());
    }

    ++index;
  }
}

EraseStatement::EraseStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls), _bHasData(false) {
  _stmt << "DELETE FROM " << getTableName() << " WHERE ";
}

EraseStatement::~EraseStatement() {}

EraseStatement& EraseStatement::operator<<(ID id) {
  if (_bHasData) {
    _stmt << " or ";
  }
  _stmt << "id=" << id;
  _bHasData = true;
  return *this;
}

Statement EraseStatement::done() {
  _bHasData = false;
  return _stmt;
}

InsertStatement::InsertStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls), _bHasData(false) {
  const std::vector<Column>& columns = getColumns();
  if (columns.empty()) {
    return;
  }
  _stmt << "INSERT INTO " << getTableName() << " (";

  Boolean bFind = false;
  for (Column column : columns) {
    if (bFind) {
      _stmt << ",";
    }

    if (column.field->getRefKind() != RefKind::None) {
      _stmt << column.field->getName() << "Id";
    } else {
      _stmt << column.field->getName();
    }
    bFind = true;
  }
  _stmt << ") VALUES ";
}

InsertStatement::~InsertStatement() {}

Int InsertStatement::maxInsert() const { return _stmt._impl->maxInsert(); }

InsertStatement& InsertStatement::operator<<(SmartPtr<BaseEntity> entity) {
  const std::vector<Column>& columns = getColumns();
  if (columns.empty()) {
    return *this;
  }
  if (_bHasData) {
    _stmt << ",";
  }
  _stmt << "(";
  Boolean bFind = false;
  for (Column column : columns) {
    if (bFind) {
      _stmt << ",";
    }

    std::shared_ptr<api::DataHandler> dataHandler =
        _driver->getDataHandler(*column.field);
    if (dataHandler == nullptr) {
      dataHandler = _driver->getDataHandler(column.field->getType());
    }

    if (dataHandler != nullptr) {
      _stmt << dataHandler->read(entity, column.field);
    } else {
      _stmt << StringUtil::getField(entity, *column.field).c_str();
    }
    bFind = true;
  }
  _stmt << ")";
  _bHasData = true;
  return *this;
}

Statement InsertStatement::done() {
  _bHasData = false;
  return _stmt;
}

UpdateStatement::UpdateStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls) {}

UpdateStatement::~UpdateStatement() {}

UpdateStatement& UpdateStatement::operator<<(SmartPtr<BaseEntity> entity) {
  return *this;
}

Statement UpdateStatement::done() { return _stmt; }

ClearStatement::ClearStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls) {
  _stmt << "TRUNCATE TABLE " << getTableName();
}

ClearStatement::~ClearStatement() {}

Statement ClearStatement::done() { return _stmt; }

CreateStatement::CreateStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls) {}

CreateStatement::~CreateStatement() {}

Statement CreateStatement::done() {
  String tableName = getTableName();
  if (_stmt.existed(tableName)) {
    return Statement();
  }
  _stmt.reset();
  _stmt << "CREATE TABLE " << tableName << " (";
  std::vector<Column> columns = getColumns();
  for (Column column : columns) {
    if (column.field->getRefKind() != RefKind::None) {
      _stmt << column.field->getName() << "Id"
            << " ";
    } else {
      _stmt << column.field->getName() << " ";
    }

    _stmt << _stmt._impl->getColumnType(column.type) << ",";
  }
  _stmt << "PRIMARY KEY (id)";
  _stmt << ")";
  return _stmt;
}

CheckFieldStatement::CheckFieldStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls) {}

CheckFieldStatement::~CheckFieldStatement() {}

void CheckFieldStatement::execute() {
  _stmt << "SELECT * FROM " << getTableName();
  ResultSet result = _stmt.query();
  if (!result.valid()) {
    return;
  }
  std::vector<Column> columns = getColumns();
  std::map<String, Column> innerFields;
  for (Column column : columns) {
    innerFields.insert(std::make_pair(column.field->getName(), column));
  }
  const Int columnCount = result.columnCount();
  for (Int i = 0; i < columnCount; ++i) {
    String columnName = result.columnName(i);
    if (ClassUtil::hasField(*_cls, columnName)) {
      innerFields.erase(columnName);
    } else {
    }
  }

  if (innerFields.empty()) {
    return;
  }

  Boolean bFind = false;
  _stmt.reset();
  _stmt << "ALTER TABLE " << getTableName() << " ADD ";
  for (auto iter = innerFields.begin(); iter != innerFields.end(); ++iter) {
    if (bFind) {
      _stmt << ",";
    }
    Column column = iter->second;
    if (column.field->getRefKind() != RefKind::None) {
      _stmt << column.field->getName() << "Id"
            << " ";
    } else {
      _stmt << column.field->getName() << " ";
    }

    _stmt << _stmt._impl->getColumnType(column.type);
    bFind = true;
  }
  _stmt.execute();
}

Statement CheckFieldStatement::done() { return _stmt; }

BulkStatement::BulkStatement(Connection conn, const Class& cls)
    : AbstractStatement(conn, cls) {
  _file.reset(new File(getPath().c_str()));
  _file->open();
}

BulkStatement::~BulkStatement() {}

BulkStatement& BulkStatement::operator<<(SmartPtr<BaseEntity> entity) {
  Boolean bFind = false;

  std::vector<Column> columns = getColumns();
  for (Column column : columns) {
    if (bFind) {
      _file->write("\t");
    }

    std::shared_ptr<api::DataHandler> dataHandler =
        _driver->getDataHandler(*column.field);
    if (dataHandler == nullptr) {
      dataHandler = _driver->getDataHandler(column.field->getType());
    }

    if (dataHandler != nullptr) {
      _file->write(dataHandler->read(entity, column.field));
    } else {
      _file->write(StringUtil::getField(entity, *column.field).c_str());
    }
    bFind = true;
  }
  _file->write("\n");
  return *this;
}

Statement BulkStatement::done() {
  _file->flush();
  String sql = "load data infile '";
  StringUtil::append(sql, _file->getFilePath().string(),
                     "' replace into table ", getTableName());
  /*_stmt << "load data infile '" << _file->getFilePath().string()
        << "' replace into table " << getTableName();*/
  _stmt << sql;
  return _stmt;
}

String BulkStatement::getPath() {
  FilePath filePath(getApp().getTempPath());
  filePath.append("sql");
  if (!filePath.isExist()) {
    filePath.createDirectories();
  }
  filePath.append("locale");
  if (!filePath.isExist()) {
    filePath.createDirectories();
  }
  filePath.append(_cls->getName().c_str());
  return filePath.string();
}

}  // namespace sql
}  // namespace gemini