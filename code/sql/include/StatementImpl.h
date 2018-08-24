#ifndef GEMINI_SQL_StatementImpl_INCLUDE
#define GEMINI_SQL_StatementImpl_INCLUDE
#include "../public/Connection.h"

#include <mutex>
#include <sstream>

namespace gemini {
namespace sql {

class MetaColumn;
class Binder;
class ResultSetImpl;
class StatementImpl {
 public:
  enum class State {
    ST_INITIALIZED,
    ST_COMPILED,
    ST_BOUND,
    ST_PAUSED,
    ST_DONE,
    ST_RESET
  };

  StatementImpl(ConnectionImpl &conn);
  virtual ~StatementImpl();

  void reset();

  State getState() const { return _state; }

  virtual std::shared_ptr<ResultSetImpl> createResultSet() const = 0;

  template <typename T>
  StatementImpl &operator<<(T value) {
    _ostr << StringUtil::format(value);
    return *this;
  }
  StatementImpl &operator<<(const Char *value) {
    _ostr << value;
    return *this;
  }
  StatementImpl &operator<<(const String &value) {
    return *this << value.c_str();
  }

  String toString() const { return _ostr.str(); }

  virtual void prepareExisted(const String &tblName) = 0;
  virtual String getColumnType(Types type);

  virtual Boolean canCompile() const = 0;
  void compile();
  virtual void execute() = 0;
  virtual Int affectedRowCount() = 0;

  virtual const MetaColumn &metaColumn(Int pos) = 0;

  virtual std::shared_ptr<Binder> getBinder() { return nullptr; }

 protected:
  virtual void resetImpl() = 0;
  virtual void compileImpl() = 0;

 private:
  State _state;
  ConnectionImpl &_conn;
  std::ostringstream _ostr;
  std::mutex _mutex;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_StatementImpl_INCLUDE