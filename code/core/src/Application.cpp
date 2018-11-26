#include "Application.h"
#include "tools/File.h"
//#include "DumpFile.h"
#include "Module.h"
#include "api/DataNode.h"
#include "entities/FactoryMgr.h"
#include "propagate/PropagateHelper.h"
#include "Session.h"
#include "tools/LocaleUtil.h"

#include "MultiEnum.h"
namespace gemini {

Application g_app;
IApplication& getApp() { return g_app; }
Application::Application() {}

Application::~Application() {}

void Application::registerModule(const Char* moduleName, Module* module) {
  std::map<String, ModuleData>::iterator iter = _modules.find(moduleName);
  _modules[moduleName].module = module;
  _modules[moduleName].name = moduleName;
}

void Application::unregisterModule(const Char* moduleName) {
  std::map<String, ModuleData>::iterator iter = _modules.find(moduleName);
  if (iter != _modules.end()) {
    iter->second.module->uninit();
    _modules.erase(iter);
  }
}

void Application::init() {
  _defaultLocal.reset(new LocaleUtil());
  // DumpFile::instance().Init();
  FactoryMgr::instance().init();
  readConfiguration();

  for (std::map<String, ModuleData>::iterator iter = _modules.begin();
       iter != _modules.end(); ++iter) {
    iter->second.module->init();
  }
}

void Application::uninit() {
  for (std::map<String, ModuleData>::iterator iter = _modules.begin();
       iter != _modules.end(); ++iter) {
    iter->second.module->uninit();
  }
}

void Application::readConfiguration() {
  FilePath configPath = getConfigPath();
  configPath.append("app");
  InitFile config(configPath.string());
  if (config.valid()) {
    DataNode root = config.getNode();
    root.foreach ([&](DataNode node) {
      if (node.getName() == "environment") {
        _environment = node.getValue();
      }
    });
  }
}

Boolean Application::isFieldStoraged(const Class& cls, const Field& field) {
  return FactoryMgr::instance().isFieldStoraged(cls, field);
}

const Char* Application::getConfigPath() {
  static String path;
  if (path.empty()) {
    FilePath filePath = FilePath::currentPath();
    filePath.append("config");
    if (!filePath.isExist()) {
      filePath.createDirectories();
    }

    path = filePath.string();
  }
  return path.c_str();
}

const Char* Application::getTempPath() {
  static String path;
  if (path.empty()) {
    FilePath filePath = FilePath::currentPath();
    filePath.append("temp");
    if (!filePath.isExist()) {
      filePath.createDirectories();
    }

    path = filePath.string();
  }
  return path.c_str();
}

const Char* Application::getDumpPath() {
  static String dump;
  if (dump.empty()) {
    FilePath filePath = FilePath::currentPath();
    filePath.append("dump");
    if (!filePath.isExist()) {
      filePath.createDirectories();
    }

    dump = filePath.string();
  }
  return dump.c_str();
}

const std::locale& Application::getLocale() {
  Session::SPtr session = getSession();
  if (!session.valid()) {
    return _defaultLocal->getLocale();
  }
  return session->get<LocaleUtil>().getLocale();
}

void Application::setLocale(const Char* name) {
  boost::locale::generator gen;
  getSession()->get<LocaleUtil>().setLocale(
      gen(String(name) + ".UTF-8"));
}

void Application::setLocale(const std::locale& loc) {
  getSession()->get<LocaleUtil>().setLocale(loc);
}

LocaleSwitch::LocaleSwitch(const Char* name) {
  _oldLocale = getApp().getLocale();
  getApp().setLocale(name);
}

LocaleSwitch::LocaleSwitch(const std::locale& loc) {
  _oldLocale = getApp().getLocale();
  getApp().setLocale(loc);
}

LocaleSwitch::~LocaleSwitch() { getApp().setLocale(_oldLocale); }

}  // namespace gemini