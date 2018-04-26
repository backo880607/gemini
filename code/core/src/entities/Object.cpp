#include "Object.h"
#include "entities/RefBase.h"
#include "message/Exception.h"
#include "tools/StringUtil.h"

#include <chrono>
#include <atomic>

namespace gemini {
	
void* createObject() { return nullptr; }
const Class Object::s_class("Object", nullptr, createObject);

//static const boost::posix_time::ptime s_startTime(boost::gregorian::date(2016, 1, 1), boost::posix_time::time_duration(0, 0, 0, 0));
static const std::chrono::steady_clock::time_point s_startTime;
class IDGenerator final {
	IDGenerator()
		: m_lastMilliseconds(0)
		, _logicSlice(0)
		, _seq_id(0)
	{
		std::chrono::steady_clock::duration dur = std::chrono::steady_clock::now() - s_startTime;
		m_lastMilliseconds = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	}
public:
	~IDGenerator() {}
	static IDGenerator& instance() { static IDGenerator obj; return obj; }

	ID getID(ID id = 0) {
		if (0 != id) return id;

		std::chrono::steady_clock::duration dur = std::chrono::steady_clock::now() - s_startTime;
		Long totalMilliseconds = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		Long seqID = 0;
		if (totalMilliseconds > m_lastMilliseconds) {
			m_lastMilliseconds = totalMilliseconds;
			_seq_id = 0;
		}
		else {
			seqID = ++_seq_id;
			if ((seqID >> 12) > 0) {

			}
		}

		id |= totalMilliseconds << 22;
		id |= _logicSlice << 10;
		id |= seqID;
		return id;
	}
	Long getLogicalSlice() const { return _logicSlice; }

private:
	Long m_lastMilliseconds;
	Long _logicSlice;
	Long _seq_id;
};

const Class EntityObject::_class("EntityObject", &Object::getClassStatic(), createObject);
Int EntityObject::s_index = 1;
EntityObject::EntityObject()
	: _id(IDGenerator::instance().getID())
{
}

EntityObject::~EntityObject()
{
	for (RefBase* ref : _relations) {
		delete ref;
	}
}

Boolean EntityObject::operator==(const Any & rhs) const
{
	return Boolean();
}

Boolean EntityObject::operator<(const Any & rhs) const
{
	return Boolean();
}

Boolean IList::operator==(const Any & rhs) const
{
	const IList& rhsList = rhs.cast<IList>();
	IList::Iterator iter = iterator();
	IList::Iterator rhsIter = rhsList.iterator();
	while (iter.hasNext()) {
		EntityObject::SPtr entity = iter.next<EntityObject>();
		if (rhsIter.hasNext()) {
			EntityObject::SPtr rhsEntity = iter.next<EntityObject>();
			if (entity->getID() != rhsEntity->getID()) {
				break;
			}
		} else {
			break;
		}
	}
	return rhsIter.hasNext() ? false : true;
}

}