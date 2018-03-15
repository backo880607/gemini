#include "InitApplication.h"
//#include "aps/common/Export.h"
#include "session/Subject.h"
#include "session/UsernamePasswordToken.h"
#include "System.h"
#include "ServerUtil.h"

InitApplication::InitApplication()
{
	//initAPS();
	gemini::getApp().init();
	gemini::UsernamePasswordToken token(u8"root", u8"12345678");
	gemini::Subject::get().login(token);
	gemini::getApp().setLocale(u8"en_US");

	gemini::ServerUtil::startHTTPServer();

	System system;
	if (!system.hasError()) {
		system.GetSerialNumber();
		system.GetCPUID();
		system.GetMainHardDiskId();
		system.GetMainBoardId();
		system.GetNetworkAdapterId();
		system.GetGroupName();
	}
}

InitApplication::~InitApplication()
{

}