//只对外暴露IJamComponentFactory接口类
#ifndef MOVINGTARGETINDICATOR_H
#define MOVINGTARGETINDICATOR_H
#ifdef MOVINGTARGETINDICATOR_EXPORTS
#define MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllexport)
#else
#define MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "MovingTargetIndicatorModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class MOVING_TARGET_INDICATOR_EXPORTS MovingTargetIndicatorPlugin
	{
	public:
		MovingTargetIndicatorPlugin();
		~MovingTargetIndicatorPlugin();
		MovingTargetIndicatorModule * PluginMovingTargetIndicator();
	private:
		MovingTargetIndicatorModule * Moving_Target_Indicator_Module_Pointer;
	};
}
#endif

