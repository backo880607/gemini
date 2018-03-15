#include "../include/DumpFile.h"
#include "../include/Application.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#pragma comment(lib, "common.lib")
#pragma comment(lib, "exception_handler.lib")
#pragma comment(lib, "crash_generation_client.lib")
#include <client/windows/handler/exception_handler.h>
//#include "client/windows/crash_generation/crash_generation_server.h"
#include "client/windows/crash_generation/client_info.h"
#elif GEMINI_OS == GEMINI_OS_LINUX_
#include <client/linux/handler/exception_handler.h>
#endif

using namespace google_breakpad;

#include <boost/locale.hpp>

namespace gemini {

DumpFile::DumpFile(void)
	: m_pCrashHandler(nullptr)
{
}

const char kSuccessIndicator[] = "success";
const char kFailureIndicator[] = "failure";
static CrashGenerationServer* crash_server = nullptr;
const wchar_t kPipeName[] = L"\\\\.\\pipe\\BreakpadCrashServices\\TestServer";
static void ShowClientConnected(void* context,
	const ClientInfo* client_info) {
	TCHAR* line = new TCHAR[256];
	line[0] = L'\0';
	int result = swprintf_s(line,
		256,
		L"Client connected:\t\t%d\r\n",
		client_info->pid());

	if (result == -1) {
		delete[] line;
		return;
	}
}
static void ShowClientCrashed(void* context,
	const ClientInfo* client_info,
	const wstring* dump_path) {
}
static void ShowClientExited(void* context,
	const ClientInfo* client_info) {
}
/*void CrashServerStart() {
	// Do not create another instance of the server.
	if (crash_server) {
		return;
	}

	std::wstring dump_path = L"C:\\Dumps\\";

	if (_wmkdir(dump_path.c_str()) && (errno != EEXIST)) {
		MessageBoxW(NULL, L"Unable to create dump directory", L"Dumper", MB_OK);
		return;
	}

	crash_server = new CrashGenerationServer(kPipeName,
		NULL,
		ShowClientConnected,
		NULL,
		ShowClientCrashed,
		NULL,
		ShowClientExited,
		NULL,
		NULL,
		NULL,
		true,
		&dump_path);

	if (!crash_server->Start()) {
		MessageBoxW(NULL, L"Unable to start server", L"Dumper", MB_OK);
		delete crash_server;
		crash_server = NULL;
	}
}*/

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
bool onMinidumpDumped(const wchar_t* dump_path,
	const wchar_t* minidump_id,
	void* context,
	EXCEPTION_POINTERS* exinfo,
	MDRawAssertionInfo* assertion,
	bool succeeded)
{
	return succeeded;
}
#elif GEMINI_OS == GEMINI_OS_LINUX_
bool onMinidumpDumped(const google_breakpad::MinidumpDescriptor& descriptor,
	void* context,
	bool succeeded)
{
	return succeeded;
}
#endif

const std::wstring& GetDumpPath()
{
	static std::wstring path;
	if (path.empty())
	{
		path = boost::locale::conv::to_utf<WChar>(g_app.getDumpPath(), "UTF-8");
		path += L"Bug.dmp";
	}

	return path;
}

void DumpFile::Init()
{
	if (m_pCrashHandler)
		return;

	//CrashServerStart();
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
	// This is needed for CRT to not show dialog for invalid param
	// failures and instead let the code handle it.
	_CrtSetReportMode(_CRT_ASSERT, 0);
	m_pCrashHandler = new google_breakpad::ExceptionHandler(GetDumpPath().c_str(),
		nullptr,
		onMinidumpDumped,
		nullptr,
		google_breakpad::ExceptionHandler::HANDLER_ALL,
		MINIDUMP_TYPE::MiniDumpNormal,
		(HANDLE)nullptr,
		nullptr);
#elif GEMINI_OS == GEMINI_OS_LINUX_
	google_breakpad::MinidumpDescriptor descriptor(".");
	m_pCrashHandler = new google_breakpad::ExceptionHandler(descriptor,
		NULL,
		onMinidumpDumped,
		NULL,
		true,
		-1);
#endif
}


DumpFile::~DumpFile(void)
{
	if (m_pCrashHandler)
	{
		delete m_pCrashHandler;
	}
}

}