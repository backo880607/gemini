#include "Application.h"
#include "tools/File.h"
//#include "DumpFile.h"
#include "api/DataNode.h"
#include "entities/FactoryMgr.h"
#include "propagate/PropagateHelper.h"
#include "session/Subject.h"
#include "tools/LocaleUtil.h"
#include "Module.h"

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
  PropagateHelper propagateHelper;
  // propagateHelper.loadConfig();
  readConfiguration();

  // 初始化各模块
  for (std::map<String, ModuleData>::iterator iter = _modules.begin();
       iter != _modules.end(); ++iter) {
    iter->second.module->init();
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
  Session::SPtr session = Subject::get().getSession();
  if (!session.valid()) {
    return _defaultLocal->getLocale();
  }
  return session->get<LocaleUtil>().getLocale();
}

void Application::setLocale(const Char* name) {
  boost::locale::generator gen;
  Subject::get().getSession()->get<LocaleUtil>().setLocale(
      gen(String(name) + ".UTF-8"));
}

}  // namespace gemini