//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef CFARDETECTORTWODIMENSION_H
#define CFARDETECTORTWODIMENSION_H
#ifdef CFARDETECTORTWODIMENSION_EXPORTS
#define CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllexport)
#else
#define CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "CFARDetectorTwoDimensionModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
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

