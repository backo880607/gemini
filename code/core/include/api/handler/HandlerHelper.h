#ifndef GEMINI_API_HandlerHelper_INCLUDE
#define GEMINI_API_HandlerHelper_INCLUDE
#include "../../../public/api/Handler.h"

namespace gemini {
namespace api {

class DataHandler;
class DataHandlerHelper {
  typedef std::shared_ptr<DataHandler> handler_type;

 public:
  DataHandlerHelper();
  ~DataHandlerHelper();

  void registerHandler(const Class& cls, handler_type handler);
  void registerHandler(const Class& cls, const Field& field,
                       handler_type handler);

  handler_type getHandler(const Class& cls);
  handler_type getHandler(const Class& cls, const Field& field);

 private:
  std::map<const Class*, handler_type> _clsHandlers;
  std::map<const Class*, std::map<const Field*, handler_type>> _fieldHandlers;
};

class ObjectHandler;
class ObjectHandlerHelper {
  typedef std::shared_ptr<ObjectHandler> handler_type;

 public:
  ObjectHandlerHelper();
  ~ObjectHandlerHelper();

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
  void registerHandler(const Class& cls, const Field& field,
                       handler_type handler);

  handler_type getHandler(const Class& cls);
  handler_type getHandler(const Class& cls, const Field& field);

 private:
  std::map<const Class*, handler_type> _clsHandlers;
  std::map<const Class*, std::map<const Field*, handler_type>> _fieldHandlers;
};

}  // namespace api
}  // namespace gemini
#endif  // !GEMINI_API_HandlerHelper_INCLUDE