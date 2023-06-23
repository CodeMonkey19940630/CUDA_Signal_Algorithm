#include "MatchFilterPlugin.h"

namespace GPUSignalAlgorithm
{
	MatchFilterPlugin::MatchFilterPlugin()
	{
		this->Match_Filter_Module_Pointer = nullptr;
	}
	MatchFilterPlugin::~MatchFilterPlugin()
	{
		delete this->Match_Filter_Module_Pointer;
	}
	MatchFilterModule * MatchFilterPlugin::PluginMatchFilter()
	{
		this->Match_Filter_Module_Pointer = new MatchFilterModule;
		return(this->Match_Filter_Module_Pointer);
	}
}