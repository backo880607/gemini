#pragma once
#include <string>
#include <memory>

namespace APSUTIL {

class Authorize
{
public:
	struct TagQueryResult {
		int valid;
		std::wstring deadtime;
		int maxUsers;
		int maxConcurrency;
		std::wstring head;
		std::wstring msg;
	};
	struct TagImportResult {
		std::wstring msg;
	};
	struct TagCheckResult {
		std::wstring msg;
	};
public:
	Authorize();
	~Authorize();

	bool Valid() const { return _valid; }

	static std::string AuthPath();
	// 用户保存创建授权信息的临时文件
	static std::string AuthCreatePath();
	static std::shared_ptr<Authorize> Get();

	static void ImportAuth(const char * data, std::size_t len);

	static void CreateAuth(const std::string& data);
	static void UpdateAuth(std::shared_ptr<Authorize> auth, bool bCreate = false);


	int GetMaxUsers() const { return _maxUsers; }
	int GetMaxConcurrency() const { return _maxConcurrency; }
	const std::string GetDeadTime() const { return _deadtime; }

	static std::wstring ToJson(const TagQueryResult& res);
	static std::wstring ToJson(const TagImportResult& res);

protected:
	static std::shared_ptr<Authorize> GetImpl(const char* data, std::size_t len);

private:
	friend class AuthorizeCheck;
	bool _valid;
	bool _isRenew;
	int _maxUsers;
	int _maxConcurrency;
	std::string _randomCode;
	std::string _keyRandomCode;
	std::string _deadtime;
	std::string _firstUseTime;
	std::string _onlyAuthCode;
	std::string _keyFileImportTime;
};

}