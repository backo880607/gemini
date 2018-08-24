#include "InitApplication.h"
#include "aps/common/Export.h"
#include "session/Subject.h"
#include "session/UsernamePasswordToken.h"

#include "aps/public/service/mstr/ItemService.h"

InitApplication::InitApplication() {
  gemini::getApp().init();
  initAPS();

  gemini::UsernamePasswordToken token("root", "880607");
  gemini::Subject::get().login(token);
  gemini::getApp().setLocale("en_US");
}

InitApplication::~InitApplication() {}