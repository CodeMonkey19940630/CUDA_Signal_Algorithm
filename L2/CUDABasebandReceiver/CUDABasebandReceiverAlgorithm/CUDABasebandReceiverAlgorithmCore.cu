#include "CUDABasebandReceiverAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
__device__ __host__ double NoiseVoltage(double Power, double Impedance_Temperature)
{
	return sqrt(Power * Impedance_Temperature);
}

__device__ __host__ double NoisePower(double Band_Width, double Noise_Factor, double Impedance_Temperature)
{
	double Boltzmann_Constant = 1.3806505e-23;//玻尔兹曼常数k
	double Perfect_Receiver_Noise_Power = Boltzmann_Constant*Band_Width;//理想接收机输入噪声功率
	double Holistic_Noise_Power = Noise_Factor * Perfect_Receiver_Noise_Power;//考虑整机噪声系数后的噪声功率
	return Holistic_Noise_Power;
}

__device__ __host__ double ReceiverNoiseVoltage(double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature)
{
	double Band_Width_Temporary = Band_Width * 1.2 * 1.2;
	double Noise_Power = NoisePower(Band_Width_Temporary, Noise_Factor, Impedance_Temperature) * Receiver_Gain;
	double Noise_Voltage = NoiseVoltage(Noise_Power, Impedance);
	return Noise_Voltage;
}

__host__ __device__ int CalculationOfOffset(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	return Axis_Y * Count_Of_Sampling_Point_Of_Monopulse + Axis_Z * Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
}

__host__ __device__ float2 * GetArrayOneDimensionFloat2Data(float2*Initial_Position, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	float2 *One_Dimension_Float2_Data_Position = NULL;
	One_Dimension_Float2_Data_Position = Initial_Position + CalculationOfOffset(Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Axis_Y, Axis_Z);
	return One_Dimension_Float2_Data_Position;
}

__global__ void SensitivityTimeControlEcho(float2 * Radar_Data_Cube_Address, int Total_Size, float Sensitivity_Time_Control_Coefficient, float Pulse_Repetition_Time)
{
	float Time_Step = Pulse_Repetition_Time / (Total_Size*1.0f);
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		float Time_Step_Temporary = (Index + 1.0)*Time_Step;
		float STC_Attenuation = pow(Time_Step_Temporary / Pulse_Repetition_Time, Sensitivity_Time_Control_Coefficient);
		Radar_Data_Cube_Address[Index].x = (Radar_Data_Cube_Address[Index].x * STC_Attenuation);
		Radar_Data_Cube_Address[Index].y = (Radar_Data_Cube_Address[Index].y * STC_Attenuation);
	}
}

__global__ void OverLapSignal(float2 *Total_Received_Signal, float2  *Random_Sigal, int Sampling_Point_Total_Count, float Amtitude)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	for (int Index = Thread_ID; Index < Sampling_Point_Total_Count; Index += Total_Threads)
	{
		Total_Received_Signal[Index].x = Total_Received_Signal[Index].x + Random_Sigal[Index].x*Amtitude;
		Total_Received_Signal[Index].y = Total_Received_Signal[Index].y + Random_Sigal[Index].y*Amtitude;
	}
}

__global__ void LogarithmicAmplifierEcho(float2 * Radar_Data_Cube_Address, int Total_Size, float Logarithmic_Amplifier_Voltage)//U01电压
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	for (unsigned int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		int sgnx;
		if ((Radar_Data_Cube_Address[Index].x) > 0)
		{
			sgnx = 1;

		}
		else
		{
			sgnx = -1;
		}
		float tmpx = fabsf(Radar_Data_Cube_Address[Index].x);
		if (tmpx > Logarithmic_Amplifier_Voltage)
		{
			Radar_Data_Cube_Address[Index].x = (Logarithmic_Amplifier_Voltage + Logarithmic_Amplifier_Voltage*log(tmpx / Logarithmic_Amplifier_Voltage))*sgnx;
		}


		int sgny;
		if ((Radar_Data_Cube_Address[Index].y) > 0)
		{
			sgny = 1;

		}
		else
		{
			sgny = -1;
		}
		float tmpy = fabsf(Radar_Data_Cube_Address[Index].y);
		if (tmpy > Logarithmic_Amplifier_Voltage)
		{
			Radar_Data_Cube_Address[Index].y = (Logarithmic_Amplifier_Voltage + Logarithmic_Amplifier_Voltage*log(tmpy / Logarithmic_Amplifier_Voltage))*sgny;
		}
	}
}

__global__ void AmplifierSaturation(float2 * Radar_Data_Cube_Address, int Total_Size, float Voltage_Saturation, float Voltage_Max, float Saturation_Factor)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	for (unsigned int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		int sgnx;
		if ((Radar_Data_Cube_Address[Index].x) > 0)
		{
			sgnx = 1;
		}
		else
		{
			sgnx = -1;
		}
		float tmpx = fabsf(Radar_Data_Cube_Address[Index].x);
		if (tmpx > Voltage_Saturation)
		{
			Radar_Data_Cube_Address[Index].x = (Voltage_Max - pow(Saturation_Factor, (tmpx - Voltage_Saturation)))*sgnx;
		}


		int sgny;
		if ((Radar_Data_Cube_Address[Index].y) > 0)
		{
			sgny = 1;
		}
		else
		{
			sgny = -1;
		}
		float tmpy = fabsf(Radar_Data_Cube_Address[Index].y);
		if (tmpy > Voltage_Saturation)
		{
			Radar_Data_Cube_Address[Index].y = (Voltage_Max - pow(Saturation_Factor, (tmpy - Voltage_Saturation)))*sgny;
		}
	}
}

