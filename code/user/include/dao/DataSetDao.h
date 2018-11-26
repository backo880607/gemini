#ifndef GEMINI_USER_DataSetDao_INCLUDE
#define GEMINI_USER_DataSetDao_INCLUDE
#include "../../../data/public/SQLDao.h"

namespace gemini {
namespace user {

class DataSetDao : public sql::SQLDao {
  DECLARE_CLASS(DataSetDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DataSetDao_INCLUDE