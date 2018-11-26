#include "../include/Driver.h"
#include "../include/SQLTransmit.h"
#include "../public/SQLModule.h"
#include "IApplication.h"
#include "api/DataNode.h"
#include "tools/File.h"

__register_sql_table_config__::__register_sql_table_config__(
    const gemini::Class& cls, const char* tableName) {
  gemini::sql::afx_getSQLModule().registerTableName(cls, tableName);
}

__register_sql_column_config__::__register_sql_column_config__(
    const gemini::Class& cls, const gemini::Field& field,
    gemini::sql::Types columnType) {
  gemini::sql::afx_getSQLModule().registerColumnType(cls, field, columnType);
}

__register_sql_column_disable__::__register_sql_column_disable__(
    const gemini::Class& cls, const gemini::Field& field) {
  gemini::sql::afx_getSQLModule().disableColumn(cls, field);
}

namespace gemini {
namespace sql {

REGISTER_MODULE(sql, SQLModule)
SQLModule::SQLModule() {}

SQLModule::~SQLModule() { clear(); }

void SQLModule::init() {
  initColumnTypes();
  readConfiguration();
  SQLTransmit::instance().start();
}

void SQLModule::clear() {
  for (std::map<String, Driver*>::iterator iter = _drivers.begin();
       iter != _drivers.end(); ++iter) {
    delete iter->second;
  }
}

void SQLModule::uninit() { SQLTransmit::instance().stop(); }

void SQLModule::initColumnTypes() {
  _columnTypes.resize(Class::max_limits());
  _columnTypes[Class::forType<Boolean>().index()] = Types::BOOLEAN;
  _columnTypes[Class::forType<Char>().index()] = Types::CHAR;
  _columnTypes[Class::forType<Short>().index()] = Types::SHORT;
  _columnTypes[Class::forType<Int>().index()] = Types::INT;
  _columnTypes[Class::forType<Long>().index()] = Types::LONG;
  _columnTypes[Class::forType<Float>().index()] = Types::FLOAT;
  _columnTypes[Class::forType<Double>().index()] = Types::DOUBLE;
  _columnTypes[Class::forType<Char>().index()] = Types::CHAR;
  _columnTypes[Class::forType<String>().index()] = Types::VARCHAR;
  _columnTypes[Class::forType<ID>().index()] = Types::LONG;
  _columnTypes[Class::forType<DateTime>().index()] = Types::DATE;
  _columnTypes[Class::forType<Duration>().index()] = Types::TIMESTAMP;
  _columnTypes[Class::forType<DurationExtend>().index()] = Types::VARCHAR;
}

void SQLModule::readConfiguration() {
  FilePath configPath = getApp().getConfigPath();
  configPath.append(
      StringUtil::SPrintf("%s%s", "sql_", getApp().getEnvironment()).c_str());
  InitFile config(configPath.string());
  if (config.valid()) {
    DataNode root = config.getNode();
    root.foreach ([&](DataNode node) {
      Driver* driver = new Driver();
      _drivers[node.getName()] = driver;
      node.foreach ([&](DataNode subNode) {
        const Char* nodeName = subNode.getName().c_str();
        if (StringUtil::icompare(nodeName, "ip") == 0) {
          driver->getConfig().ip = subNode.getValue();
        } else if (StringUtil::icompare(nodeName, "port") == 0) {
          THROW_IF(subNode.getValue<Int>() <= 0, ConfigException,
                   "invalid port value: ", subNode.getValue<Int>())
          driver->getConfig().port = subNode.getValue<Int>();
        } else if (StringUtil::icompare(nodeName, "username") == 0) {
          driver->getConfig().username = subNode.getValue();
        } else if (StringUtil::icompare(nodeName, "password") == 0) {
          driver->getConfig().password = subNode.getValue();
        } else if (StringUtil::icompare(nodeName, "database") == 0) {
          driver->getConfig().database = subNode.getValue();
        } else if (StringUtil::icompare(nodeName, "driver") == 0) {
          driver->setType(subNode.getValue());
        } else if (StringUtil::icompare(nodeName, "maxTotal") == 0) {
          THROW_IF(subNode.getValue<Int>() <= 0, ConfigException,
                   "invalid max total value: ", subNode.getValue<Int>())
          driver->getConfig().maxTotal = subNode.getValue<Int>();
        } else {
          THROW(ConfigException, "invalid config name: ", subNode.getName());
        }
      });
      driver->changeDataBase();
    });
  }
}

Driver* SQLModule::getDriver(const String& name) const {
  std::map<String, Driver*>::const_iterator iter = _drivers.find(name);
  return iter->second;
}

void SQLModule::registerTableName(const Class& cls, const Char* name) {
  _tableNames[&cls] = name;
}

void SQLModule::registerColumnType(const Class& cls, Types type) {
  _columnTypes[cls.index()] = type;
}

void SQLModule::registerColumnType(const Class& cls, const Field& field,
                                   Types type) {
  _fieldTypes[&cls][&field] = type;
}

String SQLModule::getTableName(const Class& cls) {
  auto iter = _tableNames.find(&cls);
  return iter != _tableNames.end() ? iter->second : "";
}

Types SQLModule::getColumnType(const Class& cls) {
  if (cls.isEnum() || cls.isMultiEnum()) {
    return Types::SHORT;
  }
  THROW_IF(_columnTypes[cls.index()] == Types::UNKNOW, UnknownTypeException)
  return _columnTypes[cls.index()];
}

Types SQLModule::getColumnType(const Class& cls, const Field& field) {
  std::map<const Class*, std::map<const Field*, Types>>::iterator iter =
      _fieldTypes.find(&cls);
  if (iter == _fieldTypes.end()) {
    return Types::UNKNOW;
  }
  auto iterField = iter->second.find(&field);
  return iterField != iter->second.end() ? iterField->second : Types::UNKNOW;
}

Boolean SQLModule::disableColumn(const Class& cls, const Field& field) {
  std::map<const Class*, std::map<const Field*, Types>>::iterator iter =
      _fieldTypes.find(&cls);
  if (iter == _fieldTypes.end()) {
    return false;
  }

  return iter->second.find(&field) != iter->second.end();
}

}  // namespace sql
}  // namespace gemini