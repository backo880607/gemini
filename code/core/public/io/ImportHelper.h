#ifndef GEMINI_IO_ImportHelper_INCLUDE
#define GEMINI_IO_ImportHelper_INCLUDE
#include "DataSource.h"

namespace gemini
{
namespace io
{
class IOScheme;
class ImportHelper
{
  public:
    ImportHelper(SmartPtr<IOScheme> scheme);
    ~ImportHelper();

    void execute();

	template <typename T, typename HANDLER>
	void registerHandler() {
		_dataHandler.registerHandler(Class::forType<T>(), new HANDLER());
	}

	template <typename CLS, typename FIELD, typename HANDLER>
	void registerFieldHandler() {
		_dataHandler.registerHandler(Class::forType<CLS>(), FIELD::index(), new HANDLER());
	}
  private:
    Boolean parseIOScheme();
	void write(EntityObject::SPtr entity, const Field* field, const String& value);

  private:
    std::shared_ptr<DataSource> _dataSource;
    SmartPtr<IOScheme> _scheme;
	DataHandlerHelper _dataHandler;
};

} // namespace io
} // namespace gemini
#endif // GEMINI_IO_ImportHelper_INCLUDE