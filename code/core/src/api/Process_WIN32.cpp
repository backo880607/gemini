#include "api/Errors.h"
#include "api/Process_WIN32.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
namespace gemini {
namespace api {

ProcessImpl::ProcessImpl(HANDLE hProcess, Long pid)
    : _hProcess(hProcess), _pid(pid) {}

ProcessImpl::~ProcessImpl() { killImpl(); }

Long ProcessImpl::id() const { return _pid; }

HANDLE ProcessImpl::process() const { return _hProcess; }

Boolean ProcessImpl::running() const {
  HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, (DWORD)_pid);
  bool result = true;
  DWORD exitCode;
  BOOL rc = GetExitCodeProcess(hProc, &exitCode);
  if (!rc || exitCode != STILL_ACTIVE) result = false;
  return result;
}

int ProcessImpl::wait() const {
  DWORD rc = WaitForSingleObject(_hProcess, INFINITE);
  if (rc != WAIT_OBJECT_0) {
    Message::error<ProcessWaitError>();
    return -1;
  }

  DWORD exitCode;
  if (GetExitCodeProcess(_hProcess, &exitCode) == 0) {
    return 0;
  }

  return exitCode;
}

void ProcessImpl::killImpl() {
  if (_hProcess) {
    if (TerminateProcess(_hProcess, 0) == 0) {
      CloseHandle(_hProcess);
      _hProcess = NULL;
      _pid = 0;
      Message::error<ProcessKillError>();
    }
    CloseHandle(_hProcess);
    _hProcess = NULL;
    _pid = 0;
  }
}

Long ProcessImpl::currentId() { return GetCurrentProcessId(); }

std::shared_ptr<ProcessImpl> ProcessImpl::launch(const String& command,
                                                 const Args& args) {
  String commandLine = command;
  for (Args::const_iterator it = args.begin(); it != args.end(); ++it) {
    commandLine.append(u8" ");
    commandLine.append(*it);
  }

  STARTUPINFOA startupInfo;
  GetStartupInfoA(&startupInfo);  // take defaults from current process
  startupInfo.cb = sizeof(STARTUPINFOA);
  startupInfo.lpReserved = NULL;
  startupInfo.lpDesktop = NULL;
  startupInfo.lpTitle = NULL;
  startupInfo.dwFlags = STARTF_FORCEOFFFEEDBACK;
  startupInfo.cbReserved2 = 0;
  startupInfo.lpReserved2 = NULL;

  HANDLE hProc = GetCurrentProcess();
  Boolean mustInheritHandles = false;
  if (GetStdHandle(STD_INPUT_HANDLE)) {
    DuplicateHandle(hProc, GetStdHandle(STD_INPUT_HANDLE), hProc,
                    &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
    mustInheritHandles = true;
  } else {
    startupInfo.hStdInput = 0;
  }

  if (GetStdHandle(STD_OUTPUT_HANDLE)) {
    DuplicateHandle(hProc, GetStdHandle(STD_OUTPUT_HANDLE), hProc,
                    &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
    mustInheritHandles = true;
  } else {
    startupInfo.hStdOutput = 0;
  }

  if (GetStdHandle(STD_ERROR_HANDLE)) {
    DuplicateHandle(hProc, GetStdHandle(STD_ERROR_HANDLE), hProc,
                    &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
    mustInheritHandles = true;
  } else {
    startupInfo.hStdError = 0;
  }

  if (mustInheritHandles) {
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;
  }

  PROCESS_INFORMATION processInfo;
  DWORD creationFlags = GetConsoleWindow() ? 0 : CREATE_NO_WINDOW;
  BOOL rc = CreateProcessA(NULL, const_cast<Char*>(commandLine.c_str()),
                           NULL,  // processAttributes
                           NULL,  // threadAttributes
                           mustInheritHandles, creationFlags, NULL, NULL,
                           &startupInfo, &processInfo);
  if (startupInfo.hStdInput) CloseHandle(startupInfo.hStdInput);
  if (startupInfo.hStdOutput) CloseHandle(startupInfo.hStdOutput);
  if (startupInfo.hStdError) CloseHandle(startupInfo.hStdError);
  if (rc) {
    CloseHandle(processInfo.hThread);
    return std::shared_ptr<ProcessImpl>(
        new ProcessImpl(processInfo.hProcess, processInfo.dwProcessId));
  } else {
    Message::error<ProcessLaunchError>();
  }

  return nullptr;
}

}
}  // namespace gemini
#endif