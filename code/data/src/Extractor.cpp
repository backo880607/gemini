#include "../include/Extractor.h"
#include "../include/StatementImpl.h"

#include <Poco/Data/Extraction.h>
#include <Poco/Data/Statement.h>

namespace gemini {
namespace sql {

Extractor::Extractor(StatementImpl* stmt) : _stmt(stmt) {}

Extractor::~Extractor() {}

void Extractor::extract(Boolean& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(Char& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(Short& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(Int& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(Long& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(Float& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(Double& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(String& value) {
  *_stmt->_stmt, Poco::Data::Keywords::into(value);
}

void Extractor::extract(DateTime& value) {}

void Extractor::extract(Duration& value) {}

void Extractor::extract(DurationExtend& value) {}

}  // namespace sql
}  // namespace gemini