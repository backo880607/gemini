#include "../../../bean/mstr/Shift.h"
#include "../../../include/service/mstr/ShiftServiceImpl.h"

namespace aps {
gemini::ServiceRegister<ShiftServiceImpl, ShiftService> shift_service_register;
}  // namespace aps