#include "cache/CacheMgr.h"
#include "cache/InnerCacheDao.h"
#include "entities/FactoryMgr.h"

namespace gemini {

CacheMgr::CacheMgr()
	: _daoes(Class::max_limits())
{

}

CacheMgr::~CacheMgr()
{

}

void CacheMgr::init()
{
	FactoryMgr::instance().foreach_class([&](const Class &cls) {
		_daoes[cls.index()] = std::shared_ptr<CacheDao>(new InnerCacheDao());
	});
}

CacheMgr::dao_type CacheMgr::getDao(const Class& cls)
{
	if ((std::size_t)cls.index() >= _daoes.size()) {
		
	}
	return _daoes[cls.index()];
}

}