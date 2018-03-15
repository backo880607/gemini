#pragma once
#include "DataExport.h"

namespace gemini {
namespace data {

class ResultSet;
class GEMINI_DATA_API RowIterator
{
public:
	static const std::size_t POSITION_END;

	RowIterator(const ResultSet* pResultSet, Boolean positionEnd);
	~RowIterator();
	
	void swap(RowIterator& other);

private:
	const ResultSet*	_pResultSet;
	mutable Int _position;
};

}
}