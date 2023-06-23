#ifndef MATCHFILTERSEGMENTEDCONVOLUTIONMODULE_H
#define MATCHFILTERSEGMENTEDCONVOLUTIONMODULE_H
#ifdef MATCHFILTERSEGMENTEDCONVOLUTION_EXPORTS
#define MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAMatchFilterSegmentedConvolution.h"
namespace GPUSignalAlgorithm
{
	class MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS MatchFilterSegmentedConvolutionModule
	{
	public:
		MatchFilterSegmentedConvolutionModule();
		~MatchFilterSegmentedConvolutionModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		struct SignalParameter OutputData();
	private:
		CUDAMatchFilterSegmentedConvolutionNamespace::CUDAMatchFilterSegmentedConvolution * CUDA_Match_Filter_Segmented_Convolution_Pointer;
		struct SignalParameter Input_Data;
		struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
		//struct SignalParameter Output_Data;//不一定用得上，先挂着。
		//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif