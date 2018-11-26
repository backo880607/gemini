#include "InitApplication.h"
#include "aps/common/Export.h"
#include "user/public/Subject.h"
#include "user/public/UsernamePasswordToken.h"

#include "aps/public/service/mstr/ItemService.h"

InitApplication::InitApplication() {
  gemini::getApp().init();
  initAPS();

  gemini::user::UsernamePasswordToken token("root", "880607");
  gemini::user::Subject::get().login(token);
  gemini::getApp().setLocale("en_US");

  gemini::ServiceHelper<aps::ItemService> itemService;
  itemService->test();
}

InitApplication::~InitApplication() { gemini::getApp().uninit(); }