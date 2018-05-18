#include "Authorize.h"
#include "../common/File.h"
#include "../common/System.h"
#include "../common/StringUtil.h"
#include "../common/Json.h"
#include "LocaleKey.h"
#include "AuthorizeManager.h"

#if APS_OS == APS_OS_WINDOWS_NT
#include "../WinService/cryptopp/aes.h"
#include "../WinService/cryptopp/filters.h"
#include "../WinService/cryptopp/modes.h"
#else
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/modes.h"
#endif

#include "LicenseException.h"

//#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

uint8_t s_key_1[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
uint8_t s_iv_1[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
const unsigned int AES_BLOCK_LEN = 16;
namespace APSUTIL {

Authorize::Authorize()
	: _valid(false)
	, _isRenew(false)
	, _maxUsers(0)
	, _maxConcurrency(0)
{
}

Authorize::~Authorize()
{
}

std::string Authorize::AuthPath()
{
	static std::string path;
	if (path.empty()) {
		path = FilePath::GetCurrentPath().Append("license").Append("auth").GetPath();
	}
	
	return path;
}

std::string Authorize::AuthCreatePath()
{
	static std::string path;
	if (path.empty()) {
		path = FilePath::GetCurrentPath().Append("license").Append("tempAuth").GetPath();
	}

	return path;
}

std::shared_ptr<Authorize> Authorize::Get()
{
	FilePath filePath(AuthPath());
	if (!filePath.IsExist()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}

	int len = 0;
	char * buffer = nullptr;
	std::ifstream in(filePath.GetPath().c_str(), std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
	if (in.is_open()) {
		len = in.tellg();
		in.seekg(0, std::ios_base::beg);
		buffer = new char[len];
		in.read(buffer, len);
		in.close();
	}

	if (buffer == nullptr) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}

	return GetImpl(buffer, len);
}

std::shared_ptr<Authorize> Authorize::GetImpl(const char * data, std::size_t len)
{
	std::string decryptedText;
	CryptoPP::AES::Decryption aesDecryption(s_key_1, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, s_iv_1);
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(data), len);
	stfDecryptor.MessageEnd();

	len = decryptedText.size();
	Json json(StringUtil::UTF8ToString(decryptedText.c_str()).c_str());
	if (!json.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}

	JsonNode validNode = json.GetNode(L"valid");
	if (!validNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode isRenewNode = json.GetNode(L"isRenew");
	if (!isRenewNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode maxUsersNode = json.GetNode(L"maxUsers");
	if (!maxUsersNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode maxConcurrencyNode = json.GetNode(L"maxConcurrency");
	if (!maxConcurrencyNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode randomNode = json.GetNode(L"randomCode");
	if (!randomNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode keyRandomCodeNode = json.GetNode(L"keyRandomCode");
	if (!keyRandomCodeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode deadtimeNode = json.GetNode(L"deadtime");
	if (!deadtimeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode firstUseTimeNode = json.GetNode(L"firstUseTime");
	if (!firstUseTimeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode keyFileImportTimeNode = json.GetNode(L"keyFileImportTime");
	if (!keyFileImportTimeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}
	JsonNode onlyAuthCodeNode = json.GetNode(L"onlyAuthCode");
	if (!onlyAuthCodeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}

	std::shared_ptr<Authorize> auth(new Authorize());
	auth->_valid = validNode.GetValue<bool>();
	auth->_isRenew = isRenewNode.GetValue<bool>();
	auth->_maxUsers = maxUsersNode.GetValue<int>();
	auth->_maxConcurrency = maxConcurrencyNode.GetValue<int>();
	auth->_randomCode = StringUtil::StringToUTF8(randomNode.GetValue().c_str());
	auth->_keyRandomCode = StringUtil::StringToUTF8(keyRandomCodeNode.GetValue().c_str());
	auth->_deadtime = StringUtil::StringToUTF8(deadtimeNode.GetValue().c_str());
	auth->_firstUseTime = StringUtil::StringToUTF8(firstUseTimeNode.GetValue().c_str());
	auth->_keyFileImportTime = StringUtil::StringToUTF8(keyFileImportTimeNode.GetValue().c_str());
	auth->_onlyAuthCode = StringUtil::StringToUTF8(onlyAuthCodeNode.GetValue().c_str());

	return auth;
}

void Authorize::ImportAuth(const char * data, std::size_t len)
{
	if (data == nullptr || len <= 0) {
		ExceptionThrow(LicenseException, LicenseException::E_Authorize(L""));
	}
	std::shared_ptr<LocaleKey> localeKey = LocaleKey::Get();
	if (!localeKey || !localeKey->Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_ModifySystemTime(L"本地key文件不存在或无效。"));
	}

	std::shared_ptr<LocaleKey> curKey = LocaleKey::GetSystemKey();
	if (localeKey->GetDiskSerialNo() != curKey->GetDiskSerialNo() ||
		localeKey->GetMacAddr() != curKey->GetMacAddr()) {
		// 更改了硬件信息
		ExceptionThrow(LicenseException, LicenseException::E_ModifyHardInfo(L"请勿修改硬件信息。"));
	}

	boost::gregorian::date curDay = boost::gregorian::day_clock::local_day();
	if (boost::gregorian::from_simple_string(localeKey->GetUpdateTime()) > curDay) {
		ExceptionThrow(LicenseException, LicenseException::E_ModifySystemTime(L"请勿修改系统时间。"));
	}

	std::shared_ptr<Authorize> auth = GetImpl(data, len);
	if (auth->_keyRandomCode != localeKey->GetRandomCode()) {
		ExceptionThrow(LicenseException, LicenseException::E_RandomCode(L"本地Key文件和授权信息不匹配。"));
	}
	
	// 判断授权信息的截止日期。
	if (boost::gregorian::from_simple_string(auth->_deadtime) < curDay) {
		ExceptionThrow(LicenseException, LicenseException::E_Authorize(L"授权信息已过期。"));
	}

	auth->_firstUseTime = boost::gregorian::to_simple_string(curDay);
	auth->_onlyAuthCode = StringUtil::uuid();
	auth->_keyFileImportTime = auth->_firstUseTime;
	UpdateAuth(auth);

	AuthorizeManager::instance()._valid = true;
}

void Authorize::CreateAuth(const std::string& data)
{
	Json json(StringUtil::UTF8ToString(data.c_str()).c_str());
	JsonNode keyRandomCodeNode = json.GetNode(L"randomCode");
	if (!keyRandomCodeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息缺少keyRandomCode"));
	}
	JsonNode isRenewNode = json.GetNode(L"isRenew");
	if (!isRenewNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息缺少isRenew"));
	}
	JsonNode maxUsersNode = json.GetNode(L"maxUsers");
	if (!maxUsersNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息缺少maxUsers"));
	}
	JsonNode maxConcurrencyNode = json.GetNode(L"maxConcurrency");
	if (!maxConcurrencyNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息缺少maxConcurrency"));
	}
	JsonNode deadtimeNode = json.GetNode(L"deadtime");
	if (!deadtimeNode.Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息缺少deadtime"));
	}

	std::shared_ptr<Authorize> auth(new Authorize());
	auth->_valid = true;
	auth->_keyRandomCode = StringUtil::StringToUTF8(keyRandomCodeNode.GetValue().c_str());
	auth->_randomCode = StringUtil::uuid();
	auth->_deadtime = StringUtil::StringToUTF8(deadtimeNode.GetValue().c_str());
	auth->_maxUsers = maxUsersNode.GetValue<int>();
	auth->_maxConcurrency = maxConcurrencyNode.GetValue<int>();
	auth->_isRenew = isRenewNode.GetValue<bool>();
	UpdateAuth(auth, true);
}

void Authorize::UpdateAuth(std::shared_ptr<Authorize> auth, bool bCreate /* = false */)
{
	Json json;
	json.CreateNode(L"valid").SetValue(auth->_valid);
	json.CreateNode(L"keyRandomCode").SetValue(StringUtil::UTF8ToString(auth->_keyRandomCode.c_str()));
	json.CreateNode(L"randomCode").SetValue(StringUtil::UTF8ToString(auth->_randomCode.c_str()));
	json.CreateNode(L"deadtime").SetValue(StringUtil::UTF8ToString(auth->_deadtime.c_str()));
	json.CreateNode(L"maxUsers").SetValue(auth->_maxUsers);
	json.CreateNode(L"maxConcurrency").SetValue(auth->_maxConcurrency);
	json.CreateNode(L"isRenew").SetValue(auth->_isRenew);
	json.CreateNode(L"firstUseTime").SetValue(StringUtil::UTF8ToString(auth->_firstUseTime.c_str()));
	json.CreateNode(L"keyFileImportTime").SetValue(StringUtil::UTF8ToString(auth->_keyFileImportTime.c_str()));
	json.CreateNode(L"onlyAuthCode").SetValue(StringUtil::UTF8ToString(auth->_onlyAuthCode.c_str()));
	std::wostringstream ss;
	json.Write(ss);

	std::string context = StringUtil::StringToUTF8(ss.str().c_str());
	int len = context.size();

	// 加密
	std::string cipherText;
	CryptoPP::AES::Encryption aesEncryption(s_key_1, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, s_iv_1);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(context.c_str()), len);
	stfEncryptor.MessageEnd();
	len = cipherText.size();

	FilePath filePath(bCreate ? AuthCreatePath() : AuthPath());
	std::ofstream of(filePath.GetPath().c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc/* | std::ios_base::_Nocreate */);
	if (of.is_open()) {
		of.write(cipherText.c_str(), len);
		of.close();
	}
}

std::wstring Authorize::ToJson(const TagQueryResult& res)
{
	Json json;
	json.CreateNode(L"valid").SetValue(res.valid);
	json.CreateNode(L"deadtime").SetValue(res.deadtime);
	json.CreateNode(L"maxUsers").SetValue(res.maxUsers);
	json.CreateNode(L"head").SetValue(res.head);
	json.CreateNode(L"maxConcurrency").SetValue(res.maxConcurrency);
	json.CreateNode(L"msg").SetValue(res.msg);

	std::wostringstream ss;
	//std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
	//ss.imbue(utf8Locale);
	json.Write(ss);
	return ss.str();
}

std::wstring Authorize::ToJson(const TagImportResult & res)
{
	Json json;
	json.CreateNode(L"msg").SetValue(res.msg);

	std::wostringstream ss;
	//std::locale utf8Locale(std::locale(), new boost::program_options::detail::utf8_codecvt_facet());
	//ss.imbue(utf8Locale);
	json.Write(ss);
	return ss.str();
}

}
