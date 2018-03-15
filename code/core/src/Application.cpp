#include "../include/Application.h"
#include "../public/tools/File.h"
#include "../include/DumpFile.h"
#include "../include/entities/FactoryMgr.h"
#include "../include/propagate/PropagateHelper.h"
#include "../public/session/Subject.h"
#include "../include/tools/LocaleUtil.h"

namespace gemini {

Application g_app;
IApplication& getApp() {
	return g_app;
}
Application::Application()
{

}

Application::~Application()
{

}

void Application::init()
{
	//DumpFile::instance().Init();
	FactoryMgr::instance().init();
	PropagateHelper propagateHelper;
	//propagateHelper.loadConfig();
}

const Char* Application::getConfigPath()
{
	static String path;
	if (path.empty()) {
		FilePath filePath = FilePath::currentPath();
		filePath.append(u8"config");
		if (!filePath.isExist()) {
			filePath.createDirectories();
		}

		path = filePath.string();
	}
	return path.c_str();
}

const Char* Application::getDumpPath()
{
	static String dump;
	if (dump.empty()) {
		FilePath filePath = FilePath::currentPath();
		filePath.append(u8"dump");
		if (!filePath.isExist()) {
			filePath.createDirectories();
		}

		dump = filePath.string();
	}
	return dump.c_str();
}

const std::locale& Application::getLocale()
{
	return Subject::get().getSession()->get<LocaleUtil>().getLocale();
}

void Application::setLocale(const Char* name)
{
	boost::locale::generator gen;
	Subject::get().getSession()->get<LocaleUtil>().setLocale(gen(String(name) + u8".UTF-8"));
}

}