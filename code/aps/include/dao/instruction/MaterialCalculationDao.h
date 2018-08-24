#ifndef APS_MaterialCalculationDao_INCLUDE
#define APS_MaterialCalculationDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class MaterialCalculationDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(MaterialCalculationDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_MaterialCalculationDao_INCLUDE