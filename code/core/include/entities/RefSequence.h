#ifndef GEMINI_RefList_INCLUDE
#define GEMINI_RefList_INCLUDE
#include "RefBase.h"

namespace gemini {

class RefSequence : public RefBase, std::list<BaseEntity::WPtr> {
  typedef std::list<BaseEntity::WPtr> base_type;

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
#endif  // GEMINI_RefList_INCLUDE