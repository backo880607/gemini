#ifndef GEMINI_DataNode_INCLUDE
#define GEMINI_DataNode_INCLUDE
#include "../Core.h"

namespace boost {
namespace property_tree {
namespace detail {
template <typename T>
struct less_nocase;
}

template <class Key, class Data, class KeyCompare>
class basic_ptree;
typedef basic_ptree<std::string, std::string, detail::less_nocase<std::string> >
    iptree;
}  // namespace property_tree
}  // namespace boost

namespace gemini {

class CORE_API DataNode {
 public:
  typedef boost::property_tree::iptree node_type;
  typedef node_type* node_ptr;
  DataNode() : _pNode(nullptr) {}
  DataNode(node_ptr node, const Char* name = "") : _pNode(node), _name(name) {}
  ~DataNode() {}
  DataNode& operator=(node_ptr node) {
    _pNode = node;
    _name.clear();
    return *this;
  }
  DataNode& operator=(const DataNode& node) {
    _pNode = node._pNode;
    _name = node._name;
    return *this;
  }

  Boolean valid() const { return _pNode != nullptr; }

  String getName() const { return _name; }

  String getValue() const;
  template <typename T>
  T getValue() const {
    return StringUtil::convert<T>(getValue().c_str());
  }

  void setValue(const Char* val);
  void setValue(const String& val) { setValue(val.c_str()); }
  template <typename T>
  void setValue(T val) {
    setValue(StringUtil::format(val));
  }

  DataNode getNode(const Char* tagName, Boolean bCreate = false);
  DataNode getNode(const String& tagName, Boolean bCreate = false) {
    return getNode(tagName.c_str(), bCreate);
  }
  DataNode createNode();
  DataNode createNode(const Char* tagName);
  DataNode createNode(const String& tagName) {
    return createNode(tagName.c_str());
  }
  void removeNode(const Char* tagName);
  void removeNode(const String& tagName) { removeNode(tagName.c_str()); }

  template <typename FUN>
  void foreach (FUN fun) const {
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

}  // namespace gemini
#endif  // GEMINI_DataNode_INCLUDE