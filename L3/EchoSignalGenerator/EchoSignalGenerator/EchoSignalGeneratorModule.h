#ifndef ECHOSIGNALGENERATORMODULE_H
#define ECHOSIGNALGENERATORMODULE_H
#ifdef ECHOSIGNALGENERATOR_EXPORTS
#define ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllexport)
#else
#define ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAEchoSignalGenerator.h"
namespace GPUSignalAlgorithm
{
	class ECHO_SIGNAL_GENERATOR_EXPORTS EchoSignalGeneratorModule
	{
	public:
		EchoSignalGeneratorModule();
		~EchoSignalGeneratorModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDAEchoSignalGeneratorNamespace::CUDAEchoSignalGenerator * CUDA_Echo_Signal_Generator_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif