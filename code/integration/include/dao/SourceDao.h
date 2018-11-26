#ifndef GEMINI_INTEGRATION_SourceDao_INCLUDE
#define GEMINI_INTEGRATION_SourceDao_INCLUDE
#include "../../../data/public/SQLDao.h"

namespace gemini {
namespace integration {

class SourceDao : public sql::SQLDao {
  DECLARE_CLASS(SourceDao, sql::SQLDao)
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_SourceDao_INCLUDE