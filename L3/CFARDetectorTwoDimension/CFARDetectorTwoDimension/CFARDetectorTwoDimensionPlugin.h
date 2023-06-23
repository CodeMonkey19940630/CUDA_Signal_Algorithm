//只对外暴露IJamComponentFactory接口类
#ifndef CFARDETECTORTWODIMENSION_H
#define CFARDETECTORTWODIMENSION_H
#ifdef CFARDETECTORTWODIMENSION_EXPORTS
#define CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllexport)
#else
#define CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "CFARDetectorTwoDimensionModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class CFAR_DETECTOR_TWO_DIMENSION_EXPORTS CFARDetectorTwoDimensionPlugin
	{
	public:
		CFARDetectorTwoDimensionPlugin();
		~CFARDetectorTwoDimensionPlugin();
		CFARDetectorTwoDimensionModule * PluginCFARDetectorTwoDimension();
	private:
		CFARDetectorTwoDimensionModule * CFAR_Detector_Two_Dimension_Module_Pointer;
	};
}
#endif

