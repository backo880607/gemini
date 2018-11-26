#ifndef GEMINI_INTEGRATION_SchemeDao_INCLUDE
#define GEMINI_INTEGRATION_SchemeDao_INCLUDE
#include "../../../data/public/SQLDao.h"

namespace gemini {
namespace integration {

class SchemeDao : public sql::SQLDao {
  DECLARE_CLASS(SchemeDao, sql::SQLDao)
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_SchemeDao_INCLUDE