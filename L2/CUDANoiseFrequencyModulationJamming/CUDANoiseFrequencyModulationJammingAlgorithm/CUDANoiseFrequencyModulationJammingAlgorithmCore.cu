#include "CUDANoiseFrequencyModulationJammingAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
#define  PI_CUDA 3.141592653589793f
__device__ __host__ int CalculationOfOffset(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	return Axis_Y * Count_Of_Sampling_Point_Of_Monopulse + Axis_Z * Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group;
}

__device__ __host__ float * GetArrayOneDimensionFloatData(float *Initial_Position, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	float * One_Dimension_Float_Data_Position = NULL;
	One_Dimension_Float_Data_Position = Initial_Position + CalculationOfOffset(Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Axis_Y, Axis_Z);
	return One_Dimension_Float_Data_Position;
}

__host__ __device__ float2 * GetArrayOneDimensionFloat2Data(float2*Initial_Position, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Axis_Y, int Axis_Z)
{
	float2 *One_Dimension_Float2_Data_Position = NULL;
	One_Dimension_Float2_Data_Position = Initial_Position + CalculationOfOffset(Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Axis_Y, Axis_Z);
	return One_Dimension_Float2_Data_Position;
}


__global__ void RealFrequencyModulationJammingGenerator(float Amplitude, float Frequency_Modulation_Coefficient, float Medium_Frequency, float Sampling_Frequency_Of_Medium_Frequency, float* Random_Complex, int Count_Of_Sampling_Point_Of_Monopulse, float * Result)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;

	for (int Index = Thread_ID; Index < Count_Of_Sampling_Point_Of_Monopulse; Index += Total_Threads)
	{
		float Temporary_Frequency = Medium_Frequency + Frequency_Modulation_Coefficient * Random_Complex[Index];
		Result[Index] = Result[Index] + Amplitude * cosf(2 * PI_CUDA*Temporary_Frequency*Index / Sampling_Frequency_Of_Medium_Frequency);
	}
}

__global__ void ComplexFrequencyModulationJammingGenerator(float Amplitude, float Frequency_Modulation_Coefficient, float Medium_Frequency, float Sampling_Frequency_Of_Medium_Frequency, float2 * Random_Complex, int Count_Of_Sampling_Point_Of_Monopulse, float2 * Result)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;

	for (unsigned int Index = Thread_ID; Index < Count_Of_Sampling_Point_Of_Monopulse; Index += Total_Threads)
	{
		float Frequency_X = Medium_Frequency;
		float Frequency_Y = Medium_Frequency;
		for (int k = 0; k < Index; k++)
		{
			Frequency_X = Frequency_X + Frequency_Modulation_Coefficient*Random_Complex[Index].x;
			Frequency_Y = Frequency_Y + Frequency_Modulation_Coefficient*Random_Complex[Index].x;
		}
		Result[Index].x = Amplitude * cosf(2 * PI_CUDA*Frequency_X * Index / Sampling_Frequency_Of_Medium_Frequency);
		Result[Index].y = Amplitude * sinf(2 * PI_CUDA*Frequency_Y * Index / Sampling_Frequency_Of_Medium_Frequency);
	}
}

float Ino(float X)
{
	float Y, T, E, Z, De, Sde;
	Y = X / 2.0;
	T = 1.0e-08;
	E = 1.0;
	De = 1.0;
	for (int i = 1; i <= 25; i++)
	{
		De = De * Y / i;
		Sde = De * De;
		E = E + Sde;
		if ((E * T) <= Sde)
		{
			continue;
		}
		else
		{
			Z = E;
		}
	}
	return (Z);
}

