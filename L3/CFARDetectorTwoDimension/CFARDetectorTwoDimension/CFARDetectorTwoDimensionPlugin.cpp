// CFARDetectorTwoDimension.cpp : ���� DLL Ӧ�ó���ĵ���������
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
