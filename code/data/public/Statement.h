#ifndef GEMINI_SQL_Statement_INCLUDE
#define GEMINI_SQL_Statement_INCLUDE
#include "Binder.h"
#include "Connection.h"
#include "ResultSet.h"

namespace gemini {
class File;
namespace sql {

class MetaColumn;
class StatementImpl;
class GEMINI_SQL_API Statement {
  typedef std::shared_ptr<StatementImpl> impl_type;

 public:
  Statement();
  Statement(Connection conn);
  ~Statement();

  Boolean valid() const { return _impl != nullptr; }

  void reset();
  void reset(Connection conn);

  Statement& operator<<(const Char* str);
  Statement& operator<<(const String& str) { return *this << str.c_str(); }
  template <typename T>
  Statement& operator<<(const T& val) {
    return *this << StringUtil::format(val);
  }

  ResultSet query();
  Long execute();

  Boolean existed(const String& tblName);

  template <typename T>
  Statement& bind(T& value) {
    getBinder()->bind(value, Binder::Direction::PD_IN_OUT);
    return *this;
  }
  template <typename T>
  Statement& in(T& value) {
    getBinder()->bind(value, Binder::Direction::PD_IN);
    return *this;
  }
  template <typename T>
  Statement& out(T& value) {
    getBinder()->bind(value, Binder::Direction::PD_OUT);
    return *this;
  }

 protected:
  Binder* getBinder();

 private:
  friend class ResultSet;
  friend class CreateStatement;
  friend class InsertStatement;
  friend class SelectStatement;
  friend class CheckFieldStatement;
  impl_type _impl;
};

class PreparedStatementImpl;
class GEMINI_SQL_API PreparedStatement {
  typedef std::shared_ptr<PreparedStatementImpl> impl_type;

 public:
  PreparedStatement(Connection conn);
  ~PreparedStatement();

  void reset(Connection conn);

 private:
  impl_type _impl;
};

class CallableStatementImpl;
class GEMINI_SQL_API CallableStatement {
  typedef std::shared_ptr<CallableStatementImpl> impl_type;

 public:
  CallableStatement(Connection conn);
  ~CallableStatement();

  void reset(Connection conn);

 private:
  impl_type _impl;
};

class CheckDataBase {
 public:
  CheckDataBase();
  virtual ~CheckDataBase();

  void setSQLType(SQL_TYPE type) { _type = type; }
  void setSQLConfig(const SQLConfig& config) { _config = config; }

  virtual void execute();

 protected:
  SQL_TYPE _type;
  SQLConfig _config;
};

class GEMINI_SQL_API AbstractStatement {
 public:
  struct Column {
    const Field* field;
    Types type;
  };

 public:
  AbstractStatement(Connection conn, const Class& cls);
  virtual ~AbstractStatement();

  String getTableName();
  const std::vector<Column>& getColumns();

 protected:
  Driver* _driver;
  Statement _stmt;
  const Class* _cls;

 private:
  static std::map<const Class*, std::vector<Column>> s_columns;
};

class GEMINI_SQL_API SelectStatement : public AbstractStatement {
 public:
  SelectStatement(Connection conn, const Class& cls);
  ~SelectStatement();

  void execute();
  BaseEntity::SPtr execute(ID id);

  Statement done();

 private:
  void writeEntity(Row row, BaseEntity::SPtr entity);
};

class GEMINI_SQL_API EraseStatement : public AbstractStatement {
 public:
  EraseStatement(Connection conn, const Class& cls);
  ~EraseStatement();

  EraseStatement& operator<<(ID id);

  Statement done();

 private:
  Boolean _bHasData;
};

class GEMINI_SQL_API InsertStatement : public AbstractStatement {
 public:
  InsertStatement(Connection conn, const Class& cls);
  ~InsertStatement();

  Int maxInsert() const;
  InsertStatement& operator<<(SmartPtr<BaseEntity> entity);

  Statement done();

 private:
  Boolean _bHasData;
};

class GEMINI_SQL_API UpdateStatement : public AbstractStatement {
 public:
  UpdateStatement(Connection conn, const Class& cls);
  ~UpdateStatement();

  UpdateStatement& operator<<(SmartPtr<BaseEntity> entity);

  Statement done();
};

class GEMINI_SQL_API ClearStatement : public AbstractStatement {
 public:
  ClearStatement(Connection conn, const Class& cls);
  ~ClearStatement();

  Statement done();
};

class GEMINI_SQL_API CreateStatement : public AbstractStatement {
 public:
  CreateStatement(Connection conn, const Class& cls);
  ~CreateStatement();

  Statement done();
};

class GEMINI_SQL_API CheckFieldStatement : public AbstractStatement {
 public:
  CheckFieldStatement(Connection conn, const Class& cls);
  ~CheckFieldStatement();

  void execute();

  Statement done();
};

class GEMINI_SQL_API BulkStatement : public AbstractStatement {
 public:
  BulkStatement(Connection conn, const Class& cls);
  ~BulkStatement();

  BulkStatement& operator<<(SmartPtr<BaseEntity> entity);

  Statement done();

 private:
  String getPath();

 private:
  std::shared_ptr<File> _file;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Statement_INCLUDE