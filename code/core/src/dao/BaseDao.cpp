#include "../../public/dao/BaseDao.h"
#include "../../include/dao/DaoMgr.h"

namespace gemini {
DECLARE_CLASS_IMPL(BaseDao, Object)

namespace dao {
DaoRegister::DaoRegister(const Class &daoClass, const Class &entityClass) {
  DaoMgr::registerDao(daoClass, entityClass);
}

DaoRegister::~DaoRegister() {}

ListenerRegister::ListenerRegister(Creater creater) {
  DaoMgr::registerListener(creater);
}

ListenerRegister::~ListenerRegister() {}
}
}