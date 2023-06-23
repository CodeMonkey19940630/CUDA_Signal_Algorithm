//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef INTERRUPTEDSAMPLINGREPEATERJAMMING_H
#define INTERRUPTEDSAMPLINGREPEATERJAMMING_H
#ifdef INTERRUPTEDSAMPLINGREPEATERJAMMING_EXPORTS
#define INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS __declspec(dllexport)
#else
#define INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "InterruptedSamplingRepeaterJammingModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
namespace GPUSignalAlgorithm
{
	class INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS InterruptedSamplingRepeaterJammingPlugin
	{
	public:
		InterruptedSamplingRepeaterJammingPlugin();
		~InterruptedSamplingRepeaterJammingPlugin();
		InterruptedSamplingRepeaterJammingModule * PluginInterruptedSamplingRepeaterJamming();
	private:
		InterruptedSamplingRepeaterJammingModule * Interrupted_Sampling_Repeater_Jamming_Module_Pointer;
	};
}
#endif

