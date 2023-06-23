#ifndef MATCHFILTERMODULE_H
#define MATCHFILTERMODULE_H
#ifdef MATCHFILTER_EXPORTS
#define MATCH_FILTER_EXPORTS __declspec(dllexport)
#else
#define MATCH_FILTER_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAMatchFilter.h"
namespace GPUSignalAlgorithm
{
	class MATCH_FILTER_EXPORTS MatchFilterModule
	{
	public:
		MatchFilterModule();
		~MatchFilterModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		struct SignalParameter OutputData();
	private:
		CUDAMatchFilterNamespace::CUDAMatchFilter * CUDA_Match_Filter_Pointer;
		struct SignalParameter Input_Data;
		struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif