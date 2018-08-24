#include "..\include\ConnectionImpl.h"

namespace gemini {
namespace sql {

Boolean ConnectionImpl::open(const SQLConfig &config) {
  _config = config;
  return open();
}

Boolean ConnectionImpl::isTransactionIsolation(Int level) {
  return 0 != (level & getTransactionIsolation());
}

}  // namespace sql
}  // namespace gemini