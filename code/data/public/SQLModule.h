#ifndef GEMINI_SQL_SQLModule_INCLUDE
#define GEMINI_SQL_SQLModule_INCLUDE
#include "Module.h"

namespace gemini {
namespace sql {

class SQLModule : public Module {
 public:
  SQLModule();
  ~SQLModule();

  virtual void init();
  virtual void uninit();

  Driver* getDriver(const String& name) const;

  void registerTableName(const Class& cls, const Char* name);

  void registerColumnType(const Class& cls, Types type);
  void registerColumnType(const Class& cls, const Field& field, Types type);

  String getTableName(const Class& cls);
  Types getColumnType(const Class& cls);
  Types getColumnType(const Class& cls, const Field& field);

  Boolean disableColumn(const Class& cls, const Field& field);

 private:
  void readConfiguration();
  void initColumnTypes();
  void clear();

 private:
  std::map<String, Driver*> _drivers;
  std::vector<Types> _columnTypes;
  std::map<const Class*, String> _tableNames;
  std::map<const Class*, std::map<const Field*, Types>> _fieldTypes;
  std::map<const Class*, std::set<const Field*>> _disableFields;
};
SQLModule& afx_getSQLModule();

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLModule_INCLUDE