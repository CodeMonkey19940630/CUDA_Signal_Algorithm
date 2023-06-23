// CUDAMatchFilter.cpp : ���� DLL Ӧ�ó���ĵ���������
//
//#include "stdafx.h"
#include "CUDAMatchFilter.h"
#include "../CUDAMatchFilterAlgorithm/CUDAMatchFilterAlgorithmCore.cuh"
namespace CUDAMatchFilterNamespace
{
	void CUDAMatchFilter::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	void CUDAMatchFilter::CUFFTResourceAllocation(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count)
	{
		this->Rank = 1;
		this->N[0] = Count_Of_Sampling_Point_Of_Monopulse;
		this->Inembed[0] = 0;
		this->Istride = 1;
		this->Idist = Count_Of_Sampling_Point_Of_Monopulse;
		this->Onembed[0] = 0;
		this->Ostride = 1;
		this->Odist = Count_Of_Sampling_Point_Of_Monopulse;
		this->Type = CUFFT_C2C;
		this->Batch = Count_Of_Pulse_Group * Antenna_Chanel_Count;
		//cufftPlanManyֻ�����һ��Plan��һ�Σ�һ��Plan��cufftPlanManyʹ�þ������ˣ�Plan��������;�ı����ʼ������á�
		cufftPlanMany(&(this->Plan_Forward), this->Rank, this->N, this->Inembed, this->Istride, this->Idist, this->Onembed, this->Ostride, this->Odist, this->Type, this->Batch);
		cufftPlanMany(&(this->Plan_Backword), this->Rank, this->N, this->Inembed, this->Istride, this->Idist, this->Onembed, this->Ostride, this->Odist, this->Type, this->Batch);
	}
	CUDAMatchFilter::CUDAMatchFilter()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDAMatchFilter::~CUDAMatchFilter()
	{
		//cuFFT������٣����������ٽ����
		cufftResult Result_Of_Plan_Forward = cufftDestroy(this->Plan_Forward);
		cufftResult Result_Of_Plan_Backword = cufftDestroy(this->Plan_Backword);
	}
	//void CUDAGeographyAndSeaClutter::Procedure()����ֻ��ҵ�������
	void CUDAMatchFilter::Procedure(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int Baseband_Total_Size, int ScaleFactor, float2 * Baseband_Signal, float2 * Baseband_Frequency_Domain_Signal_Kernel)
	{
		CUDAMatchFilterAlgorithmCore(this->Plan_Forward, this->Plan_Backword, this->BlockSize, Baseband_Total_Size, ScaleFactor, Baseband_Signal, Baseband_Frequency_Domain_Signal_Kernel);
	}
}