#ifndef GEMINI_SQL_Statement_INCLUDE
#define GEMINI_SQL_Statement_INCLUDE
#include "../include/Binder.h"
#include "../include/Extractor.h"
#include "Connection.h"
#include "ResultSet.h"

namespace gemini {
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
  Int execute(Boolean reset = true);
  Int executeAsync(Boolean reset = true);

  const MetaColumn& metaColumn(Int pos);

  Boolean initialized();
  Boolean paused();
  Boolean done();

  Boolean existed(const String& tblName);

  template <typename T>
  Statement& bind(T& value) {
    getBinder()->bind(_binderPos++, value, Binder::Direction::PD_IN_OUT);
    return *this;
  }
  template <typename T>
  Statement& in(T& value) {
    getBinder()->bind(_binderPos++, value, Binder::Direction::PD_IN);
    return *this;
  }
  template <typename T>
  Statement& out(T& value) {
    getBinder()->bind(_binderPos++, value, Binder::Direction::PD_OUT);
    return *this;
  }

  template <typename T>
  Boolean into(T& value) {
    return getExtractor()->extract(_extractorPos, value);
  }

 protected:
  std::shared_ptr<Binder> getBinder();
  std::shared_ptr<Extractor> getExtractor();

 private:
  friend class ResultSet;
  friend class CreateStatement;
  impl_type _impl;
  Int _binderPos;
  Int _extractorPos;
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

class GEMINI_SQL_API EraseStatement {
 public:
  EraseStatement(Connection conn, const Class& cls);
  ~EraseStatement();

  EraseStatement& operator<<(ID id) {
    _ids.push_back(id);
    return *this;
  }

  Statement done();

 private:
  Statement _stmt;
  const Class& _cls;
  std::vector<ID> _ids;
};

class GEMINI_SQL_API InsertStatement {
 public:
  InsertStatement(Connection conn, const Class& cls);
  ~InsertStatement();

  InsertStatement& operator<<(SmartPtr<EntityObject> entity);

  Statement done();

 private:
  Statement _stmt;
  const Class& _cls;
};

class GEMINI_SQL_API UpdateStatement {
 public:
  UpdateStatement(Connection conn, const Class& cls);
  ~UpdateStatement();

  UpdateStatement& operator<<(SmartPtr<EntityObject> entity);

  Statement done();

 private:
  Statement _stmt;
  const Class& _cls;
};

class GEMINI_SQL_API CreateStatement {
 public:
  CreateStatement(Connection conn, const Class& cls);
  ~CreateStatement();

  Statement done();

 private:
  Statement _stmt;
  const Class& _cls;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Statement_INCLUDE