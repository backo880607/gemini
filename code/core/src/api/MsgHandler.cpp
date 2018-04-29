#include "api/MsgHandler.h"
#include "tools/Json.h"

namespace gemini {

MsgHandler::MsgHandler() {

}

MsgHandler::~MsgHandler() {

}

MsgData MsgHandler::execute(const MsgData& msg) {
	return MsgData();
}
Boolean MsgHandler::format(MsgData& msg, const EntityObject::SPtr& entity)
{
	if (!msg.valid()) {
		return false;
	}

	if (!entity.valid()) {
		return true;
	}

	switch (msg.getDataType())
	{
	case DataType::DT_JSON:
		return formatJson(msg, entity);
	default:
		break;
	}

	return false;
}

String MsgHandler::getValue(const EntityObject::SPtr& entity, const Field* field)
{
	if (field == nullptr) {
		return "";
	}

	if (field->getType() == Class::forType<Boolean>()) {
		return StringUtil::format(field->get<Boolean>(entity));
	} else if (field->getType() == Class::forType<Short>()) {
		return StringUtil::format(field->get<Short>(entity));
	} else if (field->getType() == Class::forType<Int>()) {
		return StringUtil::format(field->get<Int>(entity));
	}

	return "";
}

Boolean MsgHandler::formatJson(MsgData & msg, const EntityObject::SPtr & entity)
{
	Json json;
	entity->getClass().foreach_fields([&](const Field* field) {
		json.createNode(field->getName()).setValue(getValue(entity, field));
	});
	return true;
}

MsgProcessHandler::MsgProcessHandler()
{

}

MsgProcessHandler::~MsgProcessHandler()
{

}

MsgRemoteHandler::MsgRemoteHandler()
{

}

MsgRemoteHandler::~MsgRemoteHandler()
{

}

}