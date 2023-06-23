//只对外暴露IJamComponentFactory接口类
#ifndef MATCHFILTERSEGMENTEDCONVOLUTION_H
#define MATCHFILTERSEGMENTEDCONVOLUTION_H
#ifdef MATCHFILTERSEGMENTEDCONVOLUTION_EXPORTS
#define MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "MatchFilterSegmentedConvolutionModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS MatchFilterSegmentedConvolutionPlugin
	{
	public:
		MatchFilterSegmentedConvolutionPlugin();
		~MatchFilterSegmentedConvolutionPlugin();
		MatchFilterSegmentedConvolutionModule * PluginMatchFilterSegmentedConvolution();
	private:
		MatchFilterSegmentedConvolutionModule * Match_Filter_Segmented_Convolution_Module_Pointer;
	};
}
#endif

