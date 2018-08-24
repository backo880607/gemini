#ifndef GEMINI_Application_INCLUDE
#define GEMINI_Application_INCLUDE
#include "../public/IApplication.h"

namespace gemini {

class LocaleUtil;
class Module;
class CORE_API Application final : public IApplication {
  struct ModuleData {
    Module *module;
    String name;
  };

 public:
  Application();
  ~Application();

  void registerModule(const Char *moduleName, Module *module);
  void unregisterModule(const Char *moduleName);

  virtual void init() override;

  virtual const Char *getEnvironment() override { return _environment.c_str(); }
  virtual const Char *getConfigPath() override;
  const Char *getDumpPath();

  virtual const std::locale &getLocale() override;
  virtual void setLocale(const Char *name) override;

  std::shared_ptr<LocaleUtil> getDefaultLocal() { return _defaultLocal; }

 private:
  void readConfiguration();

 private:
  std::shared_ptr<LocaleUtil> _defaultLocal;
  String _environment;
  std::map<String, ModuleData> _modules;
};
extern CORE_API Application g_app;

}  // namespace gemini
#endif  // GEMINI_Application_INCLUDE