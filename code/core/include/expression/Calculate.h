#ifndef GEMINI_Calculate_INCLUDE
#define GEMINI_Calculate_INCLUDE
#include "Expression.h"

#include "../../public/DateTime.h"
#include "./function/FunctionMgr.h"

namespace gemini {

class Calculate {
 public:
  virtual ~Calculate() {}
  virtual Any getValue(const EntityObject::SPtr& entity) = 0;
  virtual Boolean parse(const Char*& str) = 0;
};

class LongCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  Long _value;
  friend class Expression;
};

class DoubleCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  Double _value;
  friend class Expression;
};

class TextCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  String _value;
};

class DateTimeCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  DateTime _value;
};

class DurationCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  Duration _value;
};

class EnumCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  Int _value;
};

class OperTypeCalculate : public Calculate {
 public:
  OperTypeCalculate(const String& name);

  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Any getValue(const Any& param1, const Any& param2,
                       const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  const Method* _method;
};

class FieldCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  Any getResult(const EntityObject* entity);

 private:
  Boolean _isList;
  const Class* _propertyCls;
  const Field* _field;
  std::vector<const Field*> _paths;
};

class FunctionCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 private:
  const Method* _method;
  std::vector<Expression> _params;
};

class BracketCalculate : public Calculate {
 public:
  virtual Any getValue(const EntityObject::SPtr& entity);
  virtual Boolean parse(const Char*& str);

 public:
  Expression _exp;
};

}  // namespace gemini
#endif  // !GEMINI_Calculate_INCLUDE