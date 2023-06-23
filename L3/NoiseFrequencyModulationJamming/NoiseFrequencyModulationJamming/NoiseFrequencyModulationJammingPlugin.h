#ifndef NOISEFREQUENCYMODULATIONJAMMING_H
#define NOISEFREQUENCYMODULATIONJAMMING_H
#ifdef NOISEFREQUENCYMODULATIONJAMMING_EXPORTS
#define NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS __declspec(dllexport)
#else
#define NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "NoiseFrequencyModulationJammingModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
namespace GPUSignalAlgorithm
{
	class NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS NoiseFrequencyModulationJammingPlugin
	{
	public:
		NoiseFrequencyModulationJammingPlugin();
		~NoiseFrequencyModulationJammingPlugin();
		NoiseFrequencyModulationJammingModule * PluginNoiseFrequencyModulationJamming();
	private:
		NoiseFrequencyModulationJammingModule * Noise_Frequency_Modulation_Jamming_Module_Pointer;
	};
}
#endif

