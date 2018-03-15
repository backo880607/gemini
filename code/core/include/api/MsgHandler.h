#ifndef GEMINI_MsgHandler_INCLUDE
#define GEMINI_MsgHandler_INCLUDE
#include "../../public/api/MsgData.h"
#include "../../public/Object.h"

namespace gemini {

class MsgHandler
{
public:
	Boolean format(MsgData& msg, const EntityObject::SPtr& entity);

private:
	String getValue(const EntityObject::SPtr& entity, const Field* field);
	Boolean formatJson(MsgData& msg, const EntityObject::SPtr& entity);
};

}
#endif // GEMINI_MsgHandler_INCLUDE