__global__ void ADConverter(float2 * Radar_Data_Cube_Address, int Total_Size, float Min_Voltage, float Max_Voltage, float Delta_Voltage)
{
	const int numThreads = blockDim.x * gridDim.x;
	const int threadID = blockIdx.x * blockDim.x + threadIdx.x;
	for (unsigned int Index = threadID; Index < Total_Size; Index += numThreads)
	{
		if (Radar_Data_Cube_Address[Index].x <= Min_Voltage)
		{
			Radar_Data_Cube_Address[Index].x = Min_Voltage;
		}
		else
		{
			if (Radar_Data_Cube_Address[Index].x >= Max_Voltage)
			{
				Radar_Data_Cube_Address[Index].x = Max_Voltage;
			}
			else
			{
				Radar_Data_Cube_Address[Index].x = round((Radar_Data_Cube_Address[Index].x - Min_Voltage) / Delta_Voltage)*Delta_Voltage - Max_Voltage;;
			}
		}

		if (Radar_Data_Cube_Address[Index].y <= Min_Voltage)
		{
			Radar_Data_Cube_Address[Index].y = Min_Voltage;
		}
		else
		{
			if (Radar_Data_Cube_Address[Index].y >= Max_Voltage)
			{
				Radar_Data_Cube_Address[Index].y = Max_Voltage;
			}
			else
			{
				Radar_Data_Cube_Address[Index].y = round((Radar_Data_Cube_Address[Index].y - Min_Voltage) / Delta_Voltage)*Delta_Voltage - Max_Voltage;;
			}
		}
	}
}

void CUDABasebandReceiverAlgorithmCore(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, int BlockSize, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Sensitivity_Time_Control_Coefficient, double Window_Of_Range_Right, double Window_Of_Range_Left, double Logarithmic_Amplifier_Voltage, float Voltage_Saturation, float Max_Voltage, float Saturation_Factor, int ADC_Number, float Pulse_Repetition_Time, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Sensitivity_Time_Control, bool Use_Window_Of_Range, bool Automatic_Gain_Control, bool Logarithmic_Amplifier, bool Amplifier_Saturation, bool Analog_Digital_Conversion)
{
	curandGenerator_t Random_Generator;
	curandRngType_t Random_Type = CURAND_RNG_PSEUDO_MTGP32;
	curandStatus_t Curand_Status= curandCreateGenerator(&Random_Generator, Random_Type);
	double Amptitude = ReceiverNoiseVoltage(Receiver_Gain, Band_Width, Noise_Factor, Impedance, Impedance_Temperature);
	curandStatus_t Curand_Result = curandGenerateNormal(Random_Generator, (float*)Receiver_Noise_Data_Address, Total_Size_Of_Receiver_Noise_Data * 2, 0.0, pow(Amptitude, 2)*Impedance);
	int GridSize = (Count_Of_Sampling_Point_Of_Monopulse + BlockSize - 1) / BlockSize;
	for (int Index_Z = 0; Index_Z < Antenna_Chanel_Count; Index_Z++)
	{
		for (int Index_Y = 0; Index_Y < Count_Of_Pulse_Group; Index_Y++)
		{
			float2 * Radar_Signal_Padding = GetArrayOneDimensionFloat2Data(Radar_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Y, Index_Z);
			if (Sensitivity_Time_Control)
			{
				SensitivityTimeControlEcho << <GridSize , BlockSize>> >(Radar_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Sensitivity_Time_Control_Coefficient, Pulse_Repetition_Time);
				if (Use_Window_Of_Range)
				{
					double Window_Of_Range_Size = 2 * (Window_Of_Range_Right - Window_Of_Range_Left) / 3e8;
					SensitivityTimeControlEcho << <GridSize, BlockSize >> >(Radar_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Sensitivity_Time_Control_Coefficient, Window_Of_Range_Size);
				}
			}
			float2 * Receiver_Thermal_Noise_Signal_Data = GetArrayOneDimensionFloat2Data(Receiver_Noise_Data_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Y, Index_Z);
			OverLapSignal << <GridSize, BlockSize >> >(Radar_Signal_Padding, Receiver_Thermal_Noise_Signal_Data, Count_Of_Sampling_Point_Of_Monopulse, 1.0);
			if (Automatic_Gain_Control)
			{
				//该算法还没有开发。
			}
			if (Logarithmic_Amplifier)
			{
				LogarithmicAmplifierEcho << <GridSize, BlockSize >> >(Radar_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Logarithmic_Amplifier_Voltage);

			}
			if (Amplifier_Saturation)
			{
				AmplifierSaturation << <GridSize, BlockSize >> >(Radar_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Voltage_Saturation, Max_Voltage, Saturation_Factor);

			}
			if (Analog_Digital_Conversion)
			{
				ADConverter << <GridSize, BlockSize >> >(Radar_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, -1.0 * Max_Voltage, 1.0 * Max_Voltage, 2.0* Max_Voltage / pow(2.0, ADC_Number));

			}
		}
	}


}