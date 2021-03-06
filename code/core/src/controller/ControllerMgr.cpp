#include "controller/ControllerMgr.h"
#include "message\Exception.h"

namespace gemini {

void ControllerMgr::init()
{
	_controllers.clear();
	const std::map<String, const Class* const>& ctlClses = geminiAfxControllerClasses();
	for (auto iter = ctlClses.begin(); iter != ctlClses.end(); ++iter) {
		_controllers.insert(std::make_pair(iter->first, (const BaseController*)iter->second->newInstance()));
	}
}

const BaseController& ControllerMgr::getController(const String& name)
{
	auto iter = _controllers.find(name);
	THROW_IF(iter == _controllers.end(), NoClassDefException, name)
	return *iter->second;
}

}