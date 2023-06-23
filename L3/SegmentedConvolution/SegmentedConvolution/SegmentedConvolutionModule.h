#ifndef SEGMENTEDCONVOLUTIONMODULE_H
#define SEGMENTEDCONVOLUTIONMODULE_H
#ifdef SEGMENTEDCONVOLUTION_EXPORTS
#define SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDASegmentedConvolution.h"
namespace GPUSignalAlgorithm
{
	class SEGMENTED_CONVOLUTION_EXPORTS SegmentedConvolutionModule
	{
	public:
		SegmentedConvolutionModule();
		~SegmentedConvolutionModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		struct SignalParameter OutputData();
	private:
		CUDASegmentedConvolutionNamespace::CUDASegmentedConvolution *CUDA_Segmented_Convolution_Pointer;
		struct SignalParameter Input_Data;
		struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
		//struct SignalParameter Output_Data;//不一定用得上，先挂着。
		//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif