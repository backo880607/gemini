#pragma once
#include <string>

struct IWbemLocator;
struct IWbemServices;
class System
{
public:
	System();
	~System();

	bool hasError() const { return m_bError; }

	const std::string& getError() const { return m_error; }

	// 获取操作系统序列号
	std::string GetSerialNumber();

	std::string GetCPUID();

	std::string GetMainHardDiskId();

	std::string GetMainBoardId();

	// 获取mac地址
	std::string GetNetworkAdapterId();

	std::string GetGroupName();
private:
	void connect();

private:
	bool m_bError;
	std::string m_error;
	IWbemLocator* m_pLoc;
	IWbemServices* m_pSvc;
};