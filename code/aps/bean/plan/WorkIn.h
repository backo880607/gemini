#ifndef APS_WorkIn_INCLUDE
#define APS_WorkIn_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class APS_API WorkIn : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(WorkIn, gemini::EntityObject)
public:
	WorkIn();
	~WorkIn();

	DECLARE_ENTITY(Work, work)
};

}
#endif // APS_WorkIn_INCLUDE
