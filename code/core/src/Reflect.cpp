#include "entities/IocRelation.h"
#include "Reflect.h"
#include "propagate/Propagate.h"
#include "controller/BaseController.h"

namespace gemini {
	
Field::Field(const Class& type, Long offset, const Class& cls, const Char* name, Int index /* = 0 */, Boolean multiRef /* = 0 */)
	: _multiRef(multiRef)
	, _index(index)
	, _type(type)
	, _offset(offset)
	, _class(cls)
	, _name(name)
{

}

Field::~Field() {
	
}

__register_field__::__register_field__(const Class& type, Long offset, const Class& cls, const Char* name, Int index /* = 0 */, Boolean multiRef /* = 0 */)
{
	const Field* field = new Field(type, offset, cls, name, index, multiRef);
	const_cast<Class&>(cls).addField(field);
}

Method::Method(const Class& cls, const Class& returnCls, const char *name, const char *args)
	: _class(cls)
	, _name(name)
	, _returnCls(returnCls)
{

}

Method::~Method()
{

}

void Method::set_callable(__callable__ *cb)
{
	m_callable = cb;
	/*if (cb) {
		m_id = getName();
		m_long_id = getPrefix(cb->get_ret_type());
		m_long_id += '(';
		if (cb->get_args_count() == 0) {
			m_id += "__";
			m_id += typeid(void).name();
		}
		else {
			const arglist& list = cb->get_args();
			arglist::const_iterator i = list.begin();
			bool notfirst = false;
			while (i != list.end()) {
				const std::type_info* ti = *i++;
				m_id += "__";
				m_id += ti->name();
				if (notfirst) m_long_id += ", ";
				m_long_id += unmangle(ti->name());
				notfirst = true;
			}
		}
		m_long_id += ')';
	}*/
}

__register_method__::__register_method__(__callable__ *cb, const Class& cls, const Class& returnCls, const char *name, const char *args, const char *virt) {
	Method* method = new Method(cls, returnCls, name, args);
	method->set_callable(cb);
	const_cast<Class&>(cls).addMethod(method);
}


__register_static_method__::__register_static_method__(__callable__ *cb, const Class *pclass, const char *type, const char *name, const char *args) {
	//StaticMethod* method = new StaticMethod(pclass, type, name, args);
	//(const_cast<Class *>(pclass))->_addStaticMethod(method, cb);
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
ClassManager& geminiAfxGetClassManager() {
	static ClassManager manager;
	return manager;
}
const std::map<String, const Class* const>& geminiAfxEntityClasses() {
	return geminiAfxGetClassManager().getEntityClasses();
}
const std::map<String, const Class* const>& geminiAfxControllerClasses() {
	return geminiAfxGetClassManager().getControllerClasses();
}

SmartPtr<EntityObject> PropertyRefHelp::get(const EntityObject* entity, Int sign) {
	return entity->_relations[sign]->get();
}
void PropertyRefHelp::set(EntityObject* entity, Int sign, const SmartPtr<EntityObject>& relaEntity) {
	SmartPtr<EntityObject> entitySPtr;
	entitySPtr.wrapRawPointer(entity);
	IocRelation::set(entitySPtr, sign, relaEntity);
}
const IList& PropertyRefHelp::getList(const EntityObject* entity, Int sign) {
	return *((const IList*)(entity->_relations[sign]));
}

Int Class::s_maxIndex = 0;
Class::Class(const Char* name, const Class* superClass, PNewInstance instance) 
	: _index(s_maxIndex++)
	, _superClass(superClass)
	, _instance(instance)
	, _name(name)
{
	geminiAfxGetClassManager().registerClass(*this);
}

Class::~Class() {

}

#if GEMINI_OS == GEMINI_OS_LINUX
template<>
void* Class::create<void>() { return nullptr; }
template<>
void* Class::create<Object>() { return nullptr; }
template<>
void* Class::create<EntityObject>() { return nullptr; }
template<>
void* Class::create<IList>() { return nullptr; }
template<>
void* Class::create<const IList&>() { return nullptr; }

template <>
const Class& Class::forType<void>() { static const Class _class("void", nullptr, create<void>); return _class; }
template <>
const Class& Class::forType<Boolean>() { static const Class _class("Boolean", nullptr, create<Boolean>); return _class; }
template <>
const Class& Class::forType<Char>() { static const Class _class("Char", nullptr, create<Char>); return _class; }
template <>
const Class& Class::forType<Short>() { static const Class _class("Short", nullptr, create<Short>); return _class; }
template <>
const Class& Class::forType<Int>() { static const Class _class("Int", nullptr, create<Int>); return _class; }
template <>
const Class& Class::forType<Long>() { static const Class _class("Long", nullptr, create<Long>); return _class; }
template <>
const Class& Class::forType<Float>() { static const Class _class("Float", nullptr, create<Float>); return _class; }
template <>
const Class& Class::forType<Double>() { static const Class _class("Double", nullptr, create<Double>); return _class; }
template <>
const Class& Class::forType<String>() { static const Class _class("String", nullptr, create<String>); return _class; }
template <>
const Class& Class::forType<const Char*>() { return forType<String>(); }
#endif

Int Class::max_limits() {
	return 1024;
}

String Class::getName(const Char* name) {
	const Char* pLastSlash = strrchr(name, ':');
	if (pLastSlash == nullptr) {
		pLastSlash = strrchr(name, ' ');
	}
	return pLastSlash != nullptr ? pLastSlash + 1 : name;
}

Boolean Class::hasSuper() const {
	return _superClass != nullptr;
}

Boolean Class::isBase(const Class& cls) const {
	const Class* temp = this;
	while (temp->hasSuper()) {
		temp = &temp->getSuperClass();
		if (*temp == cls) {
			return true;
		}
	}
	return false;
}

const Class& Class::forName(const String& name) {
	return geminiAfxGetClassManager().forName(name);
}

const Field& Class::getField(const String& name) const {
	std::map<String, const Field*>::const_iterator iter = _fields.find(name);
	if (iter == _fields.end()) {

	}

	return *(iter->second);
}

void Class::addField(const Field* field) {
	std::map<String, const Field*>::iterator iter = _fields.find(field->getName());
	if (iter != _fields.end()) {

	}

	_fields.insert(std::make_pair(field->getName(), field));
}

void Class::addMethod(const Method* method) {
	std::map<String, const Method*>::iterator iter = _methods.find(method->getName());
	if (iter != _methods.end()) {

	}
	_methods.insert(std::make_pair(method->getName(), method));
}

}