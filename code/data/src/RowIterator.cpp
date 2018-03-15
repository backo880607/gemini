#include "../public/RowIterator.h"

namespace gemini {
namespace data {

const std::size_t RowIterator::POSITION_END = Int_MAX;
RowIterator::RowIterator(const ResultSet* pResultSet, Boolean positionEnd)
	: _pResultSet(pResultSet)
	, _position(positionEnd ? POSITION_END : 0)
{
}

RowIterator::~RowIterator()
{

}

void RowIterator::swap(RowIterator& other)
{
	std::swap(_pResultSet, other._pResultSet);
	std::swap(_position, other._position);
}

}
}