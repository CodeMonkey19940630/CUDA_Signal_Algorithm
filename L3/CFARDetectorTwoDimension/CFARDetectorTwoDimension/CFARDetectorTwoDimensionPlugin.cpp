// CFARDetectorTwoDimension.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CFARDetectorTwoDimensionPlugin.h"

namespace GPUSignalAlgorithm
{
	CFARDetectorTwoDimensionPlugin::CFARDetectorTwoDimensionPlugin()
	{
		this->CFAR_Detector_Two_Dimension_Module_Pointer = nullptr;
	}
	CFARDetectorTwoDimensionPlugin::~CFARDetectorTwoDimensionPlugin()
	{
		delete this->CFAR_Detector_Two_Dimension_Module_Pointer;
	}
	CFARDetectorTwoDimensionModule * CFARDetectorTwoDimensionPlugin::PluginCFARDetectorTwoDimension()
	{
		this->CFAR_Detector_Two_Dimension_Module_Pointer = new CFARDetectorTwoDimensionModule;
		return(this->CFAR_Detector_Two_Dimension_Module_Pointer);

	}
}
