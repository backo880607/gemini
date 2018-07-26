#ifndef GEMINI_MsgHandler_INCLUDE
#define GEMINI_MsgHandler_INCLUDE
#include "../../public/Object.h"
#include "../../public/api/MsgData.h"

namespace gemini {

class MsgHandler {
 public:
  MsgHandler();
  virtual ~MsgHandler();

  virtual MsgData execute(const MsgData& msg);
  Boolean format(MsgData& msg, const EntityObject::SPtr& entity);

 private:
  String getValue(const EntityObject::SPtr& entity, const Field* field);
  Boolean formatJson(MsgData& msg, const EntityObject::SPtr& entity);
};

class MsgProcessHandler : public MsgHandler {
 public:
  MsgProcessHandler();
  virtual ~MsgProcessHandler();
};

class MsgRemoteHandler : public MsgHandler {
 public:
  MsgRemoteHandler();
  virtual ~MsgRemoteHandler();
};

}  // namespace gemini
#endif  // GEMINI_MsgHandler_INCLUDE
