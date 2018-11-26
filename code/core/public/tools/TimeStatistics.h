#ifndef GEMINI_TimeStatistics_INCLUDE
#define GEMINI_TimeStatistics_INCLUDE
#include "../Core.h"

namespace gemini {

class CORE_API TimeStatisticsMgr {
  typedef String (*FunTimeStatistics)();

 public:
  TimeStatisticsMgr();
  ~TimeStatisticsMgr();

  static TimeStatisticsMgr& instance() {
    static TimeStatisticsMgr mgr;
    return mgr;
  }

  void registerTmStatistics(FunTimeStatistics fun) {
    _funStatistics.push_back(fun);
  }
  void writeTmStatistics(const String& str);
  void flushTmStatistics();

 private:
  String getPath();

 private:
  std::vector<FunTimeStatistics> _funStatistics;
};

template <class TAG>
class TimeStatistics {
  struct TimeInfo {
    Int nums;
    Long dtBeg;
    Long time;
    TimeInfo() : nums(0), dtBeg(0), time(0) {}
  };

 public:
  TimeStatistics() : _tmBeg(0) { beginTime(); }
  template <typename T>
  TimeStatistics(T val) {
    _remark = StringUtil::format(val);
    _tmBeg = clock();
  }
  TimeStatistics(const Char* val) {
    _remark = val;
    _tmBeg = clock();
  }
  TimeStatistics(const String& val) {
    _remark = val;
    _tmBeg = clock();
  }
  ~TimeStatistics() {
    if (_tmBeg > 1) {
      Double tm = ((Double)(clock() - _tmBeg)) / CLOCKS_PER_SEC;
      if (!_remark.empty()) _remark += L"\t";
      _remark += StringUtil::SPrintf(L"%s\t%d\t%lf\n", name().c_str(), 1, tm);
      TimeStatisticsMgr::instance().writeTmStatistics(m_remark);
    } else {
      endTime();
    }
  }

  static void beginTime() { _values.dtBeg = clock(); }
  static void endTime(bool real = false) {
    if (!real && _values.nums == 0) {
      TimeStatisticsMgr::instance().registerTmStatistics(flushTime);
    }
    _values.nums++;
    _values.time += clock() - _values.dtBeg;

    if (real) {
      TimeStatisticsMgr::instance().::writeTmStatistics(flushTime());
      _values = TimeInfo();
    }
  }
  static String flushTime() {
    return StringUtil::SPrintf(L"%s\t%d\t%lf\n", name().c_str(), _values.nums,
                               ((Double)_values.time) / CLOCKS_PER_SEC);
  }
  static String name() { return String(typeid(TAG).name()); }

 private:
  Double _tmBeg;
  String _remark;
  static TimeInfo _values;
};
template <class TAG>
typename TimeStatistics<TAG>::TimeInfo TimeStatistics<TAG>::_values;

#define GEMINI_TIME_BEGIN(TAG) \
  struct tm_GEMINI##TAG;       \
  TimeStatistics<tm_GEMINI##TAG>::beginTime();

#define GEMINI_TIME_END(TAG) TimeStatistics<tm_GEMINI##TAG>::endTime();

#define GEMINI_TIME_END_REAL(TAG) TimeStatistics<tm_GEMINI##TAG>::endTime(true);

#define GEMINI_TIME_OBJ(TAG) \
  struct tm_GEMINI##TAG {};  \
  TimeStatistics<tm_GEMINI##TAG> tm_gemini_##TAG;

#define GEMINI_TIME_ONCE(TAG, Remark) \
  struct tm_GEMINI##TAG {};           \
  TimeStatistics<tm_GEMINI##TAG> tm_gemini_##TAG(Remark);

}  // namespace gemini
#endif  // GEMINI_TimeStatistics_INCLUDE