#include "../../include/service/DataSetService.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<DataSetService, IDataSetService>
    dataSet_service_register;
}
}  // namespace gemini