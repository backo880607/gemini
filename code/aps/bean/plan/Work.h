#ifndef APS_Work_INCLUDE
#define APS_Work_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Order;
class WorkIn;
class WorkOut;
class WorkRes;
class APS_API Work : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(Work, gemini::EntityObject)
public:
	Work();
	~Work();

	DECLARE_ENTITY(Order, order)
	DECLARE_VECTOR(WorkIn, workIns)
	DECLARE_VECTOR(WorkOut, workOuts)
	DECLARE_VECTOR(WorkRes, workReses);
};

}
#endif // APS_Work_INCLUDE