void KaiserWindow(int Order, double Band_Width, double Alpha, float* hFIR)
{
	float*Hd = (float *)malloc(sizeof(float) * Order);
	memset(Hd, 0.0, (Order)* sizeof(float));
	float* W = (float *)malloc(sizeof(float) * Order);
	memset(W, 0.0, (Order)* sizeof(float));
	int M = 2;
	float A = (Order - 1) / 2;
	float Pi = 4.0*atan(1.0);
	for (int Index = 0; Index < Order; Index++)
	{
		if (Index == A)
		{
			Hd[Index] = Band_Width;
		}
		else
		{
			float B = Index - A;
			Hd[Index] = sin(Pi*B*Band_Width) / (Pi*B);
		}

	}
	//Switch语句有缺陷，在该选择语句中case 1永远选不到。
	switch (M)
	{
		case 1:
		{
			for (int Index = 0; Index < Order; Index++)
			{
				W[Index] = 1.0;
			}
			break;
		}
		case 2:
		{
			float Bes = Ino(Alpha);
			for (int Index = 0; Index < Order; Index++)
			{
				float G = 1.0 - pow(1.0 - 2.0*(float)Index / (float)(Order - 1), 2);
				float Q = Alpha*sqrt(G);
				W[Index] = Ino(Q);
				W[Index] = W[Index] / Bes;
			}
			break;
		}
		default:
			break;
	}
	for (int Index = 0; Index < Order; Index++)
	{
		hFIR[Index] = Hd[Index] * W[Index];
	}
	free(W);
	free(Hd);
}

void BandPassFilter(unsigned int Order, double Start_Frequency, double Stop_Frequency, double Alpha, float *Filter_Pluse_Response)
{
	//原先的BPF设计
	float * Band_pass_Filter = (float *)malloc(sizeof(float) * Order);
	memset(Band_pass_Filter, 0.0, (Order)* sizeof(float));
	float * Start = (float *)malloc(sizeof(float) * Order);
	memset(Start, 0.0, (Order)* sizeof(float));
	float * Stop = (float *)malloc(sizeof(float) * Order);
	memset(Stop, 0.0, (Order)* sizeof(float));
	KaiserWindow(Order, Start_Frequency, Alpha, Start);
	KaiserWindow(Order, Stop_Frequency, Alpha, Stop);
	for (int Index = 0; Index < Order; Index++)
	{
		Band_pass_Filter[Index] = Stop[Index] - Start[Index];
		Filter_Pluse_Response[Index] = Band_pass_Filter[Index];
	}
	free(Band_pass_Filter);
	free(Start);
	free(Stop);
}


void CUDANoiseFrequencyModulationJammingAlgorithmCore(float * Radar_Float_Data_Cube_Address, float2 * Radar_Float2_Data_Cube_Address, int BlockSize, double Amplitude, double Frequency_Modulation_Coefficient, double Jamming_Center_Frequency, double Band_Width, double Sampling_Frequency_Of_Medium_Frequency, double Sampling_Frequency_Of_Band, double PRT, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Only_Baseband)
{
	double Beta = 4.55;
	for (int Index_Z = 0; Index_Z < Antenna_Chanel_Count; Index_Z++)
	{
		for (int Index_Y = 0; Index_Y < Count_Of_Pulse_Group; Index_Y++)
		{
			if (!Use_Only_Baseband)
			{
				int GridSize = (Count_Of_Sampling_Point_Of_Monopulse + BlockSize - 1) / BlockSize;
				int Order = 302;
				float * Filter_Pluse_Response = (float *)malloc(sizeof(float) * Order);
				memset(Filter_Pluse_Response, 0.0, (Order) * sizeof(float));
				float Frequency_Begin = (-Band_Width / 2) / Sampling_Frequency_Of_Medium_Frequency * 2.0;
				float Frequency_End = (+Band_Width / 2) / Sampling_Frequency_Of_Medium_Frequency * 2.0;
				BandPassFilter(Order, Frequency_Begin, Frequency_End, Beta, Filter_Pluse_Response);
				float* Filter_Address = NULL;
				checkCudaErrors(cudaMalloc((void**)&Filter_Address, Order * sizeof(float)));
				checkCudaErrors(cudaMemcpy(Filter_Address, Filter_Pluse_Response, Order * sizeof(float), cudaMemcpyHostToDevice));
				float *Noise_Data = NULL;
				checkCudaErrors(cudaMalloc((void **)&Noise_Data, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float)));
				checkCudaErrors(cudaMemset(Noise_Data, 0, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float)));
				curandGenerator_t Random_Generator;
				curandStatus_t Curand_Result = curandGenerateNormal(Random_Generator, (float*)Noise_Data, Count_Of_Sampling_Point_Of_Monopulse, 0.0, 1.0);
				float * Convolution_Result;//卷积结果
				checkCudaErrors(cudaMalloc(&Convolution_Result, (Count_Of_Sampling_Point_Of_Monopulse + Order - 1) * sizeof(float)));
				checkCudaErrors(cudaMemset(Convolution_Result, 0, (Count_Of_Sampling_Point_Of_Monopulse + Order - 1) * sizeof(float)));
				CUDAMathematicsFoundationArithmeticNamespace::RealConvolution << <GridSize, BlockSize >> >(Convolution_Result, Noise_Data, Filter_Pluse_Response, Count_Of_Sampling_Point_Of_Monopulse, Order, Count_Of_Sampling_Point_Of_Monopulse + Order - 1);
				float * Radar_Signal_Padding = GetArrayOneDimensionFloatData(Radar_Float_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Y, 0);
				RealFrequencyModulationJammingGenerator << <GridSize, BlockSize >> >(Amplitude, Frequency_Modulation_Coefficient, Jamming_Center_Frequency, Sampling_Frequency_Of_Medium_Frequency, Convolution_Result + Order / 2, Count_Of_Sampling_Point_Of_Monopulse, Radar_Signal_Padding);
				free(Filter_Pluse_Response);
				checkCudaErrors(cudaFree(Filter_Address));
				checkCudaErrors(cudaFree(Noise_Data));
				checkCudaErrors(cudaFree(Convolution_Result));
			
			}
			else
			{
				int GridSize = (Sampling_Frequency_Of_Band * PRT + BlockSize - 1) / BlockSize;
				int Order = 302;
				float * Filter_Pluse_Response = (float *)malloc(sizeof(float) * Order);
				memset(Filter_Pluse_Response, 0.0, (Order)* sizeof(float));
				float Frequency_Begin = (-Band_Width / 2) / Sampling_Frequency_Of_Band * 2.0;
				float Frequency_End = (+Band_Width / 2) / Sampling_Frequency_Of_Band * 2.0;
				BandPassFilter(Order, Frequency_Begin, Frequency_End, Beta, Filter_Pluse_Response);
				float* Filter_Address = NULL;
				checkCudaErrors(cudaMalloc((void**)&Filter_Address, Order * sizeof(float)));
				checkCudaErrors(cudaMemcpy(Filter_Address, Filter_Pluse_Response, Order * sizeof(float), cudaMemcpyHostToDevice));
				float2 *Noise_Data = NULL;
				checkCudaErrors(cudaMalloc((void **)&Noise_Data, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float2)));
				checkCudaErrors(cudaMemset(Noise_Data, 0, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float2)));
				curandGenerator_t Random_Generator;
				curandStatus_t Curand_Result = curandGenerateNormal(Random_Generator, (float*)Noise_Data, Count_Of_Sampling_Point_Of_Monopulse * 2, 0.0, 1.0);
				float2 * Convolution_Result;//卷积结果
				checkCudaErrors(cudaMalloc(&Convolution_Result, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float)));
				checkCudaErrors(cudaMemset(Convolution_Result, 0, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float)));
				CUDAMathematicsFoundationArithmeticNamespace::RealComplexConvolution << <GridSize, BlockSize >> >(Convolution_Result, Noise_Data, Filter_Pluse_Response, Count_Of_Sampling_Point_Of_Monopulse, Order, Count_Of_Sampling_Point_Of_Monopulse);
				float2 * Radar_Signal_Padding = GetArrayOneDimensionFloat2Data(Radar_Float2_Data_Cube_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Index_Y, Index_Z);
				ComplexFrequencyModulationJammingGenerator << <GridSize, BlockSize >> >(Amplitude, Frequency_Modulation_Coefficient, Jamming_Center_Frequency, Sampling_Frequency_Of_Medium_Frequency, Convolution_Result, Count_Of_Sampling_Point_Of_Monopulse, Radar_Signal_Padding);
				free(Filter_Pluse_Response);
				checkCudaErrors(cudaFree(Filter_Address));
				checkCudaErrors(cudaFree(Noise_Data));
				checkCudaErrors(cudaFree(Convolution_Result));
			}
		}
	}
}