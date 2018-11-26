#include "api/DataNode.h"
#include "message/Message.h"
#include "tools/ClassUtil.h"

#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace gemini {

String DataNode::getValue() const { return _pNode->get_value<String>(); }

void DataNode::setValue(const Char* val) { _pNode->put_value(val); }

DataNode DataNode::getNode(const Char* tagName, Boolean bCreate /* = false */) {
  auto rt = _pNode->get_child_optional(tagName);
  if (rt) return &(*rt);

  if (bCreate) return &_pNode->put_child(tagName, node_type(""));

  return DataNode();
}

DataNode DataNode::createNode() { return &_pNode->add_child("", node_type()); }

DataNode DataNode::createNode(const Char* tagName) {
  return &_pNode->put_child(tagName, node_type(""));
}

void DataNode::removeNode(const Char* tagName) { _pNode->erase(tagName); }

std::vector<DataNode> DataNode::getChilds() const {
  std::vector<DataNode> vecNode;
  for (auto pt = _pNode->begin(); pt != _pNode->end(); ++pt) {
    if (pt->first == "<xmlattr>") continue;
    vecNode.push_back(DataNode(&pt->second, pt->first.c_str()));
  }

  return vecNode;
}

void DataNode::addNode(DataNode node) {
  // m_pNode.put_child(m_pNode., node.m_pNode);
}

Object::SPtr DataNode::getObject(const Class& cls) const {
  std::vector<DataNode> fieldNodes = getChilds();
  if (fieldNodes.empty()) {
    return nullptr;
  }

  Object::SPtr object = create(cls);
  for (DataNode fieldNode : fieldNodes) {
    const String& name = fieldNode.getName();
    try {
      const Field& field = ClassUtil::getField(cls, name);
      StringUtil::setField(object, field, fieldNode.getValue().c_str());
    } catch (const NoSuchFieldException&) {
    }
  }
  return object;
}

std::vector<Object::SPtr> DataNode::getObjectList(const Class& cls) const {
  std::vector<Object::SPtr> objects;
  for (DataNode objectNode : getChilds()) {
    objects.push_back(objectNode.getObject(cls));
  }
  return objects;
}

void DataNode::setObject(const Object::SPtr& object) {
  if (!object.valid()) return;

  const Class& cls = object->getClass();
  ClassUtil::foreach_fields(cls, [&](const Field& field) {
    DataNode fieldNode = createNode(field.getName());
    fieldNode.setValue(StringUtil::getField(object, field));
  });
}

void DataNode::setObject(const std::vector<Object::SPtr>& objects) {
  for (Object::SPtr object : objects) {
    DataNode objectNode = createNode();
    objectNode.setObject(object);
  }
}
void DataNode::setObject(const IList& objects) {
  IList::Iterator iter = objects.iterator();
  while (iter.hasNext()) {
    Object::SPtr object = iter.next<Object>();
    createNode().setObject(object);
  }
}

Object::SPtr DataNode::create(const Class& cls) const {
  Object* pObject = (Object*)cls.newInstance();
  Object::SPtr object;
  object.wrapRawPointer(pObject);
  return object;
}

InitFile::InitFile(const String& path) { open(path); }

InitFile::~InitFile() {}

void InitFile::open(const String& path) {
  _ptree = nullptr;
  if (path.empty()) return;

  String filePath = path;
  const String strExtension = StringUtil::get_tail(path.c_str(), ".");
  if (strExtension.empty())
    filePath += ".ini";
  else if (strExtension != "ini")
    return;

  try {
    if (_ptree == nullptr) {
      _ptree.reset(new boost::property_tree::iptree());
    }
    std::locale utf8Locale(
        std::locale(),
        new boost::program_options::detail::utf8_codecvt_facet());
    boost::property_tree::ini_parser::read_ini(filePath, *_ptree, utf8Locale);
    _filePath = filePath;
  } catch (boost::property_tree::ini_parser_error& err) {
    _ptree = nullptr;
  }
}

DataNode InitFile::getNode() { return &(*_ptree); }

DataNode InitFile::getNode(const Char* tagName) {
  return &_ptree->get_child(tagName);
}

}  // namespace gemini