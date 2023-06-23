#include "CUDAMovingTargetIndicatorAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
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

__global__ void SecondOrderEigencanceller(float2* Pulse_Initial_Address_First, float2* Pulse_Initial_Address_Second,int Total_Size)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		Pulse_Initial_Address_First[Index].x = Pulse_Initial_Address_First[Index].x - Pulse_Initial_Address_Second[Index].x;
		Pulse_Initial_Address_First[Index].y = Pulse_Initial_Address_First[Index].y - Pulse_Initial_Address_Second[Index].y;
	}
	__syncthreads();
}

__global__ void ThirdOrderEigencanceller(float2* Pulse_Initial_Address_First, float2* Pulse_Initial_Address_Second, float2* Pulse_Initial_Address_Third, int Total_Size)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
	{
		Pulse_Initial_Address_First[Index].x = Pulse_Initial_Address_First[Index].x - 2.0 *  Pulse_Initial_Address_Second[Index].x + Pulse_Initial_Address_Third[Index].x;
		Pulse_Initial_Address_First[Index].y = Pulse_Initial_Address_First[Index].y - 2.0 *  Pulse_Initial_Address_Second[Index].y + Pulse_Initial_Address_Third[Index].y;
	}
	__syncthreads();
}

void CUDAMovingTargetIndicatorAlgorithmCore(float2 * Radar_Data_Cube_Address, int BlockSize, int Moving_Target_Indicator_Order, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count)
{
	if (Moving_Target_Indicator_Order >= 3)
	{
		int MTI_Order = 3;
		int GridSize = (Count_Of_Sampling_Point_Of_Monopulse + BlockSize - 1) / BlockSize;
		for (int Index_Z = 0; Index_Z < Antenna_Chanel_Count; Index_Z++)
		{
			for (int Index_Y = 0; Index_Y < Count_Of_Pulse_Group - MTI_Order + 1; Index_Y++)
			{
				float2 * Radar_Signal_Padding = GetArrayOneDimensionFloat2Data(Radar_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Y, Index_Z);
				float2 * Pulse_Data_Initial_Address_First = Radar_Signal_Padding;
				float2 * Pulse_Data_Initial_Address_Second = Radar_Signal_Padding + Count_Of_Sampling_Point_Of_Monopulse;
				float2 * Pulse_Data_Initial_Address_Third = Radar_Signal_Padding + 2 * Count_Of_Sampling_Point_Of_Monopulse;
				ThirdOrderEigencanceller <<<GridSize, BlockSize>>>(Pulse_Data_Initial_Address_First, Pulse_Data_Initial_Address_Second, Pulse_Data_Initial_Address_Third, Count_Of_Sampling_Point_Of_Monopulse);
			}
		}
	}
	else if (Moving_Target_Indicator_Order >= 2 && Moving_Target_Indicator_Order < 3)
	{
		int MTI_Order = 2;
		int GridSize = (Count_Of_Sampling_Point_Of_Monopulse + BlockSize - 1) / BlockSize;
		for (int Index_Z = 0; Index_Z < Antenna_Chanel_Count; Index_Z++)
		{
			for (int Index_Y = 0; Index_Y < Count_Of_Pulse_Group - MTI_Order + 1; Index_Y++)
			{

				float2 * Radar_Signal_Padding = GetArrayOneDimensionFloat2Data(Radar_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Y, Index_Z);
				float2 * Pulse_Data_Initial_Address_First = Radar_Signal_Padding;
				float2 * Pulse_Data_Initial_Address_Second = Radar_Signal_Padding + Count_Of_Sampling_Point_Of_Monopulse;
				SecondOrderEigencanceller <<<GridSize, BlockSize >>>(Pulse_Data_Initial_Address_First, Pulse_Data_Initial_Address_Second, Count_Of_Sampling_Point_Of_Monopulse);
			}
		}
	}
	else if (Moving_Target_Indicator_Order >= 1 && Moving_Target_Indicator_Order < 2)
	{
	}
}