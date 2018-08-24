#include "../include/Driver.h"
#include "../include/SQLTransmit.h"
#include "../public/SQLModule.h"
#include "IApplication.h"
#include "api/DataNode.h"
#include "tools/File.h"

__register_sql_table_config__::__register_sql_table_config__(
    const gemini::Class& cls, const char* tblName) {}

__register_sql_column_config__::__register_sql_column_config__(
    const gemini::Class& cls, int sign, gemini::sql::Types columnType) {}

__register_sql_column_disable__::__register_sql_column_disable__(
    const gemini::Class& cls, int sign) {}

namespace gemini {
namespace sql {

REGISTER_MODULE(sql, SQLModule)
SQLModule::SQLModule() {}

SQLModule::~SQLModule() {}

void SQLModule::init() {
  initColumnTypes();
  readConfiguration();
  SQLTransmit::instance().start();
}

void SQLModule::uninit() { SQLTransmit::instance().stop(); }

void SQLModule::readConfiguration() {
  FilePath configPath = getApp().getConfigPath();
  configPath.append("sql_dev");
  InitFile config(configPath.string());
  if (config.valid()) {
    DataNode root = config.getNode();
    root.foreach ([&](DataNode node) {
      std::shared_ptr<Driver> driver(new Driver());
      _drivers[node.getName()] = driver;
      node.foreach ([&](DataNode subNode) {
        if (subNode.getName() == "ip") {
          driver->getConfig().ip = subNode.getValue();
        } else if (subNode.getName() == "port") {
          driver->getConfig().port = subNode.getValue<Int>();
        } else if (subNode.getName() == "username") {
          driver->getConfig().username = subNode.getValue();
        } else if (subNode.getName() == "password") {
          driver->getConfig().password = subNode.getValue();
        } else if (subNode.getName() == "database") {
          driver->getConfig().database = subNode.getValue();
        } else if (subNode.getName() == "driver") {
          driver->setType(subNode.getValue());
        }
      });
    });
  }
}

std::shared_ptr<Driver> SQLModule::getDriver(const String& name) const {
  std::map<String, std::shared_ptr<Driver>>::const_iterator iter =
      _drivers.find(name);
  return iter->second;
}

void SQLModule::registerColumnType(const Class& cls, Types type) {
  _columnTypes[cls.index()] = type;
}

void SQLModule::registerColumnType(const Class& cls, Int sign, Types type) {
  _fieldTypes[&cls][sign] = type;
}

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
  _columnTypes[Class::forType<DateTime>().index()] = Types::DATE;
  _columnTypes[Class::forType<Duration>().index()] = Types::TIMESTAMP;
  _columnTypes[Class::forType<DurationExtend>().index()] = Types::VARCHAR;
}

Types SQLModule::getColumnType(const Class& cls) {
  if (cls.isEnum() || cls.isMultiEnum()) {
    return Types::SHORT;
  }
  THROW_IF(_columnTypes[cls.index()] == Types::UNKNOW, UnknownTypeException)
  return _columnTypes[cls.index()];
}

Types SQLModule::getColumnType(const Class& cls, Int sign) {
  std::map<const Class*, std::map<Int, Types>>::iterator iter =
      _fieldTypes.find(&cls);
  if (iter == _fieldTypes.end()) {
    return Types::UNKNOW;
  }
  std::map<Int, Types>::iterator iterSign = iter->second.find(sign);
  return iterSign != iter->second.end() ? iterSign->second : Types::UNKNOW;
}

}  // namespace sql
}  // namespace gemini