#include <boost/test/unit_test.hpp>

#include "../public/session/UsernamePasswordToken.h"
#include "../public/session/Subject.h"

BOOST_AUTO_TEST_CASE(t_test_session)
{
	using namespace gemini;
	UsernamePasswordToken token(u8"niuhaitao", u8"123456");
	const Subject& subject = Subject::get();
	subject.login(token);

}