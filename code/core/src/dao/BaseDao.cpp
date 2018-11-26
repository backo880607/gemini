#include "../../include/dao/DaoMgr.h"
#include "../../include/dao/DaoUtil.h"
#include "../../public/dao/BaseDao.h"

namespace gemini {
DECLARE_CLASS_IMPL(BaseDao, Object)
BaseEntity::SPtr BaseDao::createEntity(const Class &cls, ID id) {
  return DaoUtil::create(cls, id);
}

namespace dao {
DaoRegister::DaoRegister(const Class &daoClass, const Class &entityClass,
                         Boolean global /* = false */) {
  if (global) {
    DaoMgr::registerGlobalDao(daoClass, entityClass);
  } else {
    DaoMgr::registerDao(daoClass, entityClass);
  }
}

DaoRegister::~DaoRegister() {}

ListenerRegister::ListenerRegister(Creater creater) {
  DaoMgr::registerListener(creater);
}

ListenerRegister::~ListenerRegister() {}
}  // namespace dao
}  // namespace gemini