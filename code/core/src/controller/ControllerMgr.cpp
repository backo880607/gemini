#include "../../public/controller/ControllerMgr.h"

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
	if (iter == _controllers.end()) {

	}

	return *iter->second;
}

}