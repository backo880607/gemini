#include "../../include/poco/PocoConnection.h"

#include <Poco/Data/Session.h>

namespace gemini {
namespace sql {

void PocoConnection::open() {
  try {
    _session = new Poco::Data::Session(connector(), connectionString(), 5);
  } catch (Poco::Data::ConnectionFailedException& exc) {
    _session = nullptr;
    //THROW(ConnectionException, exc.what())
  }
}

void PocoConnection::onClose() {
  if (_session != nullptr) {
    if (isConnected()) {
      _session->close();
    }
    delete _session;
  }
}

Boolean PocoConnection::isConnected() { return _session != nullptr && _session->isConnected(); }

Boolean PocoConnection::getAutoCommit() {
  return _session->getFeature("autoCommit");
}

void PocoConnection::setAutoCommit(Boolean autoCommit) {
  _session->setFeature("autoCommit", autoCommit);
}

void PocoConnection::begin() { _session->begin(); }

void PocoConnection::commit() { _session->commit(); }

void PocoConnection::rollback() { _session->rollback(); }

Int PocoConnection::getTransactionIsolation() {
  return _session->getTransactionIsolation();
}

void PocoConnection::setTransactionIsolation(Int level) {
  _session->setTransactionIsolation(level);
}

Boolean PocoConnection::hasTransactionIsolation(Int level) {
  return _session->hasTransactionIsolation(level);
}

Boolean PocoConnection::isTransactionIsolation(Int level) {
  return 0 != (level & getTransactionIsolation());
}

}  // namespace sql
}  // namespace gemini