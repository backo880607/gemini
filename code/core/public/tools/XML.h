#ifndef GEMINI_XML_INCLUDE
#define GEMINI_XML_INCLUDE
#include "../api/DataNode.h"

namespace gemini {

class CORE_API XMLNode : public DataNode {
 public:
  XMLNode() {}
  XMLNode(const DataNode& node) : DataNode(node) {}
  ~XMLNode() {}
  XMLNode& operator=(const DataNode& node) {
    DataNode::operator=(node);
    return *this;
  }

  String getAttribute(const Char* attr) const;
  String getAttribute(const String& attr) const {
    return getAttribute(attr.c_str());
  }
  template <typename T>
  T getAttribute(const Char* attr) const {
    return StringUtil::convert<T>(getAttribute(attr).c_str());
  }
  template <typename T>
  T getAttribute(const String& attr) const {
    return getAttribute<T>(attr.c_str());
  }

  String getValue() const;
  template <typename T>
  T getValue() const {
    return StringUtil::convert<T>(getValue().c_str());
  }

  void setAttribute(const Char* attr, const Char* val);
  void setAttribute(const String& attr, const Char* val) {
    setAttribute(attr.c_str(), val);
  }
  void setAttribute(const Char* attr, const String& val) {
    setAttribute(attr, val.c_str());
  }
  void setAttribute(const String& attr, const String& val) {
    setAttribute(attr.c_str(), val.c_str());
  }
  template <typename T>
  void setAttribute(const Char* attr, T val) {
    setAttribute(attr, StringUtil::format(val).c_str());
  }
  template <typename T>
  void SetAttribute(const String& attr, T val) {
    setAttribute(attr.c_str(), StringUtil::format(val).c_str());
  }

  void removeAttribute(const Char* attr);
  void removeAttribute(const String& attr) { removeAttribute(attr.c_str()); }

 private:
  String getXmlAttrName(const Char* attr) const {
    String attrName = "<xmlattr>.";
    attrName.append(attr);
    return attrName;
  }
};

class CORE_API XMLFile {
 public:
  typedef XMLNode::node_type node_type;
  enum class File_Mode { NormalFile = 1, CreateFile, ClearFile };

  XMLFile(const String& name, File_Mode mode = File_Mode::NormalFile);
  ~XMLFile();
  Boolean open(const String& name, File_Mode mode = File_Mode::NormalFile);
  Boolean valid() const { return _ptree != nullptr; }
  Boolean write() { return write(_fileName); }
  Boolean write(const String& name, File_Mode mode = File_Mode::NormalFile);

  DataNode getNode();
  DataNode getNode(const Char* tagName);
  DataNode getNode(const String& tagName) { return getNode(tagName.c_str()); }

  DataNode createNode(const Char* tagName);
  DataNode createNode(const String& tagName) {
    return createNode(tagName.c_str());
  }
  void remove();

  static void foreach (const Char* directory,
                       std::function<void(XMLFile&)> fun);
  static void foreach_recursion(const Char* directory,
                                std::function<void(XMLFile&)> fun);

 private:
  void clear();
  Boolean proXMLFile(String& path, File_Mode mode);

 private:
  std::unique_ptr<node_type> _ptree;
  String _fileName;
};

class CORE_API XML {
 public:
  typedef XMLNode::node_type node_type;

  XML();
  XML(const Char* val);
  ~XML();

  Boolean valid() const { return !_ptree; }

  Boolean write(std::ostream& ss);

  DataNode getNode();
  DataNode getNode(const Char* tagName);
  DataNode getNode(const String& tagName) { return getNode(tagName.c_str()); }

  DataNode createNode(const Char* tagName);
  DataNode createNode(const String& tagName) {
    return createNode(tagName.c_str());
  }

 private:
  std::unique_ptr<node_type> _ptree;
};

}  // namespace gemini
#endif  // GEMINI_XML_INCLUDE