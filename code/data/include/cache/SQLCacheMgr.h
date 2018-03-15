#ifndef GEMINI_DATA_SQLCacheMgr_INCLUDE
#define GEMINI_DATA_SQLCacheMgr_INCLUDE
#include "../../core/include/cache/CacheMgr.h"
#include "../../public/Connection.h"

namespace gemini {
namespace data {

class SQLCacheMgr : public CacheMgr
{
	SQLCacheMgr();
public:
	~SQLCacheMgr();
	static SQLCacheMgr& instance();

	void init(const Char* configPath);

	virtual std::vector<EntityObject::SPtr> select(const Class& cls);
	virtual EntityObject::SPtr select(const Class& cls, ID id);
	virtual void insert(EntityObject::SPtr entity);
	virtual void erase(const Class& cls, ID id);
	virtual void erase(EntityObject::SPtr entity);
	virtual void clear(const Class& cls);

private:
	SQLConfig _config;
	Connection _sqlConn;
};

}
}
#endif // GEMINI_DATA_SQLCacheMgr_INCLUDE