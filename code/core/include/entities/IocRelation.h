#ifndef GEMINI_IocRelation_INCLUDE
#define GEMINI_IocRelation_INCLUDE
#include "../../public/Object.h"
#include "RefVector.h"

namespace gemini {

class IocRelation final
{
	static EntityObject::SPtr getImpl(EntityObject::SPtr entity,
		std::vector<UInt>::const_iterator iter, const std::vector<UInt>& signs);

	static void getListImpl(EntityObject::SPtr entity, std::vector<UInt>::const_iterator iter,
		const std::vector<UInt>& signs, std::vector<EntityObject::SPtr>& result);

public:
	static EntityObject::SPtr get(EntityObject::SPtr entity, UInt sign);
	static EntityObject::SPtr get(EntityObject::SPtr entity, const std::vector<UInt>& signs);

	static const RefBase* getList(EntityObject::SPtr entity, UInt sign);
	static std::vector<EntityObject::SPtr> getList(EntityObject::SPtr entity, const std::vector<UInt>& signs);

	static void set(EntityObject::SPtr entity, UInt sign, EntityObject::SPtr relaEntity);

	static void remove(EntityObject::SPtr entity, UInt sign);
	static void remove(EntityObject::SPtr entity, UInt sign, EntityObject::SPtr relaEntity);
};

}
#endif // GEMINI_IocRelation_INCLUDE