#include "CUDAInterruptedSamplingRepeaterJammingAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
#define  PI_CUDA 3.141592653589793f
#define PI 3.1415926535
__device__ __host__ double LinearFrequencyModulation(double Frequency_Begin, double Slope_Of_Frequency_Modulation, double Time)
{
	double Delta_Frequency = Slope_Of_Frequency_Modulation * Time;
	double Frequency_Slope = Frequency_Begin + Delta_Frequency;
	return Frequency_Slope;
}

__device__ __host__ double NonlinearityFrequencyModulationTan(double Frequency_Begin, double Band_Width, double Pulse_Width, double Time)
{
	double Alpha = 2.5;
	double Beta = atan(Alpha);
	double Delta_Frequency = Band_Width *tan(2.0 * Beta * (Time) / Pulse_Width) / (2.0 * tan(Beta));
	double Frequency_Slope = Frequency_Begin + Delta_Frequency;
	return Frequency_Slope;
}

__device__ __host__ double NonlinearityFrequencyModulationPolynomial(double Frequency_Begin, double Band_Width, double Pulse_Width, double Time)
{
	//基于多项式的非线性调频
	double Polynomial_Parameter[7] = { -0.1145, 0.0396, -0.0202, 0.0118, 0.0082, 0.0055, -0.0040 };
	double Temporary = 0;
	for (int i = 0; i < 7; i++)
	{
		Temporary = Temporary + Polynomial_Parameter[i] * sinf(2 * PI_CUDA*(i + 1)*Time / Pulse_Width);//sinf怀疑是否是cuda中的函数
	}
	double Delta_Frequency = Band_Width * (Time / Pulse_Width + Temporary);
	double Frequency_Slope = Frequency_Begin + Delta_Frequency;
	return Frequency_Slope;
}

