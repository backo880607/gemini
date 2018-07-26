#ifndef GEMINI_IO_HandlerHelper_INCLUDE
#define GEMINI_IO_HandlerHelper_INCLUDE
#include "io/Handler.h"

namespace gemini {
namespace io {

class DataHandler;
class DataHandlerHelper {
  typedef std::shared_ptr<DataHandler> handler_type;

 public:
  DataHandlerHelper();
  ~DataHandlerHelper();

  void registerHandler(const Class& cls, handler_type handler);
  void registerHandler(const Class& cls, Int sign, handler_type handler);

  handler_type getHandler(const Class& cls);
  handler_type getHandler(const Class& cls, Int sign);

 private:
  std::map<const Class*, handler_type> _clsHandlers;
  std::map<const Class*, std::vector<handler_type>> _fieldHandlers;
};

class EntityHandler;
class EntityHandlerHelper {
  typedef std::shared_ptr<EntityHandler> handler_type;

 public:
  EntityHandlerHelper();
  ~EntityHandlerHelper();

  void registerHandler(const Class& cls, handler_type handler);

  handler_type getHandler(const Class& cls);

 private:
  std::map<const Class*, handler_type> _handlers;
};

class ValidateHandler;
class ValidateHandlerHelper {
  typedef std::shared_ptr<ValidateHandler> handler_type;

 public:
  ValidateHandlerHelper();
  ~ValidateHandlerHelper();

  void registerHandler(const Class& cls, handler_type handler);
  void registerHandler(const Class& cls, Int sign, handler_type handler);

  handler_type getHandler(const Class& cls);
  handler_type getHandler(const Class& cls, Int sign);

 private:
  std::map<const Class*, handler_type> _clsHandlers;
  std::map<const Class*, std::vector<handler_type>> _fieldHandlers;
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_HandlerHelper_INCLUDE