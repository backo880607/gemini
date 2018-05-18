#ifndef APS_Work_INCLUDE
#define APS_Work_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Order;
class WorkIn;
class WorkOut;
class WorkRes;
class Task;
class ToolTask;
class RouteStep;
class WorkFdbk;
class APS_API Work : public gemini::EntityObject
{
	DECLARE_CLASS(Work, gemini::EntityObject)

	DECLARE_FIELD(gemini::DateTime, userEST)
	DECLARE_FIELD(gemini::DateTime, userLET)
	DECLARE_FIELD(gemini::DateTime, calcEST)
	DECLARE_FIELD(gemini::DateTime, calcLET)

	DECLARE_ENTITY(Order, order)
	DECLARE_VECTOR(WorkIn, workIns)
	DECLARE_VECTOR(WorkOut, workOuts)
	DECLARE_VECTOR(WorkRes, workReses)
	DECLARE_ENTITY(Task, task)
	DECLARE_VECTOR(ToolTask, toolTasks)
	DECLARE_ENTITY(RouteStep, routeStep)
	DECLARE_VECTOR(WorkFdbk, workFdbk)
};
} // namespace aps
#endif // !APS_Work_INCLUDE