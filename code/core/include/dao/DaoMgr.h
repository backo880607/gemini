#ifndef GEMINI_DaoMgr_INCLUDE
#define GEMINI_DaoMgr_INCLUDE
#include "BaseDao.h"

namespace gemini {

class DaoMgr final : public noncopyable {
 public:
  typedef std::shared_ptr<BaseDao> dao_type;
  DaoMgr();
  ~DaoMgr();

  static DaoMgr &instance() {
    static DaoMgr mgr;
    return mgr;
  }

  void init();

  dao_type getDao(const Class &cls);

 private:
  std::vector<dao_type> &getDaoes() { return _daoes; }

 private:
  friend class Memory;
  std::vector<dao_type> _daoes;
};

}  // namespace gemini
#endif  // !GEMINI_DaoMgr_INCLUDE