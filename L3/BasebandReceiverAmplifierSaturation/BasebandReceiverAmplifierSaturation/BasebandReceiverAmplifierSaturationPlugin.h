//只对外暴露IJamComponentFactory接口类
#ifndef BASEBANDRECEIVERAMPLIFIERSATURATION_H 
#define BASEBANDRECEIVERAMPLIFIERSATURATION_H
#ifdef BASEBANDRECEIVERAMPLIFIERSATURATION_EXPORTS
#define BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "BasebandReceiverAmplifierSaturationModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS BasebandReceiverAmplifierSaturationPlugin
	{
	public:
		BasebandReceiverAmplifierSaturationPlugin();
		~BasebandReceiverAmplifierSaturationPlugin();
		BasebandReceiverAmplifierSaturationModule * PluginBasebandReceiverAmplifierSaturation();
	private:
		BasebandReceiverAmplifierSaturationModule * Baseband_Receiver_Amplifier_Saturation_Module_Pointer;
	};
}
#endif

