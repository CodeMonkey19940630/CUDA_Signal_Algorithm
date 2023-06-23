//只对外暴露IJamComponentFactory接口类
#ifndef BASEBANDRECEIVERSENSITIVITYTIME_H
#define BASEBANDRECEIVERSENSITIVITYTIME_H
#ifdef BASEBANDRECEIVERSENSITIVITYTIME_EXPORTS
#define BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "BasebandReceiverSensitivityTimeModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS BasebandReceiverSensitivityTimePlugin
	{
	public:
		BasebandReceiverSensitivityTimePlugin();
		~BasebandReceiverSensitivityTimePlugin();
		BasebandReceiverSensitivityTimeModule * PluginBasebandReceiverSensitivityTime();
	private:
		BasebandReceiverSensitivityTimeModule * Baseband_Receiver_Sensitivity_Time_Module_Pointer;
	};
}
#endif

