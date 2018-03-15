#ifndef GEMINI_EntityFactory_INCLUDE
#define GEMINI_EntityFactory_INCLUDE
#include "../../public/Object.h"

namespace gemini {

class Class;
class EntityFactory final {
public:
	enum class Relation {
		OneToOne,
		OneToMulti,
		MultiToOne,
		MultiToMulti
	};
	enum class RefType {
		T_Singleton,
		T_List,
		T_Sequence,
		T_Set
	};
	struct Data {
		UInt sign;
		UInt reverseSign;
		Relation rela;
		Boolean owner;
		EntityFactory* relaFactory;
		RefType type;
		String name;
	};

	EntityFactory(const Class& cls);
	~EntityFactory();

	const Class& getEntityClass() const { return _cls; }

	EntityFactory* getSuper() const { return _super; }

	UInt getRelaSign(const String& signName) const;
	const Data* getRelaData(UInt sign) const;
	const Data* getRelaData(const String& signName) const;

	void createRelation(const EntityObject::SPtr& entity);
private:
	friend class FactoryMgr;
	const Class& _cls;
	EntityObject::SPtr _all;
	EntityFactory* _super;
	std::vector<EntityFactory*> _childs;
	std::map<UInt, Data> _relations;
};

}
#endif // GEMINI_EntityFactory_INCLUDE