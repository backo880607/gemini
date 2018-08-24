#include "api/DataNode.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>

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

std::vector<DataNode> DataNode::GetChilds() const {
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