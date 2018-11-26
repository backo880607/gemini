#include "../../include/poco/PocoConnection.h"
#include "../../include/poco/PocoResultSet.h"
#include "../../include/poco/PocoStatement.h"
#include "../../include/poco/PocoBinder.h"

#include <Poco/Data/Statement.h>

namespace gemini {
namespace sql {

PocoStatement::PocoStatement(PocoConnection &conn)
    : StatementImpl(conn), _stmt(new Poco::Data::Statement(*conn._session)) {}

PocoStatement::~PocoStatement() {}

void PocoStatement::reset() {}

StatementImpl &PocoStatement::operator<<(const Char *value) {
  *_stmt << value;
  return *this;
}

String PocoStatement::toString() const { return _stmt->toString(); }

std::shared_ptr<ResultSetImpl> PocoStatement::execute(Long &affectRows) {
  if (_stmt == nullptr) {
    return nullptr;
  }
  try {
    affectRows = _stmt->execute(true);
  } catch (Poco::Data::DataException &exc) {
    return nullptr;
  } catch (std::exception &exc) {
    return nullptr;
  }
  return std::shared_ptr<ResultSetImpl>(new PocoResultSet(*_stmt));
}

Binder *PocoStatement::createBinder() { return new PocoBinder(_stmt); }

}  // namespace sql
}  // namespace gemini