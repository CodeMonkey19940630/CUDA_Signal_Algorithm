//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef MOVINGTARGETINDICATOR_H
#define MOVINGTARGETINDICATOR_H
#ifdef MOVINGTARGETINDICATOR_EXPORTS
#define MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllexport)
#else
#define MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "MovingTargetIndicatorModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
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

