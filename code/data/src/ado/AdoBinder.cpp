#include "../../include/ado/AdoBinder.h"

namespace gemini {
namespace sql {

AdoBinder::AdoBinder(ADODB::_CommandPtr stmt) : _stmt(stmt) {}

AdoBinder::~AdoBinder() {}

void AdoBinder::bind(Boolean &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter(
      "", ADODB::adBoolean, direction(dir), sizeof(Boolean));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(Char &value, Direction dir) {
  ADODB::_ParameterPtr param =
      _stmt->CreateParameter("", ADODB::adChar, direction(dir), sizeof(Char));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(Short &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter(
      "", ADODB::adSmallInt, direction(dir), sizeof(Short));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(Int &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter(
      "", ADODB::adInteger, direction(dir), sizeof(Int));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(Long &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter(
      "", ADODB::adBigInt, direction(dir), sizeof(Long));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(Float &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter(
      "", ADODB::adDouble, direction(dir), sizeof(Float));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(Double &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter(
      "", ADODB::adDouble, direction(dir), sizeof(Double));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(String &value, Direction dir) {
  ADODB::_ParameterPtr param = _stmt->CreateParameter("", ADODB::adBSTR, direction(dir), sizeof(Float));
  _stmt->GetParameters()->Append(param);
}

void AdoBinder::bind(DateTime &value, Direction dir) {
  /**_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);*/
}

void AdoBinder::bind(Duration &value, Direction dir) {
  /**_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);*/
}

void AdoBinder::bind(DurationExtend &value, Direction dir) {
  /**_stmt, new Poco::Data::Binding<Boolean>(
              value, "", (Poco::Data::AbstractBinding::Direction)dir);*/
}

ADODB::ParameterDirectionEnum AdoBinder::direction(Direction dir) {
  ADODB::ParameterDirectionEnum result =
      ADODB::ParameterDirectionEnum::adParamUnknown;
  switch (dir) {
    case Direction::PD_IN:
      result = ADODB::ParameterDirectionEnum::adParamInput;
      break;
    case Direction::PD_IN_OUT:
      result = ADODB::ParameterDirectionEnum::adParamInputOutput;
      break;
    case Direction::PD_OUT:
      result = ADODB::ParameterDirectionEnum::adParamOutput;
      break;
  }
  return result;
}

}  // namespace sql
}  // namespace gemini