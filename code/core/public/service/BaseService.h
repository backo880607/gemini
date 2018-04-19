#ifndef GEMINI_BaseService_INCLUDE
#define GEMINI_BaseService_INCLUDE
#include "../Object.h"

namespace gemini {

class IBaseService;
class CORE_API BaseService
{
	EntityObject::SPtr createImpl(const Class& cls, Long id) const;
	EntityObject::SPtr createTempImpl(const Class& cls) const;
	EntityObject::SPtr getImpl(const Class& cls) const;
	EntityObject::SPtr getImpl(const Class& cls, Long id) const;
	EntityObject::SPtr getInheritImpl(const Class& cls, Long id) const;
	const IList& getListImpl(const Class& cls) const;

	EntityObject::SPtr getImpl(EntityObject::SPtr entity, const std::vector<UInt>& signs) const;
	const IList& getListImpl(EntityObject::SPtr entity, const std::vector<UInt>& signs) const;

	template<typename... A> class RefSign {};
	template<typename Head, typename... Tail> class RefSign<Head, Tail...> {
	public:
		typedef typename RefSign<Tail...>::value_type value_type;
		static void collect(std::vector<gemini::UInt>& vals) {
			vals.push_back(Head::index());
			RefSign<Tail...>::collect(vals);
		}
	};
	template<typename Tail> class RefSign<Tail> {
	public:
		typedef typename Tail value_type;
		static void collect(std::vector<gemini::UInt>& vals) {
			vals.push_back(Tail::index());
		}
	};
	template<> class RefSign<> {};  // 边界条件

public:

	// 创建实体对象
	template <typename T>
	typename T::SPtr create(Long id = 0) const {
		return createImpl(T::getClassStatic(), id);
	}
	template <typename T>
	typename T::const_reference create(const EntityObject::SPtr& entity) const {
		T::const_reference relaEntity = create<typename T::value_type>();
		IocRelation::set(entity, T::index(), relaEntity);
	}
	template <typename T>
	typename T::SPtr createTemp() const {
		return createTempImpl(T::getClassStatic());
	}

	template <typename T>
	typename T::SPtr get() const {
		return getImpl(T::getClassStatic());
	}

	template <typename T>
	typename T::SPtr get(Long id) const {
		return getImpl(T::getClassStatic(), id);
	}

	template <typename T>
	typename T::SPtr getInherit(Long id) const {
		return getInheritImpl(T::getClassStatic(), id);
	}

	template <class T, typename Filter>
	typename T::SPtr get(Filter filter) const {

	}

	template <class T, typename Fun>
	void foreach(Fun fun) const {
		IList::Iterator iter = getListImpl(T::getClassStatic()).iterator();
		while (iter.hasNext()) {
			fun(iter.next<T>());
		}
	}

	template <typename T>
	const IList& getList() const {
		return getListImpl(T::getClassStatic());
	}

	template <class T, typename Filter>
	const IList& getList(Filter filter) const {
		std::list<typename T::SPtr> entities = getList<T>();
		for (std::list<typename T::SPtr>::iterator iter = entities.begin();
			iter != entities.end(); ++iter) {
			if (!filter(*iter)) {
				iter = entities.erase(iter);
			}
		}
		return entities;
	}
	template <class T>
	const IList& getList(const Char* strExpression) const {

	}

	template <typename T, typename... Ref>
	typename T::SPtr get(EntityObject::SPtr entity) const {
		std::vector<gemini::UInt> signs;
		RefSign<Ref...>::collect(signs);
		return getImpl(entity, signs);
	}

	template <typename T, typename... Ref>
	typename T::SPtr get(EntityObject::SPtr entity, std::function<Boolean(typename T::SPtr)> filter) const {
		std::vector<gemini::UInt> signs;
		RefSign<Ref...>::collect(signs);
		for (typename T::SPtr target : getListImpl(entity, signs)) {
			if (filter(target)) {
				return target;
			}
		}

		return nullptr;
	}

	template <typename T, typename... Ref>
	void foreach(EntityObject::SPtr entity, std::function<void(typename T::SPtr)> fun) const {
		std::list<typename T::SPtr> entities = getList<T, Ref...>(entity);
		for (typename T::SPtr target : entities) {
			fun(target);
		}
	}

	template <typename T, typename... Ref>
	std::list<typename T::SPtr> getList(EntityObject::SPtr entity) const {
		std::vector<gemini::UInt> signs;
		RefSign<Ref...>::collect(signs);
		std::list<typename T::SPtr> entities;
		for (typename T::SPtr entity : getListImpl(entity, signs)) {
			entities.push_back(entity);
		}
		return entities;
	}

	template <class T, typename... Ref>
	std::list<typename T::SPtr> getList(EntityObject::SPtr entity, std::function<Boolean(typename T::SPtr)> filter) const {
		std::list<typename T::SPtr> entities = getList<T>();
		for (std::list<typename T::SPtr>::iterator iter = entities.begin();
			iter != entities.end(); ++iter) {
			if (!filter(*iter)) {
				iter = entities.erase(iter);
			}
		}
		return entities;
	}
};

extern CORE_API void gemini_afx_service_service(const String& name, const BaseService* service);
extern CORE_API void gemini_afx_service_interface(const String& name, const IBaseService* service);
template <class T, class ...I>
class ServiceRegister {
	template <typename... A> struct InterfaceHelper {};
	template <class Head, class ...Tail> struct InterfaceHelper<Head, Tail...> {
		static void registerInterface(const IBaseService* service) {
			gemini::gemini_afx_service_interface(Class::getName<Head>(), service);
			InterfaceHelper<Tail...>::registerInterface(service);
		}
	};
	template <> struct InterfaceHelper<> {
		static void registerInterface(const IBaseService* service) {}
	};
public:
	ServiceRegister() {
		String name = Class::getName<T>();
		gemini::gemini_afx_service_service(name, &_service);
		InterfaceHelper<I...>::registerInterface(&_service);
	}
	~ServiceRegister() {}

private:
	T _service;
};

class CORE_API ServiceAutowired
{
	ServiceAutowired(const ServiceAutowired&) = delete;
	ServiceAutowired& operator= (const ServiceAutowired&) = delete;
protected:
	ServiceAutowired(const String& iName);
	virtual ~ServiceAutowired() {}
	friend class ServiceMgr;
	virtual void assign(const IBaseService* service) = 0;
};

namespace service {

class callable {
public:
	virtual Boolean invoke(const BaseService* service, const EntityObject::SPtr& entity) = 0;
};
template <class SRV, typename FUN>
class callableHolder : public callable {
	FUN _fun;
public:
	callableHolder(FUN fun) : _fun(fun) {}
	virtual Boolean invoke(const BaseService* service, const EntityObject::SPtr& entity) override {
		return (((const SRV*)service)->*_fun)(entity);
	}
};
CORE_API void register_service_method_impl(const String& name, const String& method, callable* caller);

}

template <class SRV>
struct __register_service_method__ {
	template <typename FUN>
	__register_service_method__(FUN fun, const String& srvName, const String& methodName) {
		service::callable* caller = new service::callableHolder<SRV, FUN>(fun);
		service::register_service_method_impl(srvName, methodName, caller);
	}
};

#define SERVICE_AUTOWIRED(I_TYPE, I_NAME)\
public:\
	class __field_##I_NAME : public gemini::ServiceAutowired {\
		typedef const I_TYPE* const_reference;\
		const_reference _value;\
	public:\
		__field_##I_NAME(): gemini::ServiceAutowired(#I_TYPE) {}\
		~__field_##I_NAME() {}\
		const_reference operator-> () { return _value; }\
		operator const_reference() { return _value; }\
	protected:\
		virtual void assign(const IBaseService* service) { _value = (const_reference)service; }\
	} _##I_NAME;\


#define SERVICE_REQUIRED(I_TYPE, I_NAME)\
public:\
	class __field_##I_NAME {\
		typedef const I_TYPE* const_reference;\
		const_reference _value;\
	public:\
		__field_##I_NAME() : _value(nullptr) {}\
		~__field_##I_NAME() {}\
		const_reference operator-> () { sure();	return _value; }\
		operator const_reference() { sure(); return _value; }\
	private:\
		void sure() { if (_value == nullptr) { _value = gemini::gemini_afx_service_interface_get(#I_TYPE); } }\
	} _##I_NAME;\


#define SERVICE_METHOD(CLS, METHOD_NAME) \
private:\
	struct __method_##METHOD_NAME {\
		__method_##METHOD_NAME() { typedef gemini::Boolean (CLS##Service::*method_ptr_type)(const gemini::SmartPtr<CLS>&) const;\
			method_ptr_type method_ptr = &CLS##Service::METHOD_NAME; \
			static gemini::__register_service_method__<CLS##Service> reg(method_ptr, gemini::Class::getName<CLS##Service>(), #METHOD_NAME); }\
	} __method_##METHOD_NAME;\
public: virtual gemini::Boolean METHOD_NAME(const gemini::SmartPtr<CLS>& entity) const override;

}
#endif // GEMINI_BaseService_INCLUDE