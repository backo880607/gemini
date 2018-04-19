#include "api/DataNode.h"

#include <boost/property_tree/ptree.hpp>

namespace gemini {

String DataNode::getValue() const
{
	return _pNode->get_value<String>();
}

void DataNode::setValue(const Char* val)
{
	_pNode->put_value(val);
}

DataNode DataNode::getNode(const Char* tagName, Boolean bCreate /* = false */)
{
	auto rt = _pNode->get_child_optional(tagName);
	if (rt)
		return &(*rt);

	if (bCreate)
		return &_pNode->put_child(tagName, node_type(""));

	return DataNode();
}

DataNode DataNode::createNode()
{
	return &_pNode->add_child("", node_type());
}

DataNode DataNode::createNode(const Char* tagName)
{
	return &_pNode->put_child(tagName, node_type(""));
}

void DataNode::removeNode(const Char* tagName)
{
	_pNode->erase(tagName);
}

std::vector<DataNode> DataNode::GetChilds() const
{
	std::vector<DataNode> vecNode;
	for (auto pt = _pNode->begin(); pt != _pNode->end(); ++pt)
	{
		if (pt->first == "<xmlattr>")
			continue;
		vecNode.push_back(DataNode(&pt->second, pt->first.c_str()));
	}

	return vecNode;
}

void DataNode::addNode(DataNode node)
{
	//m_pNode.put_child(m_pNode., node.m_pNode);
}

}