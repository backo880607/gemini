#ifndef GEMINI_Propagate_INCLUDE
#define GEMINI_Propagate_INCLUDE
#include "../../public/service/BaseService.h"

namespace gemini {

class Propagate final : public noncopyable
{
public:
	struct Data {
		const UInt id = ++Propagate::s_maxID;
		std::vector<std::vector<UInt>> paths;
		std::vector<const Field*> properties;
		const BaseService* service;
		service::callable* method;
	};

	Propagate();
public:
	~Propagate();
	static Propagate& instance() { static Propagate obj; return obj; }

	void invoke();
	void modify(const EntityObject::SPtr& entity, const Field* field);

	Data* getData(const Field* field);

private:
	friend class PropagateHelper;
	static MT_UInt s_maxID;
	std::vector<std::map<const Field*, Data>> _datas;
};

}

#endif // GEMINI_Propagate_INCLUDE
