//只对外暴露IJamComponentFactory接口类
#ifndef INTERRUPTEDSAMPLINGREPEATERJAMMING_H
#define INTERRUPTEDSAMPLINGREPEATERJAMMING_H
#ifdef INTERRUPTEDSAMPLINGREPEATERJAMMING_EXPORTS
#define INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS __declspec(dllexport)
#else
#define INTERRUPTED_SAMPLING_REPEATER_JAMMING_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "InterruptedSamplingRepeaterJammingModule.h"
//PulseDopplerRadarDisplay接口类定义
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

