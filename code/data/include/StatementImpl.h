#ifndef GEMINI_SQL_StatementImpl_INCLUDE
#define GEMINI_SQL_StatementImpl_INCLUDE
#include "../public/Connection.h"

#include <mutex>
#include <sstream>

namespace gemini {
namespace sql {

class Binder;
class ResultSetImpl;
class StatementImpl {
 protected:
  StatementImpl(ConnectionImpl &conn);

 public:
  virtual ~StatementImpl();

  const SQLConfig &getConfig() const;

  virtual void reset() = 0;

  virtual StatementImpl &operator<<(const Char *value) = 0;
  virtual String toString() const = 0;

  virtual std::shared_ptr<ResultSetImpl> execute(Long &affectRows) = 0;

  virtual Binder *getBinder() {
    if (_binder == nullptr) {
      _binder = createBinder();
    }
    return _binder;
  }

  virtual String getColumnType(Types type);

  virtual String tableExisted(const String &tblName) const = 0;
  virtual Int maxInsert() const { return 1000; }

 protected:
  virtual Binder *createBinder() = 0;

 private:
  friend class Extractor;
  ConnectionImpl *_conn;
  Binder *_binder;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_StatementImpl_INCLUDE