__device__ __host__ double TwoPhaseBarkerOne()
{
	double Phase = 0.0;
	return Phase;
}
__device__ __host__ double TwoPhaseBarkerTwo(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 2.0);
	double Phase;
	if (Barker_Value == 1)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double ThreePhaseBarker(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 3.0);
	double Phase;
	if (Barker_Value == 2)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double FourPhaseBarkerOne(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 4.0);
	double Phase;
	if (Barker_Value == 2)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double FourPhaseBarkerTwo(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 4.0);
	double Phase;
	if (Barker_Value == 3)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double FivePhaseBarker(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 5.0);
	double Phase;
	if (Barker_Value == 3)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double SevenPhaseBarker(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 7.0);
	double Phase;
	if (Barker_Value == 3 || Barker_Value == 4 || Barker_Value == 6)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double ElevenPhaseBarker(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 11.0);
	double Phase;
	if (Barker_Value == 3 || Barker_Value == 4 || Barker_Value == 5 || Barker_Value ==7 || Barker_Value == 8 || Barker_Value == 10)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double ThirteenPhaseBarker(double Pulse_Width, double Time)
{
	int Barker_Value = Time / (Pulse_Width / 13.0);
	double Phase;
	if ((Barker_Value == 5) || (Barker_Value == 6) || (Barker_Value == 9) || (Barker_Value == 11))
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double PhaseBarkerMN(double Pulse_Width, double Time, int M, int N, int Index_First, int Index_Second)
{
	int Barker2One[2] = { 1, 1 };
	int Barker2Two[2] = { 1, -1 };
	int Barker3[3] = { 1, 1, -1 };
	int Barker4One[4] = { 1, 1, -1, 1 };
	int Barker4Two[4] = { 1, 1, 1, -1 };
	int Barker5[5] = { 1, 1, 1, -1, 1 };
	int Barker7[7] = { 1, 1, 1, -1, -1, 1, -1 };
	int Barker11[11] = { 1, 1, 1, -1, -1, -1, 1, -1, -1, 1, -1 };
	int Barker13[13] = { 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1 };

	std::vector < std::vector<int> > Total_Barker_Code;

	for (int i = 0; i < 9; i++)
	{
		if (i == 0)
		{
			std::vector<int> BarkerCode(Barker2One, Barker2One + sizeof(Barker2One) / sizeof(Barker2One[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 1)
		{
			std::vector<int> BarkerCode(Barker2Two, Barker2Two + sizeof(Barker2Two) / sizeof(Barker2Two[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 2)
		{
			std::vector<int> BarkerCode(Barker3, Barker3 + sizeof(Barker3) / sizeof(Barker3[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 3)
		{
			std::vector<int> BarkerCode(Barker4One, Barker4One + sizeof(Barker4One) / sizeof(Barker4One[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 4)
		{
			std::vector<int> BarkerCode(Barker4Two, Barker4Two + sizeof(Barker4Two) / sizeof(Barker4Two[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 5)
		{
			std::vector<int> BarkerCode(Barker5, Barker5 + sizeof(Barker5) / sizeof(Barker5[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 6)
		{
			std::vector<int> BarkerCode(Barker7, Barker7 + sizeof(Barker7) / sizeof(Barker7[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 7)
		{
			std::vector<int> BarkerCode(Barker11, Barker11 + sizeof(Barker11) / sizeof(Barker11[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}
		else if (i == 8)
		{
			std::vector<int> BarkerCode(Barker13, Barker13 + sizeof(Barker13) / sizeof(Barker13[0]));
			Total_Barker_Code.push_back(BarkerCode);
		}

	}
	std::vector<int> Kornecker_Product;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int Scalar_Product = Total_Barker_Code[Index_First][i] * Total_Barker_Code[Index_Second][j];
			Kornecker_Product.push_back(Scalar_Product);
		}
	}
	int Barker_Value = Time / (Pulse_Width / Kornecker_Product.size());
	double Phase;
	if (Kornecker_Product[Barker_Value] == -1)
	{
		Phase = PI_CUDA;
	}
	else
	{
		Phase = 0;
	}
	return Phase;
}

__device__ __host__ double PhaseFrank(int M, double Pulse_Width, double Time)
{
	int N = M * M;

	double Phase;
	int Row = unsigned int(Time / (Pulse_Width / N)) / M + 1;
	int Column = unsigned int(Time / (Pulse_Width / N)) % M + 1;
	Phase = 2 * PI_CUDA / M * (Row - 1) * (Column - 1);
	return Phase;
}

__device__ __host__ double PhaseLKPOne(int M, double Pulse_Width, double Time)
{
	int N = M * M;

	double Phase;
	int Row = unsigned int(Time / (Pulse_Width / N)) / M + 1;
	int Column = unsigned int(Time / (Pulse_Width / N)) % M + 1;
	Phase = -PI_CUDA / (1.0*M)*(M - 2 * Row + 1.0)*(M*(Column - 1.0) + Column - 1.0);
	return Phase;
}

__device__ __host__ double PhaseLKPTwo(int M, double Pulse_Width, double Time)
{
	int N = M * M;
	double Phase;
	int Row = unsigned int(Time / (Pulse_Width / N)) / M + 1;
	int Column = unsigned int(Time / (Pulse_Width / N)) % M + 1;
	Phase = -PI_CUDA / 2.0 / (1.0*M) * (2.0* Row - 1.0 - M)*(2.0* Column - 1.0 - M);
	return Phase;
}

__device__ __host__ double PhaseLKPThree(int N, double Pulse_Width, double Time)
{
	double Phase;
	int Chip_Number = Time / (Pulse_Width / N);
	Phase = PI_CUDA / N*Chip_Number*Chip_Number;
	return Phase;
}

__device__ __host__ double PhaseLKPFour(int N, double Pulse_Width, double Time)
{
	double Phase;
	unsigned int Chip_Number = Time / (Pulse_Width / N);
	Phase = PI_CUDA / N*Chip_Number*Chip_Number - PI_CUDA*Chip_Number;
	return Phase;
}

__device__ __host__ double GetPulse(double PRT, int Pulse_ID)
{
	return PRT * Pulse_ID;
}

__device__ __host__ float GetPulseBasisOfPRTList(float * Pulse_Transmit_Time_List, int Pulse_ID)
{
	float Pulse_Time = Pulse_Transmit_Time_List[Pulse_ID];
	return Pulse_Time;
}

__device__ __host__ double GetDelta(double Current_Distance_Between_Target_and_Radar, bool Is_Two_Way)
{
	if (Is_Two_Way)
	{
		return Current_Distance_Between_Target_and_Radar / 299792458.0 * 2.0;
	}
	else
	{
		return Current_Distance_Between_Target_and_Radar / 299792458.0;
	}
}

__device__ __host__ int GetPulseSN(float * Pulse_Transmit_Time_List, float * Pulse_Transmit_Interval_Time_List, int Pulse_Transmit_Interval_Time_List_Size, double Delta, int Pulse_Index)
{
	double  CPI = 0;
	for (int Index = 0; Index < Pulse_Transmit_Interval_Time_List_Size; Index++)
	{
		CPI += Pulse_Transmit_Interval_Time_List[Index];
	}
	Delta = Delta + Pulse_Transmit_Time_List[Pulse_Index];
	if (Delta >= CPI)
	{
		int Size = Pulse_Transmit_Interval_Time_List_Size;
		return Size;
	}
	else
	{
		int Pulse_Delay = 0;
		while (1)
		{
			if ((Pulse_Transmit_Time_List[Pulse_Index + Pulse_Delay] + Pulse_Transmit_Interval_Time_List[Pulse_Index + Pulse_Delay] > Delta) && (Pulse_Transmit_Time_List[Pulse_Index + Pulse_Delay] < Delta))
			{
				break;
			}
			Pulse_Delay++;
		}
		return Pulse_Delay;
	}
}

__device__ __host__ double GetPhaseZero(double Medium_Frequency, double Current_Time)
{
	double Tmporary = Medium_Frequency*Current_Time - (unsigned int)(Medium_Frequency*Current_Time);
	double Phase_Zero = 2.0 * PI*Tmporary;
	return Phase_Zero;
}

__device__ __host__ double GetTransmitPower(double Transmit_Power, double Antenna_Transmit_Gain, double Antenna_Receive_Gain, double Wave_Length, double RCS, double Distance)
{
	double Pr;
	Pr = Transmit_Power*Antenna_Transmit_Gain*Antenna_Receive_Gain*Wave_Length*Wave_Length*RCS / (pow((4 * PI), 3.0) * pow(Distance, 4.0));
	return Pr;
}

__device__ __host__ double GetPowerSource(double Power, double Impedance)
{
	return sqrt(Power * Impedance);
}

__device__ __host__ double GetDopplerFrequency(double Target_Velocity_Relative_to_Radar, double Wave_Length)
{
	return 2.0 * Target_Velocity_Relative_to_Radar / Wave_Length;
}
__device__ __host__ int GetStartIndex(float * Pulse_Transmit_Interval_Time_List, double Delta, int Count_Of_Pulse_Group, int Pulse_Index, double Fs)
{
	unsigned int StartIndex;
	double Delta_temporary = Delta;
	for (int Index = 0; Index < Pulse_Index; Index++)
	{
		Delta_temporary = Delta_temporary - Pulse_Transmit_Interval_Time_List[Count_Of_Pulse_Group + Pulse_Index - Index];
	}
	StartIndex = ceil(Delta * Fs);
	return StartIndex;
}

__host__ __device__ int CalculationOfOffset(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	return Axis_Y * Count_Of_Sampling_Point_Of_Monopulse + Axis_Z * Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
}

__device__ __host__ float * GetArrayOneDimensionFloatData(float *Initial_Position, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	float * One_Dimension_Float_Data_Position = NULL;
	One_Dimension_Float_Data_Position  = Initial_Position + CalculationOfOffset(Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Axis_Y, Axis_Z);
	return One_Dimension_Float_Data_Position;
}
__host__ __device__ float2 * GetArrayOneDimensionFloat2Data(float2*Initial_Position, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	float2 *One_Dimension_Float2_Data_Position = NULL;
	One_Dimension_Float2_Data_Position = Initial_Position + CalculationOfOffset(Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Axis_Y, Axis_Z);
	return One_Dimension_Float2_Data_Position;
}

__global__ void GenerateOneEchoReal(int Type, float Phase, float Frequency_Begin, float Frequency_End, float Pulse_Width, int Overlap_Position, int End_Position, float Amplitude, int Total_Size, float* Real_Signal)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	float Band_Width = Frequency_End - Frequency_Begin;
	int Pulse_Size = End_Position - Overlap_Position;
	float TimeStep = Pulse_Width / (Pulse_Size*1.0);
	float FreqSlope = Band_Width / Pulse_Width / 2.0;
	float PI_Double = 2.0 * PI_CUDA;
	float PhaseRT = 0.0;
	float FreqRT = (Frequency_End + Frequency_Begin) / 2.0;
	for (int Index = Thread_ID; Index < Pulse_Size; Index += Total_Threads)
	{
		int Array_Index = Index + Overlap_Position;
		if ((Array_Index) < Total_Size)
		{

			float TimeRT = TimeStep*(Index);		
			switch (Type)
			{
				case 0:
				{
					FreqRT = LinearFrequencyModulation(Frequency_Begin, FreqSlope, TimeRT);
					break;
				}
				case 1:
				{
					FreqRT = NonlinearityFrequencyModulationTan(Frequency_Begin, Band_Width, Pulse_Width, TimeRT);
					break;
				}
				case 2:
				{
					FreqRT = NonlinearityFrequencyModulationPolynomial(Frequency_Begin, Band_Width, Pulse_Width, TimeRT);
					break;
				}
				case 3:
				{
					PhaseRT = TwoPhaseBarkerOne();
					break;
				}
				case 4:
				{
					PhaseRT = TwoPhaseBarkerTwo(Pulse_Width, TimeRT);
					break;
				}
				case 5:
				{
					PhaseRT = ThreePhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 6:
				{
					PhaseRT = FourPhaseBarkerOne(Pulse_Width, TimeRT);
					break;
				}
				case 7:
				{
					PhaseRT = FourPhaseBarkerTwo(Pulse_Width, TimeRT);
					break;
				}
				case 8:
				{
					PhaseRT = FivePhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 9:
				{
					PhaseRT = SevenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 10:
				{
					PhaseRT = ElevenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 11:
				{
					PhaseRT = ThirteenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 12:
				{
					PhaseRT = PhaseBarkerMN(Pulse_Width, TimeRT, 4, 5, 4, 5);
					break;
				}
				case 13:
				{
					FreqRT = LinearFrequencyModulation(Frequency_Begin, FreqSlope, TimeRT);
					PhaseRT = ElevenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 14:
				{
					PhaseRT = PhaseFrank(8, Pulse_Width, TimeRT);
					break;
				}
				case 15:
				{
					PhaseRT = PhaseLKPOne(8, Pulse_Width, TimeRT);
					break;
				}
				case 16:
				{
					PhaseRT = PhaseLKPTwo(8, Pulse_Width, TimeRT);
					break;
				}
				case 17:
				{
					PhaseRT = PhaseLKPThree(64, Pulse_Width, TimeRT);
					break;
				}
				case 18:
				{
					PhaseRT = PhaseLKPFour(64, Pulse_Width, TimeRT);
					break;
				}
				default:
				{
					FreqRT = (Frequency_End + Frequency_Begin) / 2.0;
					PhaseRT = 0.0;
					break;
				}
			}
			float Echo_Signal = cos(PI_Double * FreqRT * TimeRT + Phase + PhaseRT) * Amplitude;
			Real_Signal[Array_Index] += Echo_Signal;
		}
	}
}

__global__ void GenerateOneEchoComplex(int Type, float Phase, float Frequency_Begin, float Frequency_End, float Pulse_Width, int Overlap_Position, int End_Position, float Amplitude, int Total_Size, float2* Complex_Data)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	float Band_Width = Frequency_End - Frequency_Begin;
	int Pulse_Size = End_Position - Overlap_Position;
	float TimeStep = Pulse_Width / (Pulse_Size*1.0);
	float FreqSlope = Band_Width / Pulse_Width / 2.0;
	float PI_Double = 2.0 * PI_CUDA;
	float PhaseRT = 0.0;
	float FreqRT = (Frequency_End + Frequency_Begin) / 2.0;
	for (int Index = Thread_ID; Index < Pulse_Size; Index += Total_Threads)
	{
		int Array_Index = Index + Overlap_Position;
		if ((Array_Index) < Total_Size)
		{

			float TimeRT = TimeStep*(Index);
			switch (Type)
			{
				case 0:
				{
					FreqRT = LinearFrequencyModulation(Frequency_Begin, FreqSlope, TimeRT);
					break;
				}
				case 1:
				{
					FreqRT = NonlinearityFrequencyModulationTan(Frequency_Begin, Band_Width, Pulse_Width, TimeRT);
					break;
				}
				case 2:
				{
					FreqRT = NonlinearityFrequencyModulationPolynomial(Frequency_Begin, Band_Width, Pulse_Width, TimeRT);
					break;
				}
				case 3:
				{
					PhaseRT = TwoPhaseBarkerOne();
					break;
				}
				case 4:
				{
					PhaseRT = TwoPhaseBarkerTwo(Pulse_Width, TimeRT);
					break;
				}
				case 5:
				{
					PhaseRT = ThreePhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 6:
				{
					PhaseRT = FourPhaseBarkerOne(Pulse_Width, TimeRT);
					break;
				}
				case 7:
				{
					PhaseRT = FourPhaseBarkerTwo(Pulse_Width, TimeRT);
					break;
				}
				case 8:
				{
					PhaseRT = FivePhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 9:
				{
					PhaseRT = SevenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 10:
				{
					PhaseRT = ElevenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 11:
				{
					PhaseRT = ThirteenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 12:
				{
					PhaseRT = PhaseBarkerMN(Pulse_Width, TimeRT, 4, 5, 4, 5);
					break;
				}
				case 13:
				{
					FreqRT = LinearFrequencyModulation(Frequency_Begin, FreqSlope, TimeRT);
					PhaseRT = ElevenPhaseBarker(Pulse_Width, TimeRT);
					break;
				}
				case 14:
				{
					PhaseRT = PhaseFrank(8, Pulse_Width, TimeRT);
					break;
				}
				case 15:
				{
					PhaseRT = PhaseLKPOne(8, Pulse_Width, TimeRT);
					break;
				}
				case 16:
				{
					PhaseRT = PhaseLKPTwo(8, Pulse_Width, TimeRT);
					break;
				}
				case 17:
				{
					PhaseRT = PhaseLKPThree(64, Pulse_Width, TimeRT);
					break;
				}
				case 18:
				{
					PhaseRT = PhaseLKPFour(64, Pulse_Width, TimeRT);
					break;
				}
			}
			float Echo_Signal_X = cos(PI_Double*FreqRT*(TimeRT - Pulse_Width / 2) + Phase + PhaseRT)*Amplitude;
			float Echo_Signal_Y = sin(PI_Double*FreqRT*(TimeRT - Pulse_Width / 2) + Phase + PhaseRT)*Amplitude;
			Complex_Data[Array_Index].x += Echo_Signal_X;
			Complex_Data[Array_Index].y += Echo_Signal_Y;
		}
	}
}

__global__ void GenerateOneInterruptedSamplingRepeaterJammingReal(double Sampling_Time_Period, double Duty_Factor, float Pulse_Width, float *Original_Data, float *Jamming_Data, int Overlap_Position, int Pulse_Size, int Total_Size, float Amplitude)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int Sampling_Point_Count_In_Period;//采样周期点数
	int Sampling_Duration_Count;//采样时长点数
	int Interval_Duration_Count;//间歇时长点数
	Sampling_Point_Count_In_Period = Pulse_Size / Pulse_Width * Sampling_Time_Period;
	Sampling_Duration_Count = int(Sampling_Point_Count_In_Period*Duty_Factor);
	Interval_Duration_Count = Sampling_Point_Count_In_Period - Sampling_Duration_Count;
	//间歇采样得到干扰信号
	for (int Index = 0; Index < Pulse_Size; Index++)
	{
		int Data_Index = Index + Overlap_Position;
		if ((Data_Index) < Total_Size)
		{
			if ((Index - (Index / Sampling_Point_Count_In_Period) * Sampling_Point_Count_In_Period) > Interval_Duration_Count)
			{
				Jamming_Data[Data_Index] = 0.0;
			}
		}
	}

	//回波信号与干扰信号叠加
	for (int Index = Thread_ID; Index < Pulse_Size; Index += Total_Threads)
	{
		int Data_Index = Index + Overlap_Position;
		if ((Data_Index) < Total_Size)
		{
			Original_Data[Data_Index] += Amplitude * Jamming_Data[Data_Index];
		}
	}
}

__global__ void GenerateOneInterruptedSamplingRepeaterJammingComplex(double Sampling_Time_Period, double Duty_Factor, float Pulse_Width, float2 *Original_Data, float2 *Jamming_Data, int Overlap_Position, int Pulse_Size, int Total_Size, float Amplitude)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int Sampling_Point_Count_In_Period;//采样周期点数
	int Sampling_Duration_Count;//采样时长点数
	int Interval_Duration_Count;//间歇时长点数
	Sampling_Point_Count_In_Period = Pulse_Size / Pulse_Width * Sampling_Time_Period;
	Sampling_Duration_Count = int(Sampling_Point_Count_In_Period*Duty_Factor);
	Interval_Duration_Count = Sampling_Point_Count_In_Period - Sampling_Duration_Count;
	//间歇采样得到干扰信号
	for (int Index = 0; Index < Pulse_Size; Index++)
	{
		int Data_Index = Index + Overlap_Position;
		if ((Data_Index) < Total_Size)
		{
			if ((Index - (Index / Sampling_Point_Count_In_Period) * Sampling_Point_Count_In_Period) > Interval_Duration_Count)
			{
				Jamming_Data[Data_Index].x = 0.0;
				Jamming_Data[Data_Index].y = 0.0;
			}
		}
	}

	//回波信号与干扰信号叠加
	for (int Index = Thread_ID; Index < Pulse_Size; Index += Total_Threads)
	{
		int Data_Index = Index + Overlap_Position;
		if ((Data_Index) < Total_Size)
		{
			Original_Data[Data_Index].x += Amplitude * Jamming_Data[Data_Index].x;
			Original_Data[Data_Index].y += Amplitude * Jamming_Data[Data_Index].y;
		}
	}
}

void CUDAInterruptedSamplingRepeaterJammingAlgorithmCore(float * Radar_Float_Data_Cube_Address, float2 * Radar_Float2_Data_Cube_Address, int BlockSize, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, double Distance_Between_Target_and_Radar, double RCS, double Target_Velocity_Relative_to_Radar, double Receiver_Gain, double Transmit_Power, double Antenna_Transmit_Gain, double Antenna_Receive_Gain, double Wave_Length, double Impedance, double Signal_Transmit_Time, double Duty_Factor, double Jamming_Amplitude, double Sampling_Transpond_Period, float Sampling_Frequency_Of_Medium_Frequency, float Baseband_Sampling_Frequency, float Medium_Frequency, float Pulse_Width, float Band_Width, float PRT, float *PRT_List, int PRT_List_Size, float * Pulse_Transmit_Interval_Time_List, int Pulse_Transmit_Interval_Time_List_Size, bool Use_Only_Baseband, int Type)
{
	int GridSize = (Baseband_Sampling_Frequency * Pulse_Width + BlockSize - 1) / BlockSize;
	for (int Index = 0; Index < Count_Of_Pulse_Group; Index++)
	{
		double Current_Distance_Between_Target_and_Radar = 0.0;//目标当前距离
		float Pulse = 0.0;
		if (PRT_List_Size <= 0)
		{
			Pulse = GetPulse(PRT, Index);
		}
		else
		{
			Pulse = GetPulseBasisOfPRTList(PRT_List, Index);
		}
		Current_Distance_Between_Target_and_Radar = Distance_Between_Target_and_Radar + Target_Velocity_Relative_to_Radar * Pulse;
		double Delta = GetDelta(Current_Distance_Between_Target_and_Radar, true);//为什么不直接在GetDelta函数中写死为true状态？
		int PulseSN = GetPulseSN(PRT_List, Pulse_Transmit_Interval_Time_List, Pulse_Transmit_Interval_Time_List_Size, Delta, PRT);
		if ((PulseSN + Index) >= Count_Of_Pulse_Group)
		{
			continue;
		}
		else
		{
			double Current_Time = Signal_Transmit_Time + Delta;
			double Pulse_Zero = GetPhaseZero(3.0e8 / Wave_Length, Current_Time);
			double Receiver_Power = GetTransmitPower(Transmit_Power, Antenna_Transmit_Gain, Antenna_Receive_Gain, Wave_Length, RCS, Current_Distance_Between_Target_and_Radar);
			double Power_Source_Value = GetPowerSource(Receiver_Power, Impedance);
			double Doppler_Frequency = GetDopplerFrequency(Target_Velocity_Relative_to_Radar, Wave_Length);
			if (Use_Only_Baseband)
			{
				int Overlap_Position = GetStartIndex(Pulse_Transmit_Interval_Time_List, Delta, Index, PulseSN, Sampling_Frequency_Of_Medium_Frequency);
				int End_Position = Overlap_Position + Sampling_Frequency_Of_Medium_Frequency * Pulse_Width;
				int Pulse_Size = End_Position - Overlap_Position;
				float Frequency_Begin = Medium_Frequency - Band_Width / 2;
				float Frequency_End = Medium_Frequency + Band_Width / 2;
				float * Radar_Signal_Padding = GetArrayOneDimensionFloatData(Radar_Float_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index + PulseSN, 0);
				float *DRFM_Float_Data = NULL;
				checkCudaErrors(cudaMalloc((void **)&DRFM_Float_Data, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float)));
				checkCudaErrors(cudaMemset(DRFM_Float_Data, 0, Count_Of_Sampling_Point_Of_Monopulse *  sizeof(float)));
				GenerateOneEchoReal << <GridSize, BlockSize >> >(Type, Pulse_Zero, Frequency_Begin, Frequency_End, Pulse_Width, Overlap_Position, End_Position, Power_Source_Value, Count_Of_Sampling_Point_Of_Monopulse, DRFM_Float_Data);
				GenerateOneInterruptedSamplingRepeaterJammingReal << <GridSize, BlockSize >> >(Sampling_Transpond_Period, Duty_Factor, Pulse_Width, Radar_Signal_Padding, DRFM_Float_Data, Overlap_Position, Pulse_Size, Count_Of_Sampling_Point_Of_Monopulse, Jamming_Amplitude);
				checkCudaErrors(cudaFree(DRFM_Float_Data));
			}
			else
			{
				int Overlap_Position = Baseband_Sampling_Frequency * Delta;
				int End_Position = Overlap_Position + Sampling_Frequency_Of_Medium_Frequency * Pulse_Width;
				int Pulse_Size = End_Position - Overlap_Position;
				float Frequency_Begin = - Band_Width / 2;
				float Frequency_End = Band_Width / 2;
				float2 * Radar_Signal_Padding = GetArrayOneDimensionFloat2Data(Radar_Float2_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index, 0);
				float2 *DRFM_Float2_Data = NULL;
				checkCudaErrors(cudaMalloc((void **)&DRFM_Float2_Data, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float2)));
				checkCudaErrors(cudaMemset(DRFM_Float2_Data, 0, Count_Of_Sampling_Point_Of_Monopulse *  sizeof(float2)));
				GenerateOneEchoComplex << <GridSize, BlockSize >> >(Type, Pulse_Zero, Frequency_Begin, Frequency_End, Pulse_Width, Overlap_Position, End_Position, Power_Source_Value, Count_Of_Sampling_Point_Of_Monopulse, DRFM_Float2_Data);
				GenerateOneInterruptedSamplingRepeaterJammingComplex << <GridSize, BlockSize >> >(Sampling_Transpond_Period, Duty_Factor, Pulse_Width, Radar_Signal_Padding, DRFM_Float2_Data, Overlap_Position, Pulse_Size, Count_Of_Sampling_Point_Of_Monopulse, Jamming_Amplitude);
				checkCudaErrors(cudaFree(DRFM_Float2_Data));
			}
		}
	}
}