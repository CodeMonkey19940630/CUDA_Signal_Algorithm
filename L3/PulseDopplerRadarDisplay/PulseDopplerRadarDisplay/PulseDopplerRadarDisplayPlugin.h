//只对外暴露IJamComponentFactory接口类
#ifndef PULSEEDOPPLERRADARDISPLY_H
#define PULSEEDOPPLERRADARDISPLY_H
#ifdef PULSEDOPPLERRADARDISPLAY_EXPORTS
#define PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllexport)
#else
#define PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "PulseDopplerRadarDisplayModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS PulseDopplerRadarDisplayPlugin
	{
	public:
		PulseDopplerRadarDisplayPlugin();
		~PulseDopplerRadarDisplayPlugin();
		PulseDopplerRadarDisplayModule * PlugPulseDopplerRadarDisplay();
	private:
		PulseDopplerRadarDisplayModule * Pulse_Doppler_Radar_Display_Module_Pointer;
	};
}
#endif

