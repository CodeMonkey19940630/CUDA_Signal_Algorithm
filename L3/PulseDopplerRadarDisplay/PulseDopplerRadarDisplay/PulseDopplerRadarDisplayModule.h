#ifndef PULSEEDOPPLERRADARDISPLYMODULE_H
#define PULSEEDOPPLERRADARDISPLYMODULE_H
#ifdef PULSEDOPPLERRADARDISPLAY_EXPORTS
#define PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllexport)
#else
#define PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAPulseDopplerRadarDisplay.h"
namespace GPUSignalAlgorithm
{
	class PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS PulseDopplerRadarDisplayModule
	{
		public:
			PulseDopplerRadarDisplayModule();
			~PulseDopplerRadarDisplayModule();
			void InputData(struct SignalParameter Input_Data);//����������˷ǶԳ���ƣ���Ҫ��������ģ��ͨ���ٴξ�����ơ�
			void SetControlParameter(struct ControlParameter Control_Parameter);
			struct ControlParameter GetControlParameter();
			void Process();
			struct SignalParameter OutputData();//����������˷ǶԳ���ơ�
		private:
			CUDAPulseDopplerRadarDisplayNamespace::CUDAPulseDopplerRadarDisplay * CUDA_Pulse_Doppler_Radar_Display_Pointer;
			struct SignalParameter Input_Data;
			struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
			struct ControlParameter Control_Parameter;
			//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
			//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
			//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif