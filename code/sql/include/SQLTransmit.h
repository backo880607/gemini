#ifndef GEMINI_SQL_SQLTransmit_INCLUDE
#define GEMINI_SQL_SQLTransmit_INCLUDE
#include <boost/thread.hpp>
#include <mutex>
#include <queue>
#include "../public/Connection.h"
#include "../public/Statement.h"

namespace gemini {
namespace sql {

class SQLTransmit final {
 public:
  struct data_type {
    Connection conn;
    std::vector<Statement> stmts;
  };

  SQLTransmit();
  ~SQLTransmit();

  static SQLTransmit& instance() {
    static SQLTransmit mgr;
    return mgr;
  }

  void start();
  void stop();
  void wait();

  void push(const data_type& data);

 private:
  data_type& get();
  void pop();
  static void run(SQLTransmit* transmit);

 private:
  static data_type s_emptyData;
  std::queue<data_type> _datas;
  std::mutex _mutex;
  std::shared_ptr<boost::thread> _threadQueue;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLTransmit_INCLUDE