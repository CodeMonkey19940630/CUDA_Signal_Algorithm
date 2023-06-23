//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef MATCHFILTERSEGMENTEDCONVOLUTION_H
#define MATCHFILTERSEGMENTEDCONVOLUTION_H
#ifdef MATCHFILTERSEGMENTEDCONVOLUTION_EXPORTS
#define MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "MatchFilterSegmentedConvolutionModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
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

