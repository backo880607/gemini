#ifndef GEMINI_Calculate_INCLUDE
#define GEMINI_Calculate_INCLUDE
#include "../../public/DateTime.h"
#include "Expression.h"
#include "Object.h"

namespace gemini {

class Calculate {
 public:
  virtual ~Calculate() {}
  virtual Any getValue(const BaseEntity::SPtr& entity) = 0;
  virtual Boolean parse(const Char*& str) = 0;
  virtual const Class* getClass() = 0;
};

class LongCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &Class::forType<Long>(); }

 private:
  Long _value;
  friend class Expression;
};

class DoubleCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &Class::forType<Double>(); }

 private:
  Double _value;
  friend class Expression;
};

class TextCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &Class::forType<String>(); }

 private:
  String _value;
};

class DateTimeCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &Class::forType<DateTime>(); }

 private:
  DateTime _value;
};

class DurationCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &Class::forType<Duration>(); }

 private:
  Duration _value;
};

class EnumCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &Class::forType<Short>(); }

 private:
  Short _value;
};

class OperTypeCalculate : public Calculate {
 public:
  OperTypeCalculate(const String& name);

  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Any getValue(const Any& param1, const Any& param2,
                       const BaseEntity::SPtr& entity);
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return &_method->getReturnClass(); }

 private:
  const Method* _method;
};

class FieldCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual Boolean parse(const Char*& str, const Class* propertyCls);
  virtual const Class* getClass() override { return &_field->getType(); }

 private:
  Any getResult(const BaseEntity* entity);

 private:
  const Field* _field;
  std::vector<const Field*> _paths;
};

class FunctionCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override;

 private:
  const Method* _method;
  std::vector<Expression> _params;
  FieldCalculate* _fieldCalc;
};

class BracketCalculate : public Calculate {
 public:
  virtual Any getValue(const BaseEntity::SPtr& entity) override;
  virtual Boolean parse(const Char*& str) override;
  virtual const Class* getClass() override { return _exp.getClass(); }

 public:
  Expression _exp;
};

}  // namespace gemini
#endif  // !GEMINI_Calculate_INCLUDE