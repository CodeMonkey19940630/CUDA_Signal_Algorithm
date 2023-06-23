//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef PULSEEDOPPLERRADARDISPLY_H
#define PULSEEDOPPLERRADARDISPLY_H
#ifdef PULSEDOPPLERRADARDISPLAY_EXPORTS
#define PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllexport)
#else
#define PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "PulseDopplerRadarDisplayModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
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

