// BasebandReceiverSensitivityTime.cpp : ���� DLL Ӧ�ó���ĵ���������
#include "stdafx.h"
#include "BasebandReceiverSensitivityTimePlugin.h"

namespace GPUSignalAlgorithm
{
	BasebandReceiverSensitivityTimePlugin::BasebandReceiverSensitivityTimePlugin()
	{
		this->Baseband_Receiver_Sensitivity_Time_Module_Pointer = nullptr;
	}
	BasebandReceiverSensitivityTimePlugin::~BasebandReceiverSensitivityTimePlugin()
	{
		delete this->Baseband_Receiver_Sensitivity_Time_Module_Pointer;
	}
	BasebandReceiverSensitivityTimeModule * BasebandReceiverSensitivityTimePlugin::PluginBasebandReceiverSensitivityTime()
	{
		this->Baseband_Receiver_Sensitivity_Time_Module_Pointer = new BasebandReceiverSensitivityTimeModule;
		return(this->Baseband_Receiver_Sensitivity_Time_Module_Pointer);
	}
}

