//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef BASEBANDRECEIVERAMPLIFIERSATURATION_H 
#define BASEBANDRECEIVERAMPLIFIERSATURATION_H
#ifdef BASEBANDRECEIVERAMPLIFIERSATURATION_EXPORTS
#define BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "BasebandReceiverAmplifierSaturationModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
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

