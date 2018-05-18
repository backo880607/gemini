#include "LocaleKey.h"
#include "../common/File.h"
#include "../common/System.h"
#include "../common/StringUtil.h"
#include "../common/Json.h"

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
#include <boost/date_time/gregorian/gregorian.hpp>

uint8_t s_key_2[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
uint8_t s_iv_2[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
const unsigned int AES_BLOCK_LEN = 16;
namespace APSUTIL {

std::recursive_mutex mutex_key;
LocaleKey::LocaleKey()
	: _valid(false)
{
}

LocaleKey::~LocaleKey()
{
}

std::string LocaleKey::KeyPath()
{
	std::string path;
	if (path.empty()) {
		FilePath keyPath = FilePath::GetCurrentPath().Append("license");
		if (!keyPath.IsExist()) {
			keyPath.CreateDirectories();
		}
		path = keyPath.Append("key.bin").GetPath();
	}
	
	return path;
}

int GetAESCBCSize(int len)
{
	int remainders = len % AES_BLOCK_LEN;
	return remainders == 0 ? len : (len + (AES_BLOCK_LEN - remainders));

}
std::shared_ptr<LocaleKey> LocaleKey::Get()
{
	std::unique_lock<std::recursive_mutex> locker(mutex_key);
	FilePath filePath(KeyPath());
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
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"授权信息未被加载..."));
	}

	std::shared_ptr<LocaleKey> curKey = GetSystemKey();
	if (!curKey) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"获取本地系统信息失败。"));
	}

	std::string decryptedText;
	CryptoPP::AES::Decryption aesDecryption(s_key_2, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, s_iv_2);
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(buffer), len);
	stfDecryptor.MessageEnd();
	len = decryptedText.size();

	Json json(StringUtil::UTF8ToString(decryptedText.c_str()).c_str());
	if (!json.Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"读取本地key文件失败。"));
	}
	JsonNode validNode = json.GetNode(L"valid");
	if (!validNode.Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"本地key文件无效节点: valid"));
	}
	JsonNode updateTimeNode = json.GetNode(L"updateTime");
	if (!updateTimeNode.Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"本地key文件无效节点: updateTime"));
	}
	JsonNode diskNode = json.GetNode(L"diskSerialNo");
	if (!diskNode.Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_DiskSerialNo(L"本地key文件缺失硬盘序列号。"));
	}
	JsonNode macNode = json.GetNode(L"macAddr");
	if (!macNode.Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_MacAddr(L"本地key文件缺失mac地址。"));
	}
	JsonNode randomNode = json.GetNode(L"randomCode");
	if (!randomNode.Valid()) {
		ExceptionThrow(LicenseException, LicenseException::E_RandomCode(L"本地key文件缺失随机码。"));
	}

	std::shared_ptr<LocaleKey> storeKey(new LocaleKey());
	storeKey->_valid = validNode.GetValue<bool>();
	storeKey->_updateTime = StringUtil::StringToUTF8(updateTimeNode.GetValue().c_str());
	storeKey->_randomCode = StringUtil::StringToUTF8(randomNode.GetValue().c_str());
	storeKey->_diskSerialNo = StringUtil::StringToUTF8(diskNode.GetValue().c_str());
	storeKey->_macAddr = StringUtil::StringToUTF8(macNode.GetValue().c_str());

	JsonNode createTimeNode = json.GetNode(L"createTime");
	if (createTimeNode.Valid()) {
		storeKey->_createTime = StringUtil::StringToUTF8(createTimeNode.GetValue().c_str());
	}
	JsonNode companyNode = json.GetNode(L"companyName");
	if (companyNode.Valid()) {
		storeKey->_companyName = StringUtil::StringToUTF8(companyNode.GetValue().c_str());
	}
	JsonNode addressNode = json.GetNode(L"address");
	if (addressNode.Valid()) {
		storeKey->_address = StringUtil::StringToUTF8(addressNode.GetValue().c_str());
	}
	JsonNode corporateNode = json.GetNode(L"corporate");
	if (corporateNode.Valid()) {
		storeKey->_corporate = StringUtil::StringToUTF8(corporateNode.GetValue().c_str());
	}
	JsonNode contactsNode = json.GetNode(L"contacts");
	if (contactsNode.Valid()) {
		storeKey->_contacts = StringUtil::StringToUTF8(contactsNode.GetValue().c_str());
	}
	JsonNode deadtimeNode = json.GetNode(L"deadtime");
	if (deadtimeNode.Valid()) {
		storeKey->_deadtime = StringUtil::StringToUTF8(deadtimeNode.GetValue().c_str());
	}
	JsonNode maxUsersNode = json.GetNode(L"maxUsers");
	if (maxUsersNode.Valid()) {
		storeKey->_maxUsers = maxUsersNode.GetValue<int>();
	}
	JsonNode maxConcurrencyNode = json.GetNode(L"maxConcurrency");
	if (maxConcurrencyNode.Valid()) {
		storeKey->_maxConcurrency = maxConcurrencyNode.GetValue<int>();
	}
	JsonNode renewNode = json.GetNode(L"renew");
	if (renewNode.Valid()) {
		storeKey->_renew = renewNode.GetValue<bool>();
	}
	return storeKey;
}

