#ifndef GEMINI_Expression_INCLUDE
#define GEMINI_Expression_INCLUDE
#include "../../public/Any.h"
#include "../../public/Object.h"

namespace gemini {

struct Node;
class Calculate;
class Expression final
{
public:
	Expression();
	~Expression();
	Boolean parse(const Char* str);

	Boolean getBoolean();
	Boolean getBoolean(const EntityObject::SPtr& entity);

	String getText();
	String getText(const EntityObject::SPtr& entity);

	template <typename T>
	void filter(const T& entities) {
		
	}

private:
	Any getValue(const EntityObject::SPtr& entity) { return getValue(_root, entity); }
	Any getValue(Node* node, const EntityObject::SPtr& entity);
	Node* create(const Char*& str, Boolean bFun);
	Calculate* getNumberCalculate(const Char*& str);
	Calculate* getFunOrFieldCalculate(const Char*& str);
	void clear(Node* node);
private:
	Boolean _hasField;
	Node* _root;
	friend class FunctionCalculate;
	friend class FieldCalculate;
	friend class BracketCalculate;
};

}
#endif // GEMINI_Expression_INCLUDE