#include "CUDACFARDetectorTwoDimensionAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"

__host__ __device__ int CalculationOfOffset(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Z)
{
	return Axis_Z * Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
}

__host__ __device__ float2 * GetArrayTwoDimensionFloat2Data(float2*Initial_Position, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Z)
{
	float2 *Two_Dimension_Float2_Data_Position = NULL;
	Two_Dimension_Float2_Data_Position = Initial_Position + CalculationOfOffset(Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Axis_Z);
	return Two_Dimension_Float2_Data_Position;
}

__global__ void CACFAR2D(float * CFAR_Reference, float * Signal_Absolute, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	const  int Total_Size = Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;

	int Total_Window_Size = (2 * (WindowCell_F + GuardCell_F) + 1) * (2 * (WindowCell_S + GuardCell_S) + 1);
	int Guard_Window_Size = (2 * GuardCell_F + 1)*(2 * GuardCell_S + 1);
	int Reference_Window_Size = Total_Window_Size - Guard_Window_Size;

	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		CFAR_Reference[Index] = 0.0f;
		int Axis_Y = Index / Count_Of_Sampling_Point_Of_Monopulse;
		int Axis_X = Index - Axis_Y * Count_Of_Sampling_Point_Of_Monopulse;

		//新版本遍历方式
		if ((Axis_X < WindowCell_F + GuardCell_F || Axis_X >= Count_Of_Sampling_Point_Of_Monopulse - 1 - (WindowCell_F + GuardCell_F - 1)) || (Axis_Y < WindowCell_S + GuardCell_S || Axis_Y >= Count_Of_Pulse_Group - 1 - (WindowCell_S + GuardCell_S - 1)))
		{
			continue;
		}
		else
		{
			//沿着距离方向遍历
			float Sum = 0.0;
			for (int X = Axis_X - GuardCell_F - WindowCell_F; X <= Axis_X + GuardCell_F + WindowCell_F; X++)
			{
				for (int Y = Axis_Y - GuardCell_S - WindowCell_S; Y <= Axis_Y + GuardCell_S + WindowCell_S; Y++)
				{
					int Index = X + Y * Count_Of_Sampling_Point_Of_Monopulse;
					if ((X >= Axis_X - GuardCell_F && X <= Axis_X + GuardCell_F) && (Y >= Axis_Y - GuardCell_S && Y <= Axis_Y + GuardCell_S))
					{
						continue;
					}

					Sum += Signal_Absolute[Index];

				}
			}

			CFAR_Reference[Index] = Sum / Reference_Window_Size;

		}
	}
	__syncthreads();
}

__global__ void SOCACFAR2D(float *CFAR_Reference, float *Signal_Absolute, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	const  int Total_Size = Count_Of_Sampling_Point_Of_Monopulse*Count_Of_Pulse_Group;

	int Total_Window_Size = (2 * (WindowCell_F + GuardCell_F) + 1) * (2 * (WindowCell_S + GuardCell_S) + 1);
	int Guard_Window_Size = (2 * GuardCell_F + 1)*(2 * GuardCell_S + 1);
	int Reference_Window_Size = Total_Window_Size - Guard_Window_Size;

	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		CFAR_Reference[Index] = 0.0f;
		int Axis_Y = Index / Count_Of_Sampling_Point_Of_Monopulse;
		int Axis_X = Index - Axis_Y*Count_Of_Sampling_Point_Of_Monopulse;

		//新版本遍历方式
		if ((Axis_X < WindowCell_F + GuardCell_F || Axis_X >= Count_Of_Sampling_Point_Of_Monopulse - 1 - (WindowCell_F + GuardCell_F - 1)) ||
			(Axis_Y < WindowCell_S + GuardCell_S || Axis_Y >= Count_Of_Pulse_Group - 1 - (WindowCell_S + GuardCell_S - 1)))
		{
			continue;
		}
		else
		{
			//沿着距离方向遍历
			float Left_Sum = 0.0;
			float Right_Sum = 0.0;
			for (int X = Axis_X - GuardCell_F - WindowCell_F; X <= Axis_X + GuardCell_F + WindowCell_F; X++)
			{
				for (int Y = Axis_Y - GuardCell_S - WindowCell_S; Y <= Axis_Y + GuardCell_S + WindowCell_S; Y++)
				{
					int Index = X + Y * Count_Of_Sampling_Point_Of_Monopulse;
					if ((X >= Axis_X - GuardCell_F && X <= Axis_X + GuardCell_F) && (Y >= Axis_Y - GuardCell_S && Y <= Axis_Y + GuardCell_S))
					{
						continue;
					}

					if (X < Axis_X - GuardCell_F)
					{
						Left_Sum += Signal_Absolute[Index];
					}

					if (X >= Axis_X + GuardCell_F + 1)
					{
						Right_Sum += Signal_Absolute[Index];
					}

				}
			}

			if (Left_Sum < Right_Sum)
			{
				CFAR_Reference[Index] = Left_Sum * 1.0 / (Reference_Window_Size / 2.0);
			}
			else
			{
				CFAR_Reference[Index] = Right_Sum * 1.0 / (Reference_Window_Size / 2.0);
			}

		}
	}
	__syncthreads();
}