std::string LocaleKey::decryptData(const std::string & data)
{
	int len = data.size();
	std::string decryptedText;
	CryptoPP::AES::Decryption aesDecryption(s_key_2, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, s_iv_2);
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(data.c_str()), len);
	stfDecryptor.MessageEnd();
	len = decryptedText.size();
	return decryptedText;
}

void LocaleKey::CCCCCheck(const std::string & data)
{
	int len = 0;
	char * buffer = nullptr;
	std::ifstream in("H:\\1.bin", std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
	if (in.is_open()) {
		len = in.tellg();
		in.seekg(0, std::ios_base::beg);
		buffer = new char[len];
		in.read(buffer, len);
		in.close();
	}
	if (buffer == nullptr) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"读取本地key文件失败。"));
	}

	std::string decryptedText;
	CryptoPP::AES::Decryption aesDecryption(s_key_2, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, s_iv_2);
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(buffer), len);
	stfDecryptor.MessageEnd();
	decryptedText.size();
}

bool LocaleKey::IsExist()
{
	FilePath filePath(KeyPath());
	return filePath.IsExist();
}

std::shared_ptr<LocaleKey> LocaleKey::create()
{
	std::unique_lock<std::recursive_mutex> locker(mutex_key);
	FilePath filePath(KeyPath());
	if (filePath.IsExist()) {
		File file(filePath);
		file.Delete();
	}
	std::shared_ptr<LocaleKey> curKey = GetSystemKey();
	if (!curKey) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"获取本地系统信息失败。"));
	}

	boost::gregorian::date curDay = boost::gregorian::day_clock::local_day();
	Json json;
	json.CreateNode(L"valid").SetValue(true);
	json.CreateNode(L"updateTime").SetValue(StringUtil::UTF8ToString(boost::gregorian::to_simple_string(curDay).c_str()));
	json.CreateNode(L"diskSerialNo").SetValue(StringUtil::UTF8ToString(curKey->_diskSerialNo.c_str()));
	json.CreateNode(L"macAddr").SetValue(StringUtil::UTF8ToString(curKey->_macAddr.c_str()));
	json.CreateNode(L"randomCode").SetValue(StringUtil::UTF8ToString(StringUtil::uuid().c_str()));
	std::wostringstream ss;
	json.Write(ss);
	std::string context = StringUtil::StringToUTF8(ss.str().c_str());
	int len = context.size();

	// 加密
	std::string cipherText;
	CryptoPP::AES::Encryption aesEncryption(s_key_2, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, s_iv_2);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(context.c_str()), len);
	stfEncryptor.MessageEnd();
	len = cipherText.size();

	std::ofstream of(filePath.GetPath().c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc/* | std::ios_base::_Nocreate */);
	if (of.is_open()) {
		of.write(cipherText.c_str(), len);
		of.close();
	}

	curKey->_valid = true;
	return curKey;
}

std::shared_ptr<LocaleKey> LocaleKey::create(const std::string & additional)
{
	std::unique_lock<std::recursive_mutex> locker(mutex_key);
	// 已存在key文件，则是续签，key文件的id不变。
	std::string randomCode;
	FilePath filePath(KeyPath());
	if (filePath.IsExist()) {
		try {
			std::shared_ptr<LocaleKey> existKey = Get();
			randomCode = existKey->GetRandomCode();
		}
		catch (Exception& exc) {
			randomCode.clear();
		}
		File file(filePath);
		file.Delete();
	}

	std::shared_ptr<LocaleKey> curKey = GetSystemKey();
	if (!curKey) {
		ExceptionThrow(LicenseException, LicenseException::E_LocaleKey(L"获取本地系统信息失败。"));
	}

	boost::gregorian::date curDay = boost::gregorian::day_clock::local_day();
	Json json(StringUtil::UTF8ToString(additional.c_str()).c_str());
	JsonNode node = json.GetRoot();
	node.GetNode(L"valid", true).SetValue(true);
	node.GetNode(L"updateTime", true).SetValue(StringUtil::UTF8ToString(boost::gregorian::to_simple_string(curDay).c_str()));
	node.GetNode(L"diskSerialNo", true).SetValue(StringUtil::UTF8ToString(curKey->_diskSerialNo.c_str()));
	node.GetNode(L"macAddr", true).SetValue(StringUtil::UTF8ToString(curKey->_macAddr.c_str()));
	node.GetNode(L"randomCode", true).SetValue(StringUtil::UTF8ToString(randomCode.empty() ? StringUtil::uuid().c_str() : randomCode.c_str()));
	node.GetNode(L"createTime", true).SetValue(StringUtil::UTF8ToString(boost::gregorian::to_simple_string(curDay).c_str()));
	node.GetNode(L"renew", true).SetValue(!randomCode.empty());
	std::wostringstream ss;
	json.Write(ss);
	std::string context = StringUtil::StringToUTF8(ss.str().c_str());
	int len = context.size();

	// 加密
	std::string cipherText;
	CryptoPP::AES::Encryption aesEncryption(s_key_2, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, s_iv_2);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(context.c_str()), len);
	stfEncryptor.MessageEnd();
	len = cipherText.size();

	std::ofstream of(filePath.GetPath().c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc/* | std::ios_base::_Nocreate */);
	if (of.is_open()) {
		of.write(cipherText.c_str(), len);
		//of.write(context.c_str(), len);
		of.close();
	}

	curKey->_valid = true;
	return curKey;
}

std::shared_ptr<LocaleKey> LocaleKey::GetSystemKey()
{
	System sys;
	std::string diskSerialNo = sys.GetMainHardDiskId();
	std::string macAddr = sys.GetNetworkAdapterId();

	std::shared_ptr<LocaleKey> key(new LocaleKey());
	key->_diskSerialNo = diskSerialNo;
	key->_macAddr = macAddr;

	return key;
}

void LocaleKey::UpdateKey(const std::shared_ptr<LocaleKey>& key)
{
	std::unique_lock<std::recursive_mutex> locker(mutex_key);
	FilePath filePath(KeyPath());
	if (!filePath.IsExist()) {
		return;
	}

	boost::gregorian::date curDay = boost::gregorian::day_clock::local_day();
	Json json;
	json.CreateNode(L"valid").SetValue(key->Valid());
	json.CreateNode(L"updateTime").SetValue(StringUtil::UTF8ToString(boost::gregorian::to_simple_string(curDay).c_str()));
	json.CreateNode(L"diskSerialNo").SetValue(StringUtil::UTF8ToString(key->_diskSerialNo.c_str()));
	json.CreateNode(L"macAddr").SetValue(StringUtil::UTF8ToString(key->_macAddr.c_str()));
	json.CreateNode(L"randomCode").SetValue(StringUtil::UTF8ToString(key->GetRandomCode().c_str()));
	json.CreateNode(L"companyName").SetValue(StringUtil::UTF8ToString(key->GetCompanyName().c_str()));
	json.CreateNode(L"address").SetValue(StringUtil::UTF8ToString(key->GetAddress().c_str()));
	json.CreateNode(L"corporate").SetValue(StringUtil::UTF8ToString(key->GetCorporate().c_str()));
	json.CreateNode(L"contacts").SetValue(StringUtil::UTF8ToString(key->GetContacts().c_str()));
	json.CreateNode(L"deadtime").SetValue(StringUtil::UTF8ToString(key->GetDeadTime().c_str()));
	json.CreateNode(L"maxUsers").SetValue(key->GetMaxUsers());
	json.CreateNode(L"maxConcurrency").SetValue(key->GetMaxConcurrency());
	json.CreateNode(L"createTime").SetValue(StringUtil::UTF8ToString(key->GetCreateTime().c_str()));
	json.CreateNode(L"renew").SetValue(key->GetRenew());
	std::wostringstream ss;
	json.Write(ss);
	std::string context = StringUtil::StringToUTF8(ss.str().c_str());
	int len = context.size();

	// 加密
	std::string cipherText;
	CryptoPP::AES::Encryption aesEncryption(s_key_2, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, s_iv_2);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(context.c_str()), len);
	stfEncryptor.MessageEnd();
	len = cipherText.size();

	std::ofstream of(filePath.GetPath().c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc/* | std::ios_base::_Nocreate */);
	if (of.is_open()) {
		of.write(cipherText.c_str(), len);
		of.close();
	}
}

}
