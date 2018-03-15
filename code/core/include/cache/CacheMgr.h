#ifndef GEMINI_CacheMgr_INCLUDE
#define GEMINI_CacheMgr_INCLUDE
#include "CacheDao.h"

namespace gemini {

class CacheMgr final : public noncopyable
{
	typedef std::shared_ptr<CacheDao> dao_type;
public:
	CacheMgr();
	~CacheMgr();

	static CacheMgr& instance() { static CacheMgr mgr; return mgr; }

	void init();

	dao_type getDao(const Class& cls);

private:
	std::vector<dao_type> _daoes;
};

}
#endif // !GEMINI_CacheMgr_INCLUDE
