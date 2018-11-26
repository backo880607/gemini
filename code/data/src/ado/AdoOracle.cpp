#include "../../include/ado/AdoOracle.h"

namespace gemini {
namespace sql {

AdoOracle::AdoOracle() {}

AdoOracle::~AdoOracle() {}

String AdoOracle::connectionString() const { return "OraOLEDB.Oracle.1"; }

}  // namespace sql
}  // namespace gemini