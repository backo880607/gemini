#ifndef GEMINI_RefSet_INCLUDE
#define GEMINI_RefSet_INCLUDE
#include "RefBase.h"

namespace gemini {

class RefSet : public RefBase, std::set<BaseEntity::WPtr> {
  typedef std::set<BaseEntity::WPtr> base_type;

 public:
  virtual BaseEntity::SPtr get() const;
  virtual void add(BaseEntity::SPtr entity);
  virtual void remove(BaseEntity::SPtr entity);
  virtual void remove();

  virtual Boolean empty() const { return base_type::empty(); }
  virtual Long size() const { return base_type::size(); }
  virtual Iterator iterator() const;
};

}  // namespace gemini
#endif  // GEMINI_RefSet_INCLUDE