__global__ void GOCACFAR2D(float *CFAR_Reference, float *Signal_Absolute, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	const  int Total_Size = Count_Of_Sampling_Point_Of_Monopulse*Count_Of_Pulse_Group;

	int Total_Window_Size = (2 * (WindowCell_F + GuardCell_F) + 1) * (2 * (WindowCell_S + GuardCell_S) + 1);
	int Guard_Window_Size = (2 * GuardCell_F + 1)*(2 * GuardCell_S + 1);
	int Reference_Window_Size = Total_Window_Size - Guard_Window_Size;

	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		CFAR_Reference[Index] = 0.0f;
		int Axis_Y = Index / Count_Of_Sampling_Point_Of_Monopulse;
		int Axis_X = Index - Axis_Y*Count_Of_Sampling_Point_Of_Monopulse;

		//新版本遍历方式
		if ((Axis_X < WindowCell_F + GuardCell_F || Axis_X >= Count_Of_Sampling_Point_Of_Monopulse - 1 - (WindowCell_F + GuardCell_F - 1)) ||
			(Axis_Y < WindowCell_S + GuardCell_S || Axis_Y >= Count_Of_Pulse_Group - 1 - (WindowCell_S + GuardCell_S - 1)))
		{
			continue;
		}
		else
		{
			//沿着距离方向遍历
			float Left_Sum = 0.0;
			float Right_Sum = 0.0;
			for (int X = Axis_X - GuardCell_F - WindowCell_F; X <= Axis_X + GuardCell_F + WindowCell_F; X++)
			{
				for (int Y = Axis_Y - GuardCell_S - WindowCell_S; Y <= Axis_Y + GuardCell_S + WindowCell_S; Y++)
				{
					int Index = X + Y*Count_Of_Sampling_Point_Of_Monopulse;
					if ((X >= Axis_X - GuardCell_F && X <= Axis_X + GuardCell_F) && (Y >= Axis_Y - GuardCell_S && Y <= Axis_Y + GuardCell_S))
					{
						continue;
					}

					if (X < Axis_X - GuardCell_F)
					{
						Left_Sum += Signal_Absolute[Index];
					}

					if (X >= Axis_X + GuardCell_F + 1)
					{
						Right_Sum += Signal_Absolute[Index];
					}

				}
			}

			if (Left_Sum < Right_Sum)
			{
				CFAR_Reference[Index] = Right_Sum * 1.0 / (Reference_Window_Size / 2.0);
			}
			else
			{
				CFAR_Reference[Index] = Left_Sum * 1.0 / (Reference_Window_Size / 2.0);
			}

		}
	}
	__syncthreads();
}

__global__ void DetectByCFAR2D(bool *Dectect_Result, float *Signal_Absolute, float *CFAR_Reference, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S, float Min_Detect_Factor, float Min_Detect_Threshold)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	const  int Total_Size = Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		Dectect_Result[Index] = false;

		int Axis_Y = Index / Count_Of_Sampling_Point_Of_Monopulse;
		int Axis_X = Index - Axis_Y*Count_Of_Sampling_Point_Of_Monopulse;

		if ((Axis_X < WindowCell_F + GuardCell_F || Axis_X >= Count_Of_Sampling_Point_Of_Monopulse - 1 - (WindowCell_F + GuardCell_F - 1)) || (Axis_Y < WindowCell_S + GuardCell_S || Axis_Y >= Count_Of_Pulse_Group - 1 - (WindowCell_S + GuardCell_S - 1)))
		{
			continue;
		}
		Dectect_Result[Index] = (Signal_Absolute[Index] >(CFAR_Reference[Index] * Min_Detect_Factor)) && (Signal_Absolute[Index] > Min_Detect_Threshold);
	}
	__syncthreads();
}

void CUDACFARDetectorTwoDimensionAlgorithmCore(float2 * Radar_Data_Cube_Address, float * CFAR_Absolute_Detected_Data, float * CFAR_Reference, bool * CFAR_Result, int BlockSize, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S, double Min_Detect_Factor, double Min_Detect_Threshold, int CFAR_Method_Select)
{
	unsigned int GridSize = (Count_Of_Sampling_Point_Of_Monopulse + BlockSize - 1) / BlockSize;
	for (int Index_Z = 0; Index_Z < Antenna_Chanel_Count; Index_Z++)
	{
		float2 * Radar_Signal_Padding = GetArrayTwoDimensionFloat2Data(Radar_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Z);
		int Offset = Index_Z * Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
		int Count_Of_Sampling_Point_Of_CPI = Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
		float * CFAR_Signal_Padding = CFAR_Absolute_Detected_Data + Offset;
		float *CFAR_Reference_Padding = CFAR_Reference + Offset;
		bool *Detect_Result = CFAR_Result + Offset;
		CUDAMathematicsFoundationArithmeticNamespace::ComplexArrayAbsolute << <GridSize, BlockSize >> >(CFAR_Signal_Padding, Radar_Signal_Padding, Count_Of_Sampling_Point_Of_CPI);
		switch (CFAR_Method_Select)
		{
		case 0:
		{
			CACFAR2D << <GridSize, BlockSize >> >(CFAR_Reference_Padding, CFAR_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, GuardCell_F, WindowCell_F, GuardCell_S, WindowCell_S);
			break;
		}
		case 1:
		{
			SOCACFAR2D << <GridSize, BlockSize >> >(CFAR_Reference_Padding, CFAR_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, GuardCell_F, WindowCell_F, GuardCell_S, WindowCell_S);
			break;
		}
		case 2:
		{
			GOCACFAR2D << <GridSize, BlockSize >> >(CFAR_Reference_Padding, CFAR_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, GuardCell_F, WindowCell_F, GuardCell_S, WindowCell_S);
			break;
		}
		default:
		{
			CACFAR2D << <GridSize, BlockSize >> >(CFAR_Reference_Padding, CFAR_Signal_Padding, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, GuardCell_F, WindowCell_F, GuardCell_S, WindowCell_S);
			break;
		}
		}
		DetectByCFAR2D << <GridSize, BlockSize >> >(Detect_Result, CFAR_Signal_Padding, CFAR_Reference_Padding, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, GuardCell_F, WindowCell_F, GuardCell_S, WindowCell_S, Min_Detect_Factor, Min_Detect_Threshold);
	}
}