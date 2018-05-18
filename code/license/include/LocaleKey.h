#pragma once
#include <string>
#include <memory>

namespace APSUTIL {

class LocaleKey
{
public:
	LocaleKey();
	~LocaleKey();

	bool Valid() const { return _valid; }

	const std::string& GetUpdateTime() const { return _updateTime; }
	const std::string& GetDiskSerialNo() const { return _diskSerialNo; }
	const std::string& GetMacAddr() const { return _macAddr; }
	const std::string& GetOSName() const { return _osName; }
	const std::string& GetRandomCode() const { return _randomCode; }
	const std::string& GetCreateTime() const { return _createTime; }

	const std::string& GetCompanyName() const { return _companyName; }
	const std::string& GetAddress() const { return _address; }
	const std::string& GetCorporate() const { return _corporate; }
	const std::string& GetContacts() const { return _contacts; }
	
	const std::string& GetDeadTime() const { return _deadtime; }
	int GetMaxUsers() const { return _maxUsers; }
	int GetMaxConcurrency() const { return _maxConcurrency; }
	bool GetRenew() const { return _renew; }

	static std::string KeyPath();
	static std::shared_ptr<LocaleKey> Get();
	static std::string decryptData(const std::string& data);
	static void CCCCCheck(const std::string& data);
	static bool IsExist();
	static std::shared_ptr<LocaleKey> create();
	static std::shared_ptr<LocaleKey> create(const std::string& additional);

	static std::shared_ptr<LocaleKey> GetSystemKey();

	static void UpdateKey(const std::shared_ptr<LocaleKey>& key);

private:
	friend class AuthorizeCheck;
	bool _valid;
	std::string _updateTime;
	std::string _diskSerialNo;
	std::string _macAddr;
	std::string _osName;
	std::string _randomCode;

	std::string _companyName;
	std::string _address;
	std::string _corporate;
	std::string _contacts;

	std::string _deadtime;
	int _maxUsers;
	int _maxConcurrency;
	bool _renew;
	std::string _createTime;
};

}