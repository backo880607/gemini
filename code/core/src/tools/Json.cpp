#include "tools/Json.h"

#include "tools/StringUtil.h"
#include "tools/File.h"
#include "message/Message.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace gemini {

JsonFile::JsonFile(const String& name, File_Mode mode /*= File_Mode::NormalFile*/)
{
	open(name, mode);
}

JsonFile::~JsonFile()
{

}

Boolean JsonFile::open(const String& name, File_Mode mode /*= File_Mode::NormalFile*/)
{
	String xmlName = name;
	if (!ProJsonFile(xmlName, mode))
		return false;

	try {
		if (_ptree == nullptr) {
			_ptree.reset(new boost::property_tree::iptree());
		}
		std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
		boost::property_tree::json_parser::read_json(xmlName, *_ptree, utf8Locale);
	} catch (boost::property_tree::json_parser_error& err) {
		_ptree = nullptr;
		return false;
	}
	return true;
}

Boolean JsonFile::ProJsonFile(String& path, File_Mode mode)
{
	if (path.empty())
		return false;

	const String strExtension = StringUtil::get_tail(path.c_str(), ".");
	if (strExtension.empty())
		path += ".json";
	else if (strExtension != "json")
		return false;

	File file(path.c_str());
	switch (mode) {
	case File_Mode::FM_NormalFile: 
	{
		if (!file.getFilePath().isExist() || !file.open(std::ios_base::in | std::ios_base::out))
			return false;

		file.close();
	}
	break;
	case File_Mode::FM_CreateFile: 
	{
		if (!file.getFilePath().isExist())
		{
			node_type json;
			std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
			boost::property_tree::json_parser::write_json(path, json, utf8Locale);
		}
	}
	break;
	case File_Mode::FM_ClearFile:
	{
		file.open();
		file.close();

		node_type json;
		std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
		boost::property_tree::json_parser::write_json(path, json, utf8Locale);
	}
	break;
	default:
		return false;
	}
	_fileName = path;
	return true;
}

void JsonFile::write(const String& name, File_Mode mode /*= File_Mode::NormalFile*/)
{
	String xmlName = name;
	if (!ProJsonFile(xmlName, mode))
		return;

	try {
		std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
		boost::property_tree::json_parser::write_json(xmlName, *_ptree, utf8Locale);
	} catch (boost::property_tree::json_parser_error& err) {
	}
}

DataNode JsonFile::getNode()
{
	return &(*_ptree);
}

DataNode JsonFile::getNode(const Char* tagName)
{
	return &_ptree->get_child(tagName);
}

DataNode JsonFile::createNode(const Char* tagName)
{
	return &_ptree->add_child(tagName, node_type(u8""));
}

void JsonFile::remove()
{
	File file(_fileName.c_str());
	file.remove();
}

Json::Json()
{
}

Json::Json(const Char* val)
{
	std::stringstream ss(val);
	try {
		boost::property_tree::json_parser::read_json(ss, *_ptree);
	} catch (boost::property_tree::json_parser_error& err) {
		_ptree = nullptr;
	}
}

Json::~Json()
{
}

void Json::write(std::basic_ostream<Char>& ss, Boolean bPretty /* = false */)
{
	try {
		boost::property_tree::json_parser::write_json(ss, *_ptree, bPretty);
	} catch (boost::property_tree::json_parser_error& err) {
		
	}
}

void Json::read(std::basic_istream<Char>& ss)
{
	try {
		boost::property_tree::json_parser::read_json(ss, *_ptree);
	} catch (boost::property_tree::json_parser_error& err) {
		_ptree = nullptr;
	}
}

DataNode Json::getNode()
{
	return &(*_ptree);
}

DataNode Json::getNode(const Char* tagName)
{
	return &_ptree->get_child(tagName);
}

DataNode Json::createNode(const Char* tagName)
{
	return &_ptree->add_child(tagName, node_type(u8""));
}

}