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
			void InputData(struct SignalParameter Input_Data);//与输出产生了非对称设计，需要根据所有模块通性再次尽心设计。
			void SetControlParameter(struct ControlParameter Control_Parameter);
			struct ControlParameter GetControlParameter();
			void Process();
			struct SignalParameter OutputData();//与输入产生了非对称设计。
		private:
			CUDAPulseDopplerRadarDisplayNamespace::CUDAPulseDopplerRadarDisplay * CUDA_Pulse_Doppler_Radar_Display_Pointer;
			struct SignalParameter Input_Data;
			struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
			struct ControlParameter Control_Parameter;
			//struct ControlParameter Temporary_Storage_Control_Parameter;//不一定用得上，先挂着。
			//struct SignalParameter Output_Data;//不一定用得上，先挂着。
			//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif