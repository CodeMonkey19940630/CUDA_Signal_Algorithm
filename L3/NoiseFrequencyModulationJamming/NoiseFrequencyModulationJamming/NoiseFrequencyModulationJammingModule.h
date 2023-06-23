#ifndef NOISEFREQUENCYMODULATIONJAMMINGMODULE_H
#define NOISEFREQUENCYMODULATIONJAMMINGMODULE_H
#ifdef NOISEFREQUENCYMODULATIONJAMMING_EXPORTS
#define NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS __declspec(dllexport)
#else
#define NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDANoiseFrequencyModulationJamming.h"
namespace GPUSignalAlgorithm
{
	class NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS NoiseFrequencyModulationJammingModule
	{
	public:
		NoiseFrequencyModulationJammingModule();
		~NoiseFrequencyModulationJammingModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDANoiseFrequencyModulationJammingNamespace::CUDANoiseFrequencyModulationJamming * CUDA_Noise_Frequency_Modulation_Jamming_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�
	};
}
#endif