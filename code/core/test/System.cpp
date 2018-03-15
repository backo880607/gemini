#include "System.h"

#define _WIN32_DCOM
#include <comdef.h>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

System::System()
	: m_bError(false)
{
	HRESULT hr;
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Failed to initialize COM library. Error code = %X", hr);
		m_error = buffer;
	} else {
		hr = CoInitializeSecurity(
			NULL,                        // Security descriptor    
			-1,                          // COM negotiates authentication service
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication level for proxies
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities of the client or server
			NULL);                       // Reserved

		if (FAILED(hr))
		{
			m_bError = true;
			char buffer[1024];
			sprintf_s(buffer, "Failed to initialize security. Error code = %X", hr);
			m_error = buffer;
			CoUninitialize();
		}
	}

	connect();
}

System::~System()
{
	if (m_pSvc != nullptr) {
		m_pSvc->Release();
		m_pLoc->Release();
		CoUninitialize();
	}
}

std::string System::GetSerialNumber()
{
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hr = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_OperatingSystem"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Query for Operation System SerialNumber failed. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pSvc = nullptr;
		m_pLoc->Release();
		m_pLoc = nullptr;
		CoUninitialize();
		return "";
	}
	else {
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			// Get the value of the Name property
			hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
			//wcout << "Process Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
			pclsObj = NULL;
		}
	}
	return std::string();
}

std::string System::GetCPUID()
{
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hr = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Processor"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Query for Processor SerialNumber failed. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pSvc = nullptr;
		m_pLoc->Release();
		m_pLoc = nullptr;
		CoUninitialize();
		return "";
	}
	else {
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			// Get the value of the Name property
			hr = pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);
			//wcout << "Process Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
			pclsObj = NULL;
		}
	}
	return std::string();
}

std::string System::GetMainHardDiskId()
{
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hr = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_PhysicalMedia"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Query for PhysicalMedia SerialNumber failed. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pSvc = nullptr;
		m_pLoc->Release();
		m_pLoc = nullptr;
		CoUninitialize();
		return "";
	}
	else {
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			// Get the value of the Name property
			hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
			//wcout << "Process Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
			pclsObj = NULL;
		}
	}

	return std::string();
}

std::string System::GetMainBoardId()
{
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hr = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_BaseBoard"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Query for BaseBoard Id failed. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pSvc = nullptr;
		m_pLoc->Release();
		m_pLoc = nullptr;
		CoUninitialize();
		return "";
	}
	else {
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			// Get the value of the Name property
			hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
			//wcout << "Process Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
			pclsObj = NULL;
		}
	}

	return std::string();
}

std::string System::GetNetworkAdapterId()
{
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hr = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT MACAddress FROM Win32_NetworkAdapter WHERE ((MACAddress Is Not NULL)AND (Manufacturer <> 'Microsoft'))"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Query for BaseBoard Id failed. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pSvc = nullptr;
		m_pLoc->Release();
		m_pLoc = nullptr;
		CoUninitialize();
		return "";
	}
	else {
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			// Get the value of the Name property
			hr = pclsObj->Get(L"MACAddress", 0, &vtProp, 0, 0);
			//wcout << "Process Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
			pclsObj = NULL;
		}
	}
	return std::string();
}

std::string System::GetGroupName()
{
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hr = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Group"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Query for Group Name failed. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pSvc = nullptr;
		m_pLoc->Release();
		m_pLoc = nullptr;
		CoUninitialize();
		return "";
	}
	else {
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			// Get the value of the Name property
			hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
			//wcout << "Process Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
			pclsObj = NULL;
		}
	}
	return std::string();
}

void System::connect()
{
	m_pLoc = 0;

	HRESULT hr = CoCreateInstance(CLSID_WbemLocator, 0,
		CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&m_pLoc);

	if (FAILED(hr))
	{
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Failed to create IWbemLocator object. Err code = %X", hr);
		m_error = buffer;
		CoUninitialize();
		return;
	}
	m_pSvc = 0;

	// Connect to the root\default namespace with the current user.
	hr = m_pLoc->ConnectServer(
		BSTR(L"ROOT\\CIMV2"),  //namespace
		NULL,       // User name 
		NULL,       // User password
		0,         // Locale 
		NULL,     // Security flags
		0,         // Authority 
		0,        // Context object 
		&m_pSvc);   // IWbemServices proxy


	if (FAILED(hr))
	{
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Could not connect. Error code = %X", hr);
		m_error = buffer;
		m_pLoc->Release();
		CoUninitialize();
		return;
	}

	// Set the proxy so that impersonation of the client occurs.
	hr = CoSetProxyBlanket(m_pSvc,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE
	);

	if (FAILED(hr))
	{
		m_bError = true;
		char buffer[1024];
		sprintf_s(buffer, "Could not set proxy blanket. Error code = %X", hr);
		m_error = buffer;
		m_pSvc->Release();
		m_pLoc->Release();
		CoUninitialize();
		return;
	}
}
