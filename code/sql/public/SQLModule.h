#ifndef GEMINI_SQL_SQLModule_INCLUDE
#define GEMINI_SQL_SQLModule_INCLUDE
#include "Module.h"

namespace gemini {
namespace sql {

class Driver;
class SQLModule : public Module {
 public:
  SQLModule();
  ~SQLModule();

  virtual void init();
  virtual void uninit();

  std::shared_ptr<Driver> getDriver(const String& name) const;

  void registerColumnType(const Class& cls, Types type);
  void registerColumnType(const Class& cls, Int sign, Types type);

  Types getColumnType(const Class& cls);
  Types getColumnType(const Class& cls, Int sign);

 private:
  void readConfiguration();
  void initColumnTypes();

 private:
  std::map<String, std::shared_ptr<Driver>> _drivers;
  std::vector<Types> _columnTypes;
  std::map<const Class*, std::map<Int, Types>> _fieldTypes;
};
SQLModule& afx_getSQLModule();

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLModule_INCLUDE