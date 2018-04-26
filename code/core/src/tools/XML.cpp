#include "tools/XML.h"
#include "tools/File.h"
#include "message/Log.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace gemini {


String XMLNode::getAttribute(const Char* attr) const {
	return _pNode->get<String>(getXmlAttrName(attr).c_str());
}

String XMLNode::getValue() const {
	return _pNode->get_value<String>();
}

void XMLNode::setAttribute(const Char* attr, const Char* val) {
	_pNode->put(getXmlAttrName(attr).c_str(), val);
}

void XMLNode::removeAttribute(const Char* attr) {
	_pNode->erase(getXmlAttrName(attr));
}


XMLFile::XMLFile(const String& name, File_Mode mode /* = File_Mode::NormalFile */) {
	open(name, mode);
}

XMLFile::~XMLFile() {
	clear();
}

void XMLFile::clear() {
}

Boolean XMLFile::proXMLFile(String& path, File_Mode mode) {
	using namespace boost::property_tree;
	const String strExtension = StringUtil::get_tail(path.c_str(), ".");
	if (strExtension.empty())
		path += ".xml";
	else if (strExtension != "xml")
		return false;

	File file(path.c_str());
	switch (mode) {
	case File_Mode::NormalFile: {
		if (!file.getFilePath().isExist() || !file.open(std::ios_base::in | std::ios_base::out))
			return false;

		file.close();
	}
	break;
	case File_Mode::CreateFile: {
		if (!file.getFilePath().isExist()) {
			node_type xml;
			std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
			write_xml(path.c_str(), xml, utf8Locale);
		}
	}
	break;
	case File_Mode::ClearFile: {
		file.open();
		file.close();

		node_type xml;
		std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
		write_xml(path.c_str(), xml, utf8Locale);
	}
	break;
	default:
		return false;
	}
	_fileName = path;
	return true;
}

Boolean XMLFile::open(const String& name, File_Mode mode /* = File_Mode::NormalFile */) {
	using namespace boost::property_tree;
	clear();
	String xmlName = name;
	if (!proXMLFile(xmlName, mode))
		return false;

	try {
		if (_ptree == nullptr) {
			_ptree.reset(new boost::property_tree::iptree());
		}
		std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
		read_xml(xmlName.c_str(), *_ptree, 0, utf8Locale);
	} catch (xml_parser_error& err) {
		_ptree = nullptr;
		LOG_ERROR.log(err.what());
		return false;
	}
	return true;
}

Boolean XMLFile::write(const String& name, File_Mode mode /* = File_Mode::NormalFile */) {
	String xmlName = name;
	if (!proXMLFile(xmlName, mode))
		return false;

	using namespace boost::property_tree;
	try {
		std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
		write_xml(xmlName.c_str(), *_ptree, utf8Locale);
	} catch (xml_parser_error& err) {
		LOG_ERROR.log(err.what());
		return false;
	}

	return true;
}

DataNode XMLFile::getNode() {
	return DataNode(&(*_ptree));
}

DataNode XMLFile::getNode(const Char* tagName) {
	return DataNode(&_ptree->get_child(tagName), tagName);
}

DataNode XMLFile::createNode(const Char* tagName) {
	return DataNode(&_ptree->add_child(tagName, node_type("")), tagName);
}

void XMLFile::remove() {
	File file(_fileName.c_str());
	file.remove();
}

void XMLFile::foreach(const Char * directory, std::function<void(XMLFile&)> fun) {
	FilePath dirPath(directory);
	if (dirPath.valid()) {
		std::vector<FilePath> children = dirPath.getChildren();
		for (const FilePath& filePath : children) {
			XMLFile xmlFile(filePath.string());
			if (xmlFile.valid()) {
				fun(xmlFile);
			}
		}
	}
}

void XMLFile::foreach_recursion(const Char * directory, std::function<void(XMLFile&)> fun) {
	FilePath dirPath(directory);
	if (dirPath.valid()) {
		std::vector<FilePath> children = dirPath.getChildrenRecursion();
		for (const FilePath& filePath : children) {
			XMLFile xmlFile(filePath.string());
			if (xmlFile.valid()) {
				fun(xmlFile);
			}
		}
	}
}


XML::XML() {
	_ptree->add_child("YuKon", node_type(""));
}

XML::XML(const Char* val) {
	std::stringstream ss(val);
	try {
		read_xml(ss, *_ptree);
	} catch (boost::property_tree::xml_parser_error& err) {
		_ptree->clear();
		LOG_ERROR.log(err.what());
	}
}

XML::~XML() {
}

Boolean XML::write(std::ostream& ss) {
	try {
		boost::property_tree::write_xml(ss, *_ptree);
	} catch (boost::property_tree::xml_parser_error& err) {
		LOG_ERROR.log(err.what());
		return false;
	}

	return true;
}

DataNode XML::getNode() {
	return DataNode(&(*_ptree), "");
}

DataNode XML::getNode(const Char* tagName) {
	return DataNode(&_ptree->get_child(tagName), tagName);
}

DataNode XML::createNode(const Char* tagName) {
	return DataNode(&_ptree->add_child(tagName, node_type("")), tagName);
}

}