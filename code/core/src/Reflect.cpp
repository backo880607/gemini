#include "../public/Reflect.h"
#include "../include/entities/IocRelation.h"
#include "../include/propagate/Propagate.h"
#include "../public/controller/BaseController.h"

namespace gemini {
	
Field::Field(const Class& type, ULong offset, const Class& cls, const Char* name, UInt index /* = 0 */)
	: _index(index)
	, _type(type)
	, _offset(offset)
	, _class(cls)
	, _name(name)
{

}

Field::~Field() {
	
}

__register_field__::__register_field__(const Class& type, ULong offset, const Class& cls, const Char* name, UInt index /* = 0 */)
{
	const Field* field = new Field(type, offset, cls, name, index);
	const_cast<Class&>(cls).addField(field);
}

class ClassManager final
{
	ClassManager(const ClassManager&) = delete;
	ClassManager& operator= (const ClassManager&) = delete;
public:
	ClassManager() {}
	~ClassManager() {}

	void registerClass(const Class& cls) {
		if (cls.isBase(EntityObject::getClassStatic())) {
			_classEntity.insert(std::make_pair(cls.getName(), &cls));
		} else if (cls.isBase(BaseController::getClassStatic())) {
			_classController.insert(std::make_pair(cls.getName(), &cls));
		}

		_classAll.insert(std::make_pair(cls.getName(), &cls));
	}

	const Class& forName(const String& name) {
		auto iter = _classAll.find(name);
		if (iter == _classAll.end()) {

		}

		return *iter->second;
	}

	const std::map<String, const Class* const>& getEntityClasses() const { return _classEntity; }
	const std::map<String, const Class* const>& getControllerClasses() const { return _classController; }

private:
	std::map<String, const Class* const> _classAll;
	std::map<String, const Class* const> _classEntity;
	std::map<String, const Class* const> _classController;
};
ClassManager& geminiAfxGetClassManager()
{
	static ClassManager manager;
	return manager;
}
const std::map<String, const Class* const>& geminiAfxEntityClasses()
{
	return geminiAfxGetClassManager().getEntityClasses();
}
const std::map<String, const Class* const>& geminiAfxControllerClasses()
{
	return geminiAfxGetClassManager().getControllerClasses();
}

SmartPtr<EntityObject> afxGetRelation(SmartPtr<EntityObject> entity, UInt sign)
{
	return IocRelation::get(entity, sign);
}

void afxSetRelation(SmartPtr<EntityObject> entity, UInt sign, SmartPtr<EntityObject> relaEntity)
{
	IocRelation::set(entity, sign, relaEntity);
}

void afxModifyProperty(SmartPtr<EntityObject> entity, const Field* field)
{
	Propagate::instance().modify(entity, field);
}

__register_method__::__register_method__(__callable__ *cb, const Class *pclass, const char *type, const char *name, const char *args, const char *virt) {
	//Method* method = new Method(pclass, type, name, args, virt[0] == 'v' ? true : false);
	//(const_cast<Class *>(pclass))->_addMethod(method, cb);
}


__register_static_method__::__register_static_method__(__callable__ *cb, const Class *pclass, const char *type, const char *name, const char *args) {
	//StaticMethod* method = new StaticMethod(pclass, type, name, args);
	//(const_cast<Class *>(pclass))->_addStaticMethod(method, cb);
}

UInt Class::s_maxIndex = 0;

Class::Class(const Char* name, const Class* superClass, PNewInstance instance) 
	: _index(s_maxIndex++)
	, _name(name)
	, _superClass(superClass)
	, _instance(instance)
{
	geminiAfxGetClassManager().registerClass(*this);
}

Class::~Class() {

}

UInt Class::max_limits() {
	return 1024;
}

String Class::getName(const Char* name)
{
	const Char* pLastSlash = strrchr(name, ':');
	if (pLastSlash == nullptr) {
		pLastSlash = strrchr(name, ' ');
	}
	return pLastSlash != nullptr ? pLastSlash + 1 : name;
}

Boolean Class::hasSuper() const
{
	return _superClass != nullptr;
}

Boolean Class::isBase(const Class& cls) const
{
	const Class* temp = this;
	while (temp->hasSuper()) {
		temp = &temp->getSuperClass();
		if (*temp == cls) {
			return true;
		}
	}
	return false;
}

const Class& Class::forName(const String& name)
{
	return geminiAfxGetClassManager().forName(name);
}

const Field& Class::getField(const String& name) const
{
	std::map<String, const Field*>::const_iterator iter = _fields.find(name);
	if (iter == _fields.end()) {

	}

	return *(iter->second);
}

void Class::addField(const Field* field)
{
	std::map<String, const Field*>::iterator iter = _fields.find(field->getName());
	if (iter != _fields.end()) {

	}

	_fields.insert(std::make_pair(field->getName(), field));
}

}