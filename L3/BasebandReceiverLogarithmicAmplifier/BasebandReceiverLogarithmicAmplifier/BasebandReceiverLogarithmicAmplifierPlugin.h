//只对外暴露IJamComponentFactory接口类
#ifndef BASEBANDRECEIVERLOGARITHMICAMPLIFIER_H
#define BASEBANDRECEIVERLOGARITHMICAMPLIFIER_H
#ifdef BASEBANDRECEIVERLOGARITHMICAMPLIFIER_EXPORTS
#define BASEBAND_RECEIVER_LOGARITHMIC_AMPLIFIER_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_LOGARITHMIC_AMPLIFIER_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "BasebandReceiverLogarithmicAmplifierModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_LOGARITHMIC_AMPLIFIER_EXPORTS BasebandReceiverLogarithmicAmplifierPlugin
	{
	public:
		BasebandReceiverLogarithmicAmplifierPlugin();
		~BasebandReceiverLogarithmicAmplifierPlugin();
		BasebandReceiverLogarithmicAmplifierModule * PluginBasebandReceiverLogarithmicAmplifier();
	private:
		BasebandReceiverLogarithmicAmplifierModule * Baseband_Receiver_Logarithmic_Amplifier_Module_Pointer;
	};
}
#endif

