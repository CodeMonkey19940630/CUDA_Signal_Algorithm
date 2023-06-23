#include "CUDAPulseDopplerRadarDisplayAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
//ÊµÏÖ__global__ void CUDAPulseDopplerRadarDisplayAlgorithmCore()ºËº¯Êý
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
void CUDAPulseDopplerRadarDisplayAlgorithmCore(cufftHandle Plan, float2 * Radar_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count)
{
	for (int Index = 0; Index<Antenna_Chanel_Count; Index++)
	{
		float2 * Radar_Signal_Padding = GetArrayOneDimensionFloat2Data(Radar_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, 0, Index);
		checkCudaErrors(cufftExecC2C(Plan, (cufftComplex *)(Radar_Signal_Padding), (cufftComplex *)(Radar_Signal_Padding), CUFFT_FORWARD));
	}
}