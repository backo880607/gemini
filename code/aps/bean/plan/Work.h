#ifndef APS_Work_INCLUDE
#define APS_Work_INCLUDE
#include "../../public/enums/EPlan.h"

namespace aps {

class Order;
class WorkIn;
class WorkOut;
class WorkRes;
class Task;
class ToolTask;
class RouteStep;
class WorkFdbk;
class ParentWork;
class APS_API Work : public gemini::Entity {
  DECLARE_CLASS(Work, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)              ///< �Ƿ���Ч
  DECLARE_FIELD(gemini::Boolean, fixSplit)            ///< �ָ�̶�
  DECLARE_FIELD(gemini::Double, qty)                  ///< �ƻ���������
  DECLARE_FIELD(gemini::Double, userQty)              ///< ָ����������
  DECLARE_FIELD(WorkType, workType)                   ///< ��������
  DECLARE_FIELD(PlanStatus, workStatus)               ///< ����״̬
  DECLARE_FIELD(gemini::DurationExtend, userManuf)    ///< ָ������ʱ��
  DECLARE_FIELD(gemini::DurationExtend, userPrevSet)  ///< ָ��ǰ����ʱ��
  DECLARE_FIELD(gemini::DurationExtend, userNextSet)  ///< ָ��������ʱ��
  DECLARE_FIELD(gemini::DateTime, userEST)  ///< ָ�����翪ʼ����
  DECLARE_FIELD(gemini::DateTime, userLET)  ///< ָ���������ʱ��
  DECLARE_FIELD(gemini::DateTime, calcEST)  ///< ���翪ʼ���ڼ���ʱ��
  DECLARE_FIELD(gemini::DateTime, calcLET)  ///< ����������ڼ���ʱ��
  DECLARE_FIELD(gemini::DateTime, userStart)   ///< ָ����ʼʱ��
  DECLARE_FIELD(gemini::DateTime, userEnd)     ///< ָ������ʱ��
  DECLARE_FIELD(gemini::DateTime, planStart)   ///< �ƻ���ʼʱ��
  DECLARE_FIELD(gemini::DateTime, planEnd)     ///< �ƻ�����ʱ��
  DECLARE_FIELD(gemini::String, planResource)  ///< �ƻ���Դ
  DECLARE_FIELD(gemini::String, code)          ///< ����
  DECLARE_FIELD(gemini::String, remark)        ///< ��ע

  DECLARE_ENTITY(Order, order)
  DECLARE_ENTITY(ParentWork, parent)
  DECLARE_VECTOR(WorkIn, workIns)
  DECLARE_VECTOR(WorkOut, workOuts)
  DECLARE_VECTOR(WorkRes, workReses)
  DECLARE_ENTITY(Task, task)
  DECLARE_VECTOR(ToolTask, toolTasks)
  DECLARE_ENTITY(RouteStep, routeStep)
  DECLARE_VECTOR(WorkFdbk, workFdbk)
};

}  // namespace aps
#endif  // !APS_Work_INCLUDE