#ifndef GEMINI_DataNode_INCLUDE
#define GEMINI_DataNode_INCLUDE
#include "../Common.h"

namespace boost {
	namespace property_tree {
		template < class Key, class Data, class KeyCompare = std::less<Key> > class basic_ptree;
		typedef basic_ptree<std::string, std::string> ptree;
	}
}

namespace gemini {

class CORE_API DataNode
{
public:
	typedef boost::property_tree::ptree node_type;
	typedef node_type* node_ptr;
	DataNode() : _pNode(nullptr) { }
	DataNode(node_ptr node, const Char* name = u8"") : _pNode(node), _name(name) {}
	~DataNode() {}
	DataNode& operator= (node_ptr node) { _pNode = node; _name.clear(); return *this; }
	DataNode& operator= (const DataNode& node) { _pNode = node._pNode; _name = node._name; return *this; }

	Boolean valid() const { return _pNode != nullptr; }

	String getName() const { return _name; }

	String getValue() const;
	template <typename T>
	T getValue() const {
		return getValue().Convert<T>();
	}

	void setValue(const Char* val);
	void setValue(const String& val) { setValue(val.c_str()); }
	template <typename T>
	void setValue(T val) {
		setValue(String::Format(val).c_str());
	}

	DataNode getNode(const Char* tagName, Boolean bCreate = false);
	DataNode getNode(const String& tagName, Boolean bCreate = false) { return getNode(tagName.c_str(), bCreate); }
	DataNode createNode();
	DataNode createNode(const Char* tagName);
	DataNode createNode(const String& tagName) { return createNode(tagName.c_str()); }
	void removeNode(const Char* tagName);
	void removeNode(const String& tagName) { removeNode(tagName.c_str()); }

	template <typename FUN>
	void foreach(FUN fun) const {
		std::vector<DataNode> vecNode = GetChilds();
		for (DataNode node : vecNode) {
			fun(node);
		}
	}

	void addNode(DataNode node);
private:
	std::vector<DataNode> GetChilds() const;
	
protected:
	node_ptr _pNode;
	String _name;
};

}
#endif // GEMINI_DataNode_INCLUDE