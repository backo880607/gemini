#ifndef GEMINI_INTEGRATION_ProjectDao_INCLUDE
#define GEMINI_INTEGRATION_ProjectDao_INCLUDE
#include "../../../data/public/SQLDao.h"

namespace gemini {
namespace integration {

class ProjectDao : public sql::SQLDao {
  DECLARE_CLASS(ProjectDao, sql::SQLDao)
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_ProjectDao_INCLUDE