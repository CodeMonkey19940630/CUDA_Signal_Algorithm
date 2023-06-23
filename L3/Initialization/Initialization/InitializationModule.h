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
		struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		//struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif