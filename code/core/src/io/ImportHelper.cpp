#include "io/ImportHelper.h"
#include "io/IOScheme.h"
#include "io/IOField.h"
#include "io/DataSourceMgr.h"
#include "io/DataHandler.h"
#include "tools/StringUtil.h"

namespace gemini
{
namespace io
{
ImportHelper::ImportHelper(SmartPtr<IOScheme> scheme)
	: _scheme(scheme)
{
}

ImportHelper::~ImportHelper()
{
}

void ImportHelper::execute()
{
	if (!parseIOScheme())
	{
		return;
	}
}

Boolean ImportHelper::parseIOScheme()
{
	if (_scheme == nullptr)
	{
		return false;
	}

	_dataSource = DataSourceMgr::instance().getDataSource(_scheme->_dataSource);
	if (_dataSource == nullptr)
	{
		return false;
	}

	while (_dataSource->step())
	{
		EntityObject::SPtr entity;
		if (!entity.valid())
		{
			continue;
		}

		Long index = 0;
		IList::Iterator iter = _scheme->_fields->iterator();
		while (iter.hasNext())
		{
			IOField::SPtr ioField = iter.next<IOField>();
			const Field *field = ioField->_field;
			if (field == nullptr)
			{
				continue;
			}
			String value = _dataSource->getData(index);
			std::shared_ptr<DataHandler> handler = _dataHandler.getHandler(field->getClass(), field->index());
			if (handler)
			{
				handler->write(entity, field, value);
				continue;
			}
			handler = _dataHandler.getHandler(field->getClass());
			if (handler)
			{
				handler->write(entity, field, value);
				continue;
			}

			write(entity, field, value);
		}
	}
}

void ImportHelper::write(EntityObject::SPtr entity, const Field *field, const String &value)
{
	const Class &fieldCls = field->getClass();
	if (fieldCls == Class::forType<Boolean>())
	{
		field->set(entity, StringUtil::convert<Boolean>(value.c_str()));
	}
	else if (fieldCls == Class::forType<Short>())
	{
		field->set(entity, StringUtil::convert<Short>(value.c_str()));
	}
	else if (fieldCls == Class::forType<Int>())
	{
		field->set(entity, StringUtil::convert<Int>(value.c_str()));
	}
	else if (fieldCls == Class::forType<Long>())
	{
		field->set(entity, StringUtil::convert<Long>(value.c_str()));
	}
	else if (fieldCls == Class::forType<Float>())
	{
		field->set(entity, StringUtil::convert<Float>(value.c_str()));
	}
	else if (fieldCls == Class::forType<Double>())
	{
		field->set(entity, StringUtil::convert<Double>(value.c_str()));
	}
	else if (fieldCls == Class::forType<String>())
	{
		field->set(entity, value);
	}
	else if (fieldCls.isEnum())
	{
		field->set(entity, fieldCls.getEnum(value));
	}
}

} // namespace io
} // namespace gemini