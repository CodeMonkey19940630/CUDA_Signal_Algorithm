#include "MovingTargetIndicatorPlugin.h"

namespace GPUSignalAlgorithm
{
	MovingTargetIndicatorPlugin::MovingTargetIndicatorPlugin()
	{
		this->Moving_Target_Indicator_Module_Pointer = nullptr;
	}
	MovingTargetIndicatorPlugin::~MovingTargetIndicatorPlugin()
	{
		delete this->Moving_Target_Indicator_Module_Pointer;
	}
	MovingTargetIndicatorModule * MovingTargetIndicatorPlugin::PluginMovingTargetIndicator()
	{
		this->Moving_Target_Indicator_Module_Pointer = new MovingTargetIndicatorModule;
		return(this->Moving_Target_Indicator_Module_Pointer);
	}
}