#include "../../include/poco/PocoBinder.h"

#include <Poco/Data/Binding.h>

namespace gemini {
namespace sql {

PocoBinder::PocoBinder(Poco::Data::Statement *stmt) : _stmt(stmt) {}

PocoBinder::~PocoBinder() {}

void PocoBinder::bind(Boolean &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(Char &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Char>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(Short &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Short>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(Int &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Int>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(Long &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Long>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(Float &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Float>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(Double &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<Double>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(String &value, Direction dir) {
  *_stmt, new Poco::Data::Binding<String>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);
}

void PocoBinder::bind(DateTime &value, Direction dir) {
  /**_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);*/
}

void PocoBinder::bind(Duration &value, Direction dir) {
  /**_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);*/
}

void PocoBinder::bind(DurationExtend &value, Direction dir) {
  /**_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);*/
}

}  // namespace sql
}  // namespace gemini