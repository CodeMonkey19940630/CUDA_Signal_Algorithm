#include "MatchFilterSegmentedConvolutionPlugin.h"

namespace GPUSignalAlgorithm
{
	MatchFilterSegmentedConvolutionPlugin::MatchFilterSegmentedConvolutionPlugin()
	{
		this->Match_Filter_Segmented_Convolution_Module_Pointer = nullptr;
	}
	MatchFilterSegmentedConvolutionPlugin::~MatchFilterSegmentedConvolutionPlugin()
	{
		delete this->Match_Filter_Segmented_Convolution_Module_Pointer;
	}
	MatchFilterSegmentedConvolutionModule * MatchFilterSegmentedConvolutionPlugin::PluginMatchFilterSegmentedConvolution()
	{
		this->Match_Filter_Segmented_Convolution_Module_Pointer = new MatchFilterSegmentedConvolutionModule;
		return(this->Match_Filter_Segmented_Convolution_Module_Pointer);

	}
}


