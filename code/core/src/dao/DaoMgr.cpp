#include "dao/DaoMgr.h"
#include "dao/InnerDao.h"
#include "entities/FactoryMgr.h"

namespace gemini {

std::map<const Class *, const Class *> DaoMgr::s_daoInfos;
std::map<const Class *, const Class *> DaoMgr::s_globalDaoInfos;
std::map<const Class *, DaoMgr::dao_type> DaoMgr::_globalDaoes;
std::vector<DaoMgr::FunCreateListener> DaoMgr::s_listenerInfos;
DaoMgr::DaoMgr() : _daoes(Class::max_limits()) {}

DaoMgr::~DaoMgr() {
  for (DaoListener *listener : _listeners) {
    delete listener;
  }
}

void DaoMgr::init() {
  FactoryMgr::instance().foreach_class([&](const Class &cls) {
    if (DaoMgr::_globalDaoes.find(&cls) != DaoMgr::_globalDaoes.end()) {
      return;
	}
    std::shared_ptr<BaseDao> baseDao;
    auto iter = s_daoInfos.find(&cls);
    if (iter == s_daoInfos.end()) {
      baseDao.reset(new InnerDao());
    } else {
      baseDao.reset((BaseDao *)iter->second->newInstance());
    }
    baseDao->_entityCls = &cls;
    _daoes[cls.index()] = baseDao;
  });

  for (FunCreateListener info : s_listenerInfos) {
    _listeners.push_back((*info)());
  }
  for (dao_type dao : _daoes) {
    if (!dao) continue;
    dao->init(_listeners);
  }
}

DaoMgr::dao_type DaoMgr::getDao(const Class &cls) {
  if ((std::size_t)cls.index() >= _daoes.size()) {
  }
  return _daoes[cls.index()];
}

DaoMgr::dao_type DaoMgr::getGlobalDao(const Class &cls) {
  auto iter = _globalDaoes.find(&cls);
  return iter != _globalDaoes.end() ? iter->second : nullptr;
}

void DaoMgr::registerDao(const Class &daoClass, const Class &entityClass) {
  s_daoInfos.insert(std::make_pair(&entityClass, &daoClass));
}

void DaoMgr::registerGlobalDao(const Class &daoClass,
                               const Class &entityClass) {
  s_globalDaoInfos.insert(std::make_pair(&entityClass, &daoClass));
  std::shared_ptr<BaseDao> baseDao((BaseDao*)daoClass.newInstance());
  baseDao->_entityCls = &entityClass;
  _globalDaoes[&entityClass] = baseDao;
}

void DaoMgr::startSync() {
  for (DaoListener *listener : _listeners) {
    listener->startSync();
  }
}

void DaoMgr::endSync() {
  for (DaoListener *listener : _listeners) {
    listener->endSync();
  }
}

}  // namespace gemini