#include "dao/DaoMgr.h"
#include "dao/InnerDao.h"
#include "entities/FactoryMgr.h"

namespace gemini
{

DaoMgr::DaoMgr()
	: _daoes(Class::max_limits())
{
}

DaoMgr::~DaoMgr()
{
}

void DaoMgr::init()
{
	FactoryMgr::instance().foreach_class([&](const Class &cls) {
		_daoes[cls.index()] = std::shared_ptr<BaseDao>(new InnerDao());
	});
}

DaoMgr::dao_type DaoMgr::getDao(const Class &cls)
{
	if ((std::size_t)cls.index() >= _daoes.size())
	{
	}
	return _daoes[cls.index()];
}

} // namespace gemini