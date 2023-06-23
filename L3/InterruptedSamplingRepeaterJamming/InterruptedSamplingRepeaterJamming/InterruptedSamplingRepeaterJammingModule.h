#ifndef INTERRUPTEDSAMPLINGREPEATERJAMMINGMODULE_H
#define INTERRUPTEDSAMPLINGREPEATERJAMMINGMODULE_H
#ifdef INTERRUPTEDSAMPLINGREPEATERJAMMING_EXPORTS
#define INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS __declspec(dllexport)
#else
#define INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAInterruptedSamplingRepeaterJamming.h"
namespace GPUSignalAlgorithm
{
	class INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS InterruptedSamplingRepeaterJammingModule
	{
	public:
		InterruptedSamplingRepeaterJammingModule();
		~InterruptedSamplingRepeaterJammingModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDAInterruptedSamplingRepeaterJammingNamespace::CUDAInterruptedSamplingRepeaterJamming * CUDA_Interrupted_Sampling_Repeater_Jamming_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//不一定用得上，先挂着。
		//struct SignalParameter Output_Data;//不一定用得上，先挂着。
		//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif