#include "../../include/expression/Expression.h"
#include "../../include/expression/Calculate.h"
#include "../../public/tools/StringUtil.h"
#include "../../include/expression/OperType.h"
#include "../../include/Application.h"

#include <locale>

namespace gemini {

#define ENDFLG	'\0'

struct Node {
	OperType type;
	Calculate* cal;
	Node* lchild;
	Node* rchild;

	Node(OperType t, Calculate* c = nullptr, Node *lc = nullptr, Node *rc = nullptr)
		: type(t), cal(c), lchild(lc), rchild(rc)
	{}

	template <class T>
	T* GetCalculate() { return (T*)cal; }
};

Expression::Expression()
	: _root(nullptr)
{

}

Expression::~Expression()
{
	clear(_root);
}

Boolean Expression::parse(const Char* str)
{
	if (str == nullptr) {
		return false;
	}

	_root = create(str, false);
	return _root != nullptr;
}

Boolean Expression::getBoolean()
{
	return getBoolean(nullptr);
}

Boolean Expression::getBoolean(const EntityObject::SPtr& entity)
{
	if (_root == nullptr) {
		return false;
	}
	return true;
}

String Expression::getText()
{
	return getText(nullptr);
}

String Expression::getText(const EntityObject::SPtr& entity)
{
	if (_root == nullptr) {
		return "";
	}

	return StringUtil::format(getValue(_root, entity));
}

Any Expression::getValue(Node* node, const EntityObject::SPtr& entity)
{
	if (node->type == OperType::DATA) {
		return node->cal->getValue(entity);
	}

	Any param1 = getValue(node->lchild, entity);
	Any param2 = getValue(node->rchild, entity);
	if (!param1 || !param2) {
		return nullptr;
	}

	return node->GetCalculate<OperTypeCalculate>()->getValue(param1, param2, entity);
}

OperType getCallType(const Char*& str)
{
	OperType operType = OperType::DATA;
	switch (*str) {
	case '+':
		operType = OperType::PLUS;
		break;
	case '-':
		operType = OperType::MINUS;
		break;
	case '*':
		operType = OperType::MULTIPLIED;
		break;
	case '/':
		operType = OperType::DIVIDED;
		break;
	case '&':
		if (*++str == '&') {
			operType = OperType::AND;
		}
		break;
	case '|':
		if (*++str == '|') {
			operType = OperType::OR;
		}
		break;
	case '=':
		if (*++str == '=') {
			operType = OperType::EQUAL;
		}
		break;
	case '!':
		if (*(str + 1) == '=') {
			operType = OperType::NOTEQUAL;
			++str;
		} else {
			operType = OperType::NOT;
		}
		break;
	case '>':
		if (*(str + 1) == '=') {
			operType = OperType::GREATEREQUAL;
			++str;
		} else {
			operType = OperType::GREATER;
		}
		break;
	case '<':
		if (*(str + 1) == '=') {
			operType = OperType::LESSEQUAL;
			++str;
		} else {
			operType = OperType::LESS;
		}
		break;
	}

	if (operType != OperType::DATA) {
		++str;
	}
	return operType;
}

Node* Expression::create(const Char*& str, Boolean bFun)
{
	Boolean bError = false;
	Node* root = nullptr;
	while (*str != ENDFLG) {
		const char curChar = *str;
		if (std::isspace(curChar, g_app.getLocale())) {
			++str;
			continue;
		}

		if (curChar == '#') {
			Calculate* cal = new DateTimeCalculate();
			if (!cal->parse(str)) {
				bError = true;
				delete cal;
				break;
			}

			if (root == nullptr)
				root = new Node(OperType::DATA, cal);
			else if (root->rchild == nullptr)
				root->rchild = new Node(OperType::DATA, cal);
			else
				root->rchild->rchild = new Node(OperType::DATA, cal);
		} else if (curChar == '\'') {
			Calculate* cal = new TextCalculate();
			if (!cal->parse(str)) {
				bError = true;
				delete cal;
				break;
			}

			if (root == nullptr)
				root = new Node(OperType::DATA, cal);
			else if (root->rchild == nullptr)
				root->rchild = new Node(OperType::DATA, cal);
			else
				root->rchild->rchild = new Node(OperType::DATA, cal);
		} else if (curChar == '(') {
			Node* nd = create(++str, false);
			if (nd == nullptr) {
				bError = true;
				break;
			}

			if (root == nullptr)
				root = nd;
			else if (root->rchild == nullptr)
				root->rchild = nd;
			else
				root->rchild->rchild = nd;
		} else if (curChar == ')') {
			break;
		} else if (curChar == ',') {
			if (!bFun)
				bError = true;
			++str;
			break;
		}
		else if (std::isdigit(curChar, g_app.getLocale())) {
			Calculate* cal = getNumberCalculate(str);
			if (cal == nullptr) {
				bError = false;
				break;
			}

			if (root == nullptr)
				root = new Node(OperType::DATA, cal);
			else if (root->rchild == nullptr)
				root->rchild = new Node(OperType::DATA, cal);
			else
				root->rchild->rchild = new Node(OperType::DATA, cal);
		} else {
			const Char* temp = str;
			OperType calType = getCallType(str);
			if (calType != OperType::DATA) {
				Calculate* cal = new OperTypeCalculate(String(temp, str - temp));
				if (root == nullptr)
					root = new Node(calType, cal);
				else if (calType < root->type)	// 优先级更高
					root->rchild = new Node(calType, cal, root->rchild);
				else // 作为优先级更小的左子树
					root = new Node(calType, cal, root);
			} else {
				// 自定义函数调用
				Calculate* cal = getFunOrFieldCalculate(str);
				if (cal == nullptr) {
					bError = true;
					break;
				}

				if (root == nullptr)
					root = new Node(OperType::DATA, cal);
				else if (root->rchild == nullptr)
					root->rchild = new Node(OperType::DATA, cal);
				else
					root->rchild->rchild = new Node(OperType::DATA, cal);
			}
		}
	}

	if (bError) {
		root = nullptr;
	}

	return root;
}

Calculate* Expression::getNumberCalculate(const Char*& str)
{
	const Char* temp = str;
	do {
		++str;
	} while (*str != ENDFLG && std::isdigit(*str, g_app.getLocale()));

	if (*str != ENDFLG && *str == '.') {
		if (!std::isdigit(*++str, g_app.getLocale())) {
			return nullptr;
		}

		do {
			++str;
		} while (*str != ENDFLG && std::isdigit(*str, g_app.getLocale()));
		DoubleCalculate* cal = new DoubleCalculate();
		cal->_value = StringUtil::convert<Double>(String(temp, str - temp).c_str());
		return cal;
	}

	IntCalculate* cal = new IntCalculate();
	cal->_value = StringUtil::convert<Long>(String(temp, str - temp).c_str());
	return cal;
}

Calculate* Expression::getFunOrFieldCalculate(const Char*& str)
{
	const Char* temp = str;
	while (*temp != ENDFLG) {
		if (*temp == '.') {
			Calculate* cal = new FieldCalculate();
			if (!cal->parse(str)) {
				delete cal;
				break;
			}
			return cal;
		}
		else if (*temp == '(') {
			Calculate* cal = cal = new FunctionCalculate();
			if (!cal->parse(str)) {
				delete cal;
				break;
			}
			return cal;
		}
		++temp;
	}

	return nullptr;
}

void Expression::clear(Node* node)
{

}

}