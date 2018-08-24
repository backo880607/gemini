#ifndef GEMINI_USER_DataSetService_INCLUDE
#define GEMINI_USER_DataSetService_INCLUDE
#include "../../public/service/IDataSetService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class DataSetService : public BaseService, public IDataSetService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DataSetService_INCLUDE