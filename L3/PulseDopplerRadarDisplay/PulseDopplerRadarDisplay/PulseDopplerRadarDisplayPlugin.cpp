#include "PulseDopplerRadarDisplayPlugin.h"

namespace GPUSignalAlgorithm
{
	PulseDopplerRadarDisplayPlugin::PulseDopplerRadarDisplayPlugin()
	{
		this->Pulse_Doppler_Radar_Display_Module_Pointer = nullptr;
	}
	PulseDopplerRadarDisplayPlugin::~PulseDopplerRadarDisplayPlugin()
	{
		delete this->Pulse_Doppler_Radar_Display_Module_Pointer;
	}
	PulseDopplerRadarDisplayModule * PulseDopplerRadarDisplayPlugin::PlugPulseDopplerRadarDisplay()
	{
		this->Pulse_Doppler_Radar_Display_Module_Pointer = new PulseDopplerRadarDisplayModule;
		return(this->Pulse_Doppler_Radar_Display_Module_Pointer);

	}
}