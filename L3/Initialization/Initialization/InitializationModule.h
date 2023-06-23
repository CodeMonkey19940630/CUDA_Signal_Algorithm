#ifndef INITIALIZATIONMODULE_H
#define INITIALIZATIONMODULE_H
#ifdef INITIALIZATION_EXPORTS
#define INITIALISATION_EXPORTS __declspec(dllexport)
#else
#define INITIALISATION_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAInitialization.h"
namespace GPUSignalAlgorithm
{
	class INITIALISATION_EXPORTS InitializationModule
	{
	public:
		InitializationModule();
		~InitializationModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		struct SignalParameter OutputData();
	private:
		CUDAInitializationNamespace::CUDAInitialization * CUDA_Initialization_Pointer;
		struct SignalParameter Input_Data;
		struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
		//struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//不一定用得上，先挂着。
		//struct SignalParameter Output_Data;//不一定用得上，先挂着。
		//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif