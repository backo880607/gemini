#ifndef GEMINI_SQL_ODBCStatement_INCLUDE
#define GEMINI_SQL_ODBCStatement_INCLUDE
#include "../StatementImpl.h"
#include "ODBCBinder.h"

namespace gemini {
namespace sql {

class ODBCStatement : public StatementImpl {
 public:
  ODBCStatement(ConnectionImpl& conn);
  ~ODBCStatement();

  virtual std::shared_ptr<ResultSetImpl> createResultSet() const override;

  virtual Boolean canCompile() const override { return _canCompile; }
  virtual void execute() override;

  virtual void prepareExisted(const String& tblName) override;

  virtual const MetaColumn& metaColumn(Int pos);

  virtual std::shared_ptr<Binder> getBinder();

 protected:
  virtual void resetImpl() override;
  virtual void compileImpl() override;
  virtual Int affectedRowCount() override;

 private:
  Boolean _canCompile;
  SQLHDBC _hdbc;
  SQLHSTMT _hstmt;
  std::vector<std::shared_ptr<MetaColumn>> _metaColumns;
  std::shared_ptr<ODBCBinder> _binder;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_ODBCStatement_INCLUDE