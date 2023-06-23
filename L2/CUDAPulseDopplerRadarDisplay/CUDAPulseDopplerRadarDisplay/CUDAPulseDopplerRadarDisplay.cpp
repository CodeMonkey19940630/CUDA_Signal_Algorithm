// CUDAPulseDopplerRadarDisplay.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"
#include "CUDAPulseDopplerRadarDisplay.h"
#include "../CUDAPulseDopplerRadarDisplayAlgorithm/CUDAPulseDopplerRadarDisplayAlgorithmCore.cuh"
namespace CUDAPulseDopplerRadarDisplayNamespace
{
	CUDAPulseDopplerRadarDisplay::CUDAPulseDopplerRadarDisplay()
	{
	}
	CUDAPulseDopplerRadarDisplay::~CUDAPulseDopplerRadarDisplay()
	{
		//cuFFT������٣����������ٽ����
		cufftResult Result = cufftDestroy(this->Plan);
	}
	void CUDAPulseDopplerRadarDisplay::CUFFTResourceAllocation(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Moving_Target_Indicator_Order)
	{

		this->Rank = 1;
		this->N[0] = Count_Of_Pulse_Group - Moving_Target_Indicator_Order + 1;
		this->Inembed[0] = 0;
		this->Istride = Count_Of_Sampling_Point_Of_Monopulse;
		this->Idist = 1;
		this->Onembed[0] = 0;
		this->Ostride = Count_Of_Sampling_Point_Of_Monopulse;
		this->Odist = 1;
		this->Type = CUFFT_C2C;
		this->Batch = Count_Of_Sampling_Point_Of_Monopulse;
		//cufftPlanManyֻ�����һ��Plan��һ�Σ�һ��Plan��cufftPlanManyʹ�þ������ˣ�Plan��������;�ı����ʼ������á�
		cufftPlanMany(&(this->Plan), this->Rank, this->N, this->Inembed, this->Istride, this->Idist, this->Onembed, this->Ostride, this->Odist, this->Type, this->Batch);
	}

	//void PulseDopplerRadarDisplay::Procedure()����ֻ��ҵ�������
	void CUDAPulseDopplerRadarDisplay::Procedure(float2 * Radar_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int Moving_Target_Indicator_Order)
	{
		CUDAPulseDopplerRadarDisplayAlgorithmCore(this->Plan, Radar_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count);
	}
}

