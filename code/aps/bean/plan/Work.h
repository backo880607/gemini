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

  DECLARE_FIELD(gemini::Boolean, active)              ///< 是否有效
  DECLARE_FIELD(gemini::Boolean, fixSplit)            ///< 分割固定
  DECLARE_FIELD(gemini::Double, qty)                  ///< 计划制造数量
  DECLARE_FIELD(gemini::Double, userQty)              ///< 指定制造数量
  DECLARE_FIELD(WorkType, workType)                   ///< 工作类型
  DECLARE_FIELD(PlanStatus, workStatus)               ///< 工作状态
  DECLARE_FIELD(gemini::DurationExtend, userManuf)    ///< 指定制造时间
  DECLARE_FIELD(gemini::DurationExtend, userPrevSet)  ///< 指定前设置时间
  DECLARE_FIELD(gemini::DurationExtend, userNextSet)  ///< 指定后设置时间
  DECLARE_FIELD(gemini::DateTime, userEST)  ///< 指定最早开始日期
  DECLARE_FIELD(gemini::DateTime, userLET)  ///< 指定最晚结束时刻
  DECLARE_FIELD(gemini::DateTime, calcEST)  ///< 最早开始日期计算时刻
  DECLARE_FIELD(gemini::DateTime, calcLET)  ///< 最晚结束日期计算时刻
  DECLARE_FIELD(gemini::DateTime, userStart)   ///< 指定开始时刻
  DECLARE_FIELD(gemini::DateTime, userEnd)     ///< 指定结束时刻
  DECLARE_FIELD(gemini::DateTime, planStart)   ///< 计划开始时刻
  DECLARE_FIELD(gemini::DateTime, planEnd)     ///< 计划结束时刻
  DECLARE_FIELD(gemini::String, planResource)  ///< 计划资源
  DECLARE_FIELD(gemini::String, code)          ///< 代码
  DECLARE_FIELD(gemini::String, remark)        ///< 备注

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