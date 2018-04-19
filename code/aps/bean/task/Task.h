#ifndef APS_Task_Include
#define APS_Task_Include
#include "../../common/Export.h"

namespace aps {

class Work;
class Resource;
class APS_API Task : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(Task, gemini::EntityObject)
public:
	Task();
	~Task();

	DECLARE_FIELD(gemini::DateTime, boundary)
	DECLARE_FIELD(gemini::DateTime, prevSetStart)
	DECLARE_FIELD(gemini::Duration, prevSetTime)
	DECLARE_FIELD(gemini::DateTime, prevSetEnd)
	DECLARE_FIELD(gemini::DateTime, prodStart)
	DECLARE_FIELD(gemini::Duration, prodTime)
	DECLARE_FIELD(gemini::DateTime, prodEnd)
	DECLARE_FIELD(gemini::DateTime, lockedStart)
	DECLARE_FIELD(gemini::Duration, lockedTime)
	DECLARE_FIELD(gemini::DateTime, lockedEnd)
	DECLARE_FIELD(gemini::DateTime, nextSetStart)
	DECLARE_FIELD(gemini::Duration, nextSetTime)
	DECLARE_FIELD(gemini::DateTime, nextSetEnd)

	DECLARE_ENTITY(Work, work)
	DECLARE_ENTITY(Resource, res)
	DECLARE_ENTITY(WorkRes, workRes)
	DECLARE_VECTOR(Task, prevTask)
	DECLARE_VECTOR(Task, nextTask)
};

}

#endif // APS_Task_Include
