#ifndef APS_WorkRel_INCLUDE
#define APS_WorkRel_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Work;
class APS_API WorkRel : public gemini::EntityObject
{
	DECLARE_CLASS(WorkRel, gemini::EntityObject)

	DECLARE_FIELD(ContinuousType, contType)
	DECLARE_FIELD(gemini::String, minTimeCSTR)
	DECLARE_FIELD(gemini::String, maxTimeCSTR)
};
} // namespace aps
#endif // !APS_WorkRel_INCLUDE
