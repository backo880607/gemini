#ifndef GEMINI_FactoryMgr_INCLUDE
#define GEMINI_FactoryMgr_INCLUDE
#include "EntityFactory.h"

namespace gemini {

class FactoryMgr final {
	FactoryMgr();
	FactoryMgr(const FactoryMgr&) {}
	FactoryMgr& operator= (const FactoryMgr&) {}
public:
	static FactoryMgr& instance() { static FactoryMgr mgr; return mgr; }

	void init();
	void unInit();

	const std::vector<EntityFactory*>& getFactories() const { return _factories; }
	EntityFactory* getFactory(const Class& cls) const;
	EntityFactory* getFactory(const String& name) const;

	template <typename FUN>
	void foreach_class(FUN fun) const {
		for (const EntityFactory* factory : _factories) {
			fun(factory->getEntityClass());
		}
	}

	const EntityFactory::Data* getRelaData(const Class& cls, Int sign) const;

private:
	std::vector<EntityFactory*> _factories;
	std::map<String, EntityFactory*> _factoryNames;
};

}
#endif // GEMINI_FactoryMgr_INCLUDE