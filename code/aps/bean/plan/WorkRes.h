#ifndef APS_WorkRes_INCLUDE
#define APS_WorkRes_INCLUDE
#include "../../public/enums/ETech.h"

namespace aps {

class Work;
class Resource;
class RouteStepRes;
class APS_API WorkRes : public gemini::Entity {
  DECLARE_CLASS(WorkRes, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)  ///< ��Ч��ʶ
  DECLARE_FIELD(gemini::Int, priority)    ///< ���ȼ�
  DECLARE_FIELD(UseType, useType)
  DECLARE_FIELD(gemini::String, matchNumber)
  DECLARE_FIELD(gemini::DurationExtend, prevSetTime)  ///< ǰ����ʱ��
  DECLARE_FIELD(gemini::DurationExtend, manufTime)    ///< ����ʱ��
  DECLARE_FIELD(gemini::DurationExtend, nextSetTime)  ///< ������ʱ��
  DECLARE_FIELD(gemini::Double, prevSetNeedResQty)  ///< ǰ���ñ�Ҫ��Դ��
  DECLARE_FIELD(gemini::Double, manufNeedResQty)    ///< �����Ҫ��Դ��
  DECLARE_FIELD(gemini::Double, nextSetNeedResQty)  ///< �����ñ�Ҫ��Դ��
  DECLARE_FIELD(gemini::DurationExtend,
                prevSetMaxSdTime)  ///< ���ǰ�����ж�ʱ��
  DECLARE_FIELD(gemini::DurationExtend, manufMaxSdTime)  ///< ��������ж�ʱ��
  DECLARE_FIELD(gemini::DurationExtend,
                nextSetMaxSdTime)  ///< ���������ж�ʱ��

  DECLARE_ENTITY(Work, work)
  DECLARE_ENTITY(Resource, res)
  DECLARE_ENTITY(RouteStepRes, routeStepRes)
};

}  // namespace aps
#endif  // !APS_WorkRes_INCLUDE