#include "AuthorizeCheck.h"
#include "Authorize.h"
#include "LocaleKey.h"
#include "LicenseException.h"
#include "AuthorizeManager.h"
#include "Log.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace APSUTIL {

boost::asio::io_context g_AuthorizeCheckIOS;
AuthorizeCheck::AuthorizeCheck()
	: m_timeSpan(30)
	, m_checkTimer(g_AuthorizeCheckIOS)
{
}


AuthorizeCheck::~AuthorizeCheck()
{
}

void AuthorizeCheck::Start()
{
	m_thread.reset(new boost::thread(CheckImpl));
}

void AuthorizeCheck::Stop()
{
	if (!m_thread) {
		return;
	}

	g_AuthorizeCheckIOS.stop();
	//m_thread->interrupt();
	m_thread->join();
	m_thread = nullptr;
}

std::shared_ptr<LocaleKey> AuthorizeCheck::Verify()
{
	std::shared_ptr<LocaleKey> localeKey = LocaleKey::Get();
	if (!localeKey || !localeKey->Valid()) {
		ExceptionThrow(LicenseNotFound, LicenseNotFound::E_NotFound(L"授权信息未被加载..."));
	}

	std::shared_ptr<LocaleKey> curKey = LocaleKey::GetSystemKey();
	if (localeKey->GetDiskSerialNo() != curKey->GetDiskSerialNo() ||
		localeKey->GetMacAddr() != curKey->GetMacAddr()) {
		ExceptionThrow(LicenseException, LicenseException::E_ModifyHardInfo(L"硬件信息不匹配"));
	}

	boost::gregorian::date curDay = boost::gregorian::day_clock::local_day();
	if (boost::gregorian::from_simple_string(localeKey->GetUpdateTime()) > curDay) {
		ExceptionThrow(LicenseException, LicenseException::E_ModifySystemTime(L"请勿修改系统时间。"));
	}

	std::shared_ptr<Authorize> auth = Authorize::Get();
	if (auth->_keyRandomCode != localeKey->GetRandomCode()) {
		ExceptionThrow(LicenseException, LicenseException::E_RandomCode(L"本地Key文件和授权信息不匹配。"));
	}

	// 判断授权信息的截止日期。
	if (boost::gregorian::from_simple_string(auth->_deadtime) < curDay) {
		ExceptionThrow(LicenseException, LicenseException::E_Authorize(L"授权已过期。"));
	}

	// 是否超过用户数
	if (auth->GetMaxConcurrency() < AuthorizeManager::instance()._curCount) {
		ExceptionThrow(LicenseException, LicenseException::E_MaxCount(L"超过了最大并发数限制。"));
	}

	return localeKey;
}

void AuthorizeCheck::CheckImpl()
{
	AuthorizeCheck::instance().Check();
	g_AuthorizeCheckIOS.run();
}

void AuthorizeCheck::Check()
{
	try {
		boost::unique_lock<boost::mutex> locker(AuthorizeCheck::instance().GetMutex());
		std::shared_ptr<LocaleKey> localeKey = AuthorizeCheck::Verify();
		// 更新Key文件的更新时间。
		AuthorizeManager::instance()._valid = true;
		LocaleKey::UpdateKey(localeKey);
	}
	catch (Exception& exc) {
		AuthorizeManager::instance()._valid = false;
		APSLOG(Logger::LOG_ERROR).Log(exc.Description());
	}

	m_checkTimer.expires_from_now(std::chrono::seconds(m_timeSpan));
	m_checkTimer.async_wait(boost::bind(&AuthorizeCheck::Check, this));
}

}
