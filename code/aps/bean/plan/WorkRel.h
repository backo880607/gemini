#ifndef APS_WorkRel_INCLUDE
#define APS_WorkRel_INCLUDE
#include "../../common/Export.h"

namespace aps {
	
class Work;
class APS_API WorkRel : public gemini::EntityObject
{
	DECLARE_CLASS(WorkRel, gemini::EntityObject)
public:
	WorkRel();
	~WorkRel();
};
}
#endif // APS_WorkRel_INCLUDE
