#ifndef GEMINI_SQL_Driver_INCLUDE
#define GEMINI_SQL_Driver_INCLUDE
#include "../public/Connection.h"
#include "api/Handler.h"

#include <mutex>

namespace gemini {
namespace sql {

class SQLStringHandler : public api::DataHandler {
 public:
  SQLStringHandler();
  ~SQLStringHandler();

  virtual String read(Object::SPtr entity, const Field* field) override;
  virtual void write(Object::SPtr entity, const Field* field,
                     const String& value) override;
};

/*class SQLEntityHandler : public io::EntityHandler {
 public:
  SQLEntityHandler(const Class& cls);
  ~SQLEntityHandler();

  virtual EntityObject::SPtr get(const String& primary) override;
  virtual EntityObject::SPtr require(const String& primary) override;
};*/

class Driver {
  typedef std::shared_ptr<api::DataHandler> data_handler;
  //typedef std::shared_ptr<io::EntityHandler> entity_handler;

 public:
  Driver();
  virtual ~Driver();

  virtual Connection getConn();

  SQL_TYPE getType() { return _type; }
  void setType(SQL_TYPE type) { _type = type; }
  void setType(const String& type);

  SQLConfig& getConfig() { return _config; }

  void changeDataBase();

  Int capacity() const { return _config.maxTotal; }

  void shutdown();

  void registerDataHandler(const Class& cls, data_handler handler);
  void registerDataHandler(const Class& cls, const Field& field,
                           data_handler handler);
  data_handler getDataHandler(const Class& cls);
  data_handler getDataHandler(const Field& field);

  /*void registerEntityHandler(const Class& cls, entity_handler handler);
  entity_handler getEntityHandler(const Class& cls);*/

 protected:
  //std::vector<Connection>& getConnections() { return _conns; }
  void pushBack(std::shared_ptr<ConnectionImpl>& conn);

 private:
  void purgeDeadSessions();

 private:
  friend class Connection;
  Boolean _shutdown;
  Int _curConns;
  SQL_TYPE _type;
  SQLConfig _config;
  std::mutex _mutex;
  std::vector<std::shared_ptr<ConnectionImpl>> _idleConns;
  std::vector<std::weak_ptr<ConnectionImpl>> _activeConns;
  std::map<const Class*, data_handler> _clsHandlers;
  std::map<const Class*, std::map<const Field*, data_handler>> _fieldHandlers;
  //std::map<const Class*, entity_handler> _entityHandlers;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Driver_INCLUDE