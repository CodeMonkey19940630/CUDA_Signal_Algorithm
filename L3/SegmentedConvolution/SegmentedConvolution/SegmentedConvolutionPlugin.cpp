// SegmentedConvolution.cpp : 定义 DLL 应用程序的导出函数。
#include "SegmentedConvolutionPlugin.h"

namespace GPUSignalAlgorithm
{
	SegmentedConvolutionPlugin::SegmentedConvolutionPlugin()
	{
		this->Segmented_Convolution_Module_Pointer = nullptr;
	}
	SegmentedConvolutionPlugin::~SegmentedConvolutionPlugin()
	{
		delete this->Segmented_Convolution_Module_Pointer;
	}
	SegmentedConvolutionModule * SegmentedConvolutionPlugin::PluginSegmentedConvolution()
	{
		this->Segmented_Convolution_Module_Pointer = new SegmentedConvolutionModule;
		return(this->Segmented_Convolution_Module_Pointer);
	}
}


