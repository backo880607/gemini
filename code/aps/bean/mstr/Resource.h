#ifndef APS_Resource_INCLUDE
#define APS_Resource_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Task class APS_API Resource : public gemini::EntityObject
{
	DECLARE_CLASS(Resource, gemini::EntityObject)

	DECLARE_FIELD(gemini::Boolean, isBottleneck) ///< 是否为瓶颈资源
	DECLARE_FIELD(gemini::Double, efficiency)	///< 制造效率
	DECLARE_FIELD(gemini::String, prevBuffer)	///< 前缓冲时间
	DECLARE_FIELD(gemini::String, nextBuffer)	///< 后缓冲时间
	DECLARE_FIELD(gemini::Double, maxManufBatch) ///< 最大制造批量

	DECLARE_VECTOR(Task, tasks)
};
} // namespace aps
#endif // !APS_Resource_INCLUDE
