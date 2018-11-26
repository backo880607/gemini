#include "../include/ConnectionImpl.h"
#include "../public/Connection.h"
#include "../public/Statement.h"

namespace gemini {
namespace sql {

ConnectionImpl::ConnectionImpl() : _driver(nullptr) {}

ConnectionImpl::~ConnectionImpl() {}

void ConnectionImpl::open(const SQLConfig& config) {
  _config = config;
  open();
}

void ConnectionImpl::close() {
  onClose();
}

}  // namespace sql
}  // namespace gemini