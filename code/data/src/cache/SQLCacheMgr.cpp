#include "../../include/cache/SQLCacheMgr.h"
#include "tools\File.h"
#include "tools\XML.h"
#include "IApplication.h"

namespace gemini {
namespace data {

SQLCacheMgr::SQLCacheMgr()
{
}

SQLCacheMgr::~SQLCacheMgr()
{

}

SQLCacheMgr& SQLCacheMgr::instance()
{
	static SQLCacheMgr mgr;
	return mgr;
}

void SQLCacheMgr::init(const Char* configPath)
{
	FilePath filePath = getApp().getConfigPath();
	filePath.append(u8"database").append(u8"config.xml");
	XMLFile xmlFile(filePath.string());
	if (xmlFile.valid()) {
		XMLNode rootNode = xmlFile.getNode();
		String sqlName = rootNode.getNode(u8"Type").getValue();
	}
}

std::vector<EntityObject::SPtr> SQLCacheMgr::select(const Class & cls)
{
	return std::vector<EntityObject::SPtr>();
}

EntityObject::SPtr SQLCacheMgr::select(const Class & cls, ID id)
{
	return EntityObject::SPtr();
}

void SQLCacheMgr::insert(EntityObject::SPtr entity)
{
}

void SQLCacheMgr::erase(const Class & cls, ID id)
{
}

void SQLCacheMgr::erase(EntityObject::SPtr entity)
{
}

void SQLCacheMgr::clear(const Class & cls)
{
}

}
}