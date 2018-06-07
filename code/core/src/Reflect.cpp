#include "Reflect.h"
#include "entities/IocRelation.h"
#include "propagate/Propagate.h"
#include "controller/BaseController.h"
#include "message/Exception.h"

namespace gemini
{

Field::Field(const Class &type, Long offset, const Class &cls, const Char *name, Int index /* = 0 */, Boolean multiRef /* = 0 */)
	: _multiRef(multiRef), _index(index), _type(type), _offset(offset), _class(cls), _name(name)
{
}

Field::~Field()
{
}

__register_field__::__register_field__(const Class &type, Long offset, const Class &cls, const Char *name, Int index /* = 0 */, Boolean multiRef /* = 0 */)
{
	const Field *field = new Field(type, offset, cls, name, index, multiRef);
	const_cast<Class &>(cls).addField(field);
}

Method::Method(const Class &cls, const Class &returnCls, const char *name, const char *args)
	: _class(cls), _name(name), _returnCls(returnCls)
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

__register_method__::__register_method__(__callable__ *cb, const Class &cls, const Class &returnCls, const char *name, const char *args, const char *virt)
{
	Method *method = new Method(cls, returnCls, name, args);
	method->set_callable(cb);
	const_cast<Class &>(cls).addMethod(method);
}

__register_static_method__::__register_static_method__(__callable__ *cb, const Class *pclass, const char *type, const char *name, const char *args)
{
	//StaticMethod* method = new StaticMethod(pclass, type, name, args);
	//(const_cast<Class *>(pclass))->_addStaticMethod(method, cb);
}

class ClassManager final
{
	ClassManager(const ClassManager &) = delete;
	ClassManager &operator=(const ClassManager &) = delete;

  public:
	ClassManager() {}
	~ClassManager() {}

	void registerClass(const Class &cls)
	{
		if (cls.isBase(EntityObject::getClassStatic()))
		{
			_classEntity.insert(std::make_pair(cls.getName(), &cls));
		}
		else if (cls.isBase(BaseController::getClassStatic()))
		{
			_classController.insert(std::make_pair(cls.getName(), &cls));
		}

		_classAll.insert(std::make_pair(cls.getName(), &cls));
	}

	const Class &forName(const String &name)
	{
		auto iter = _classAll.find(name);
		if (iter == _classAll.end())
		{
		}

		return *iter->second;
	}

	const std::map<String, const Class *const> &getEntityClasses() const { return _classEntity; }
	const std::map<String, const Class *const> &getControllerClasses() const { return _classController; }

  private:
	std::map<String, const Class *const> _classAll;
	std::map<String, const Class *const> _classEntity;
	std::map<String, const Class *const> _classController;
};
ClassManager &geminiAfxGetClassManager()
{
	static ClassManager manager;
	return manager;
}
const std::map<String, const Class *const> &geminiAfxEntityClasses()
{
	return geminiAfxGetClassManager().getEntityClasses();
}
const std::map<String, const Class *const> &geminiAfxControllerClasses()
{
	return geminiAfxGetClassManager().getControllerClasses();
}

SmartPtr<EntityObject> PropertyRefHelp::get(const EntityObject *entity, Int sign)
{
	return entity->_relations[sign]->get();
}
void PropertyRefHelp::set(EntityObject *entity, Int sign, const SmartPtr<EntityObject> &relaEntity)
{
	SmartPtr<EntityObject> entitySPtr;
	entitySPtr.wrapRawPointer(entity);
	IocRelation::set(entitySPtr, sign, relaEntity);
}
const IList &PropertyRefHelp::getList(const EntityObject *entity, Int sign)
{
	return *((const IList *)(entity->_relations[sign]));
}

namespace ns_class
{

String getNameImpl(const Char *name)
{
	const Char *pLastSlash = strrchr(name, ':');
	if (pLastSlash == nullptr)
	{
		pLastSlash = strrchr(name, ' ');
	}
	return pLastSlash != nullptr ? pLastSlash + 1 : name;
}

} // namespace ns_class

Int Class::s_maxIndex = 0;
Class::Class(const Char *name, const Class *superClass, PNewInstance instance)
	: _isEnum(false), _index(s_maxIndex++), _enumHelper(nullptr), _superClass(superClass), _instance(instance), _name(name)
{
	geminiAfxGetClassManager().registerClass(*this);
}

Class::~Class()
{
}

Int Class::max_limits()
{
	return 1024;
}

Boolean Class::hasSuper() const
{
	return _superClass != nullptr;
}

Boolean Class::isBase(const Class &cls) const
{
	const Class *temp = this;
	while (temp->hasSuper())
	{
		temp = &temp->getSuperClass();
		if (*temp == cls)
		{
			return true;
		}
	}
	return false;
}

Int Class::getEnum(const String &name) const
{
	THROW_IF(!isEnum(), MatchException, name, "is not enum")
	THROW_IF(_enumHelper == nullptr, RegisterException, name, " not registed")
	return _enumHelper->getValue(name);
}

const Class &Class::forName(const String &name)
{
	return geminiAfxGetClassManager().forName(name);
}

const Field &Class::getField(const String &name) const
{
	std::map<String, const Field *>::const_iterator iter = _fields.find(name);
	THROW_IF(iter == _fields.end(), NoSuchFieldException, name, " is not existed in class ", getName())
	return *(iter->second);
}

void Class::addField(const Field *field)
{
	std::map<String, const Field *>::iterator iter = _fields.find(field->getName());
	THROW_IF(iter != _fields.end(), RegisterException, field->getName(), " has existed in class ", getName())
	_fields.insert(std::make_pair(field->getName(), field));
}

void Class::addMethod(const Method *method)
{
	std::map<String, const Method *>::iterator iter = _methods.find(method->getName());
	THROW_IF(iter != _methods.end(), RegisterException, method->getName(), " has existed in class ", getName());
	_methods.insert(std::make_pair(method->getName(), method));
}

Int EnumHelper::getValue(const String &value) const
{
	std::map<String, Int>::const_iterator iter = _info.find(value);
	THROW_IF(iter == _info.end(), NoSuchElementException, value);
	return iter->second;
}

void EnumHelper::SplitEnumString(const char *str)
{
	/*const char * p = str;
		Int index = 0;
		while (std::isspace(*p)) p++;
		while (*p != '\0') {
			const char* temp = p;
			while (*p == '_' || std::isdigit(*p) || std::isalpha(*p)) p++;
			String name(temp, p - temp);
			while (std::isspace(*p)) p++;

			if (*p == '\0') {
				s_info.insert(std::make_pair(name, index++));
				break;
			}

			if (*p == '=') {
				p++;
				while (std::isspace(*p)) p++;
				temp = p;
				while (std::isdigit(*p)) p++;
				String value(temp, p - temp);
				index = StringUtil::convert<Int>(value.c_str());
				while (std::isspace(*p)) p++;
			}

			if (*p == ',') {
				s_info.insert(std::make_pair(name, index++));
			}
			p++;

			while (std::isspace(*p)) p++;
		}*/
}

} // namespace gemini