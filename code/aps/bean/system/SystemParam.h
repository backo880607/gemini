#ifndef APS_SystemParam_INCLUDE
#define APS_SystemParam_INCLUDE
#include "../../common/Export.h"

namespace aps {
    
class APS_API SystemParam : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(SystemParam, gemini::EntityObject)
public:
	SystemParam();
	~SystemParam();

    DECLARE_FIELD(gemini::DateTime, baseTime)

};

}

#endif // APS_SystemParam_INCLUDE