#ifndef GEMINI_DaoMgr_INCLUDE
#define GEMINI_DaoMgr_INCLUDE
#include "../../public/dao/BaseDao.h"

namespace gemini {

class DaoMgr final : public noncopyable {
 public:
  typedef std::shared_ptr<BaseDao> dao_type;
  typedef DaoListener *(*FunCreateListener)();
  DaoMgr();
  ~DaoMgr();

  static DaoMgr &instance() {
    static DaoMgr mgr;
    return mgr;
  }

  static void registerDao(const Class &daoClass, const Class &entityClass);
  static void registerListener(FunCreateListener creater) {
    s_listenerInfos.push_back(creater);
  }

  void init();

  dao_type getDao(const Class &cls);

  void startSync();
  void endSync();

 private:
  std::vector<dao_type> &getDaoes() { return _daoes; }

 private:
  friend class Memory;
  static std::map<const Class *, const Class *> s_daoInfos;
  std::vector<dao_type> _daoes;
  static std::vector<FunCreateListener> s_listenerInfos;
  std::vector<DaoListener *> _listeners;
};

}  // namespace gemini
#endif  // !GEMINI_DaoMgr_INCLUDE