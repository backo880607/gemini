#include "tools/Json.h"

#include "message/Log.h"
#include "tools/File.h"

#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace gemini {

Json::Json() : _ptree(new boost::property_tree::iptree()) {}

Json::Json(const Char* val) { reset(val); }

Json::~Json() {}

void Json::reset(const Char* val) {
  if (val == nullptr) {
    _ptree = nullptr;
    return;
  }
  std::stringstream ss(val);
  try {
    _ptree.reset(new JsonNode::node_type());
    boost::property_tree::json_parser::read_json(ss, *_ptree);
  } catch (boost::property_tree::json_parser_error& err) {
    _ptree = nullptr;
    LOG_ERROR.log(err.what());
  }
}

void Json::write(std::basic_ostream<Char>& ss, Boolean bPretty /* = false */) {
  try {
    boost::property_tree::json_parser::write_json(ss, *_ptree, bPretty);
  } catch (boost::property_tree::json_parser_error& err) {
    LOG_ERROR.log(err.what());
  }
}

void Json::read(std::basic_istream<Char>& ss) {
  try {
    boost::property_tree::json_parser::read_json(ss, *_ptree);
  } catch (boost::property_tree::json_parser_error& err) {
    _ptree = nullptr;
    LOG_ERROR.log(err.what());
  }
}

DataNode Json::getNode() { return &(*_ptree); }

DataNode Json::getNode(const Char* tagName) {
  return &_ptree->get_child(tagName);
}

DataNode Json::createNode(const Char* tagName) {
  return &_ptree->add_child(tagName, node_type(u8""));
}

JsonFile::JsonFile(const String& name,
                   File_Mode mode /*= File_Mode::NormalFile*/) {
  open(name, mode);
}

JsonFile::~JsonFile() { clear(); }

void JsonFile::clear() {
  _ptree = nullptr;
  _fileName.clear();
}

Boolean JsonFile::open(const String& name,
                       File_Mode mode /*= File_Mode::NormalFile*/) {
  clear();
  String xmlName = name;
  if (!ProJsonFile(xmlName, mode)) return false;

  try {
    _ptree.reset(new boost::property_tree::iptree());
    std::locale utf8Locale(
        std::locale(),
        new boost::program_options::detail::utf8_codecvt_facet());
    boost::property_tree::json_parser::read_json(xmlName, *_ptree, utf8Locale);
  } catch (boost::property_tree::json_parser_error& err) {
    _ptree = nullptr;
    LOG_ERROR.log(err.what());
    return false;
  }
  return true;
}

Boolean JsonFile::ProJsonFile(String& path, File_Mode mode) {
  if (path.empty()) return false;

  const String strExtension = StringUtil::get_tail(path.c_str(), ".");
  if (strExtension.empty())
    path += ".json";
  else if (strExtension != "json")
    return false;

  File file(path.c_str());
  switch (mode) {
    case File_Mode::FM_NormalFile: {
      if (!file.getFilePath().isExist() ||
          !file.open(std::ios_base::in | std::ios_base::out))
        return false;

      file.close();
    } break;
    case File_Mode::FM_CreateFile: {
      if (!file.getFilePath().isExist()) {
        node_type json;
        std::locale utf8Locale(
            std::locale(),
            new boost::program_options::detail::utf8_codecvt_facet());
        boost::property_tree::json_parser::write_json(path, json, utf8Locale);
      }
    } break;
    case File_Mode::FM_ClearFile: {
      file.open();
      file.close();

      node_type json;
      std::locale utf8Locale(
          std::locale(),
          new boost::program_options::detail::utf8_codecvt_facet());
      boost::property_tree::json_parser::write_json(path, json, utf8Locale);
    } break;
    default:
      return false;
  }
  _fileName = path;
  return true;
}

void JsonFile::write(const String& name,
                     File_Mode mode /*= File_Mode::NormalFile*/) {
  String xmlName = name;
  if (!ProJsonFile(xmlName, mode)) return;

  try {
    std::locale utf8Locale(
        std::locale(),
        new boost::program_options::detail::utf8_codecvt_facet());
    boost::property_tree::json_parser::write_json(xmlName, *_ptree, utf8Locale);
  } catch (boost::property_tree::json_parser_error& err) {
    LOG_ERROR.log(err.what());
  }
}

void JsonFile::remove() {
  File file(_fileName.c_str());
  file.remove();
}

void JsonFile::foreach (const Char* directory,
                        std::function<void(JsonFile&)> fun) {
  FilePath dirPath(directory);
  if (dirPath.valid()) {
    std::vector<FilePath> children = dirPath.getChildren();
    for (const FilePath& filePath : children) {
      JsonFile jsonFile(filePath.string());
      if (jsonFile.valid()) {
        fun(jsonFile);
      }
    }
  }
}

void JsonFile::foreach_recursion(const Char* directory,
                                 std::function<void(JsonFile&)> fun) {
  FilePath dirPath(directory);
  if (dirPath.valid()) {
    std::vector<FilePath> children = dirPath.getChildrenRecursion();
    for (const FilePath& filePath : children) {
      JsonFile jsonFile(filePath.string());
      if (jsonFile.valid()) {
        fun(jsonFile);
      }
    }
  }
}

}  // namespace gemini