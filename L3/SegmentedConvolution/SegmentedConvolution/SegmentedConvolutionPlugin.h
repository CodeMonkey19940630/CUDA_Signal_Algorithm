#ifndef SEGMENTEDCONVOLUTION_H
#define SEGMENTEDCONVOLUTION_H
#ifdef SEGMENTEDCONVOLUTION_EXPORTS
#define SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
#include "SegmentedConvolutionModule.h"
namespace GPUSignalAlgorithm
{
	class SEGMENTED_CONVOLUTION_EXPORTS SegmentedConvolutionPlugin
	{
	public:
		SegmentedConvolutionPlugin();
		~SegmentedConvolutionPlugin();
		SegmentedConvolutionModule * PluginSegmentedConvolution();
	private:
		SegmentedConvolutionModule * Segmented_Convolution_Module_Pointer;
	};
}
#endif

