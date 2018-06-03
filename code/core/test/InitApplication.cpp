#include "InitApplication.h"
#include "aps/common/Export.h"
#include "session/Subject.h"
#include "session/UsernamePasswordToken.h"

InitApplication::InitApplication()
{
	gemini::getApp().init();
	initAPS();
	//gemini::UsernamePasswordToken token(u8"root", u8"12345678");
	//gemini::Subject::get().login(token);
	//gemini::getApp().setLocale(u8"en_US");
}

InitApplication::~InitApplication()
{

}