#ifndef APS_EPlan_INCLUDE
#define APS_EPlan_INCLUDE
#include "../../common/Export.h"

namespace aps {

DEFINE_ENUM(PlanStatus, UNPLANNED, PLANNED, INDICATIONDONE, CONFIRM,
            STARTPRODUCT, FINISH)
DEFINE_ENUM(WorkType, FICTITIOUS, NORMAL, REPAIR)
DEFINE_ENUM(WorkRelType, INNERORDER, OUTERORDER)

}  // namespace aps
#endif  // APS_EPlan_INCLUDE