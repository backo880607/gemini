#include "api/Process_UNIX.h"

#if GEMINI_OS == GEMINI_OS_LINUX || GEMINI_OS == GEMINI_OS_MAC_OS_X
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "message/Exception.h"
namespace gemini {

ProcessImpl::ProcessImpl(Long pid) {}

ProcessImpl::~ProcessImpl() { killImpl(); }

Long ProcessImpl::id() const { return _pid; }

Boolean ProcessImpl::running() const { return kill(_pid, 0) == 0; }

Int ProcessImpl::wait() const {
  Int status;
  Int rc;
  do {
    rc = waitpid(_pid, &status, 0);
  } while (rc < 0 && errno == EINTR);
  THROW_IF(rc != _pid, SystemExecption, "Cannot wait for process", _pid)
  return WEXITSTATUS(status);
}

void ProcessImpl::killImpl() {
  if (kill(_pid, SIGKILL) != 0) {
    switch (errno) {
      case ESRCH:
        THROW(SystemExecption, "cannot kill process for not found")
      case EPERM:
        THROW(SystemExecption, "cannot kill process for has no permission")
      default:
        THROW(SystemExecption, "cannot kill process")
    }
  }
}

Long ProcessImpl::currentId() { return getpid(); }

std::shared_ptr<ProcessImpl> ProcessImpl::launch(const String& command,
                                                 const Args& args) {
  std::vector<Char*> argv(args.size() + 2);
  int i = 0;
  argv[i++] = const_cast<Char*>(command.c_str());
  for (Args::const_iterator it = args.begin(); it != args.end(); ++it) {
    argv[i++] = const_cast<Char*>(it->c_str());
  }
  argv[i] = nullptr;

  Int pid = fork();
  if (pid < 0) {
    THROW(SystemExecption, "Cannot fork process for ", command)
  } else if (pid == 0) {
    // close all open file descriptors other than stdin, stdout, stderr
    for (int i = 3; i < sysconf(_SC_OPEN_MAX); ++i) {
      close(i);
    }

    execvp(argv[0], &argv[0]);
    _exit(72);
  }
  return std::shared_ptr<ProcessImpl>(new ProcessImpl(pid));
}

}  // namespace gemini

#endif