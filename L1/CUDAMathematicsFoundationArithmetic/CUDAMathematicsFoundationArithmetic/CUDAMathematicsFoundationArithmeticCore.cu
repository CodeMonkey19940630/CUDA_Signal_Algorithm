#include "CUDAMathematicsFoundationArithmeticCore.cuh"
namespace CUDAMathematicsFoundationArithmeticNamespace
{
	//ComplexAddition��������ӡ�
	__device__ float2 ComplexAddition(float2 Left, float2 Right)
	{
		float2 Result;
		Result.x = Left.x + Right.x;
		Result.y = Left.y + Right.y;
		return Result;
	}

	//ComplexArrayAddition������������ӡ�
	__global__ void ComplexArrayAddition(float2* Left, float2 *Right, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Left[Index].x = Left[Index].x + Right[Index].x;
			Left[Index].y = Left[Index].y + Right[Index].y;
		}
		__syncthreads();
	}

	//ComplexSubtraction�����������
	__device__ float2 ComplexSubtraction(float2 Left, float2 Right)
	{
		float2 Result;
		Result.x = Left.x - Right.x;
		Result.y = Left.y - Right.y;
		return Result;
	}

	//ComplexArraySubtraction���������������
	__global__ void ComplexArraySubtraction(float2 *Left, float2 *Right, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Left[Index].x = Left[Index].x - Right[Index].x;
			Left[Index].y = Left[Index].y - Right[Index].y;
		}
		__syncthreads();
	}

	//ComplexScale������������
	__device__ float2 ComplexScale(float Scale, float2 Left)
	{
		float2 Result;
		Result.x = Scale * Left.x;
		Result.y = Scale * Left.y;
		return Result;
	}

	//ComplexMultiplication��������ˡ�
	__device__ float2 ComplexMultiplication(float2 Left, float2 Right)
	{
		float2 Result;
		Result.x = Left.x * Right.x - Left.y * Right.y;
		Result.y = Left.x * Right.y + Left.y * Right.x;
		return Result;
	}

	//ComplexAbsolute�����������ֵ��
	__device__ float ComplexAbsolute(float2 Left)
	{
		float Result;
		Result = sqrt(Left.x * Left.x + Left.y * Left.y);
		return Result;
	}

	//ComplexArrayAbsolute���������������ֵ��
	__global__ void ComplexArrayAbsolute(float *Result, float2 *Left, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Result[Index] = ComplexAbsolute(Left[Index]);
		}
		__syncthreads();
	}

	//Complex Pointwise Multiplication And Scale�����������˲�������
	__global__ void ComplexPointwiseMultiplicationAndScale(float2 *Left, const float2 *Right, int Total_Size, float Scale)
	{

		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			float2 Complex_Multiplication_Result = ComplexMultiplication(Left[Index], Right[Index]);
			Left[Index] = ComplexScale(Scale, Complex_Multiplication_Result);
		}
		__syncthreads();
	}

	//ComplexConjugate������������㡣
	__global__ void ComplexConjugate(float2 *Left, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Left[Index].x = Left[Index].x;
			Left[Index].y = -Left[Index].y;
		}
		__syncthreads();
	}

	//FloatArrayAddition��˫float��������ӡ�
	__global__ void FloatArrayAddition(float* Left, float *Right, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Left[Index] = Left[Index] + Right[Index];
		}
		__syncthreads();
	}

	//FloatArrayScale��float�����������
	__global__ void FloatArrayScale(float *Left, float Scale, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Left[Index] *= Scale;
		}
		__syncthreads();
	}

	//ComplexArrayScale������������
	__global__ void ComplexArrayScale(float2 *Left, float Scale, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			Left[Index].x *= Scale;
			Left[Index].y *= Scale;
		}
		__syncthreads();
	}

	//RealConvolution��ʵ��������㡣
	__global__ void RealConvolution(float *Result, float *Left, float *Right, int Length_Left, int Length_Right, int Length_Result)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Length_Result; Index += Total_Threads)
		{
			float Temporary_Summation = 0.0f;
			for (int I = 0; I < Length_Right; I++)
			{
				int K = Index - I;
				if (0 <= K && K < Length_Left)
				{
					Temporary_Summation += Left[K] * Right[I];
				}
			}
			Result[Index] = Temporary_Summation;
		}
		__syncthreads();
	}

	//ComplexConvolution������������㡣
	__global__ void ComplexConvolution(float2 *Result, float2 *Left, float2 *Right, int Length_Left, int Length_Right, int Length_Result)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Length_Result; Index += Total_Threads)
		{
			float2 Temporary_Summation;
			Temporary_Summation.x = 0.0f;
			Temporary_Summation.y = 0.0f;
			for (int I = 0; I < Length_Right; I++)
			{
				int K = Index - I;
				if (0 <= K && K < Length_Left)
				{
					Temporary_Summation.x += Left[K].x * Right[I].x;
					Temporary_Summation.y += Left[K].y * Right[I].y;
				}
			}
			Result[Index].x = Result[Index].x + Temporary_Summation.x;
			Result[Index].y = Result[Index].y + Temporary_Summation.y;
		}
		__syncthreads();
	}


	//ComplexConvolution��ʵ��������Ͼ�����㡣
	__global__ void RealComplexConvolution(float2 *Result, float2 *Left, float *Right, int Length_Left, int Length_Right, int Length_Result)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Length_Result; Index += Total_Threads)
		{
			float2 Temporary_Summation;
			Temporary_Summation.x = 0.0f;
			Temporary_Summation.y = 0.0f;
			for (int I = 0; I < Length_Right; I++)
			{
				int K = Index - I;
				if (0 <= K && K < Length_Left)
				{
					Temporary_Summation.x += Left[K].x * Right[I];
					Temporary_Summation.y += Left[K].y * Right[I];
				}
			}
			Result[Index].x = Result[Index].x + Temporary_Summation.x;
			Result[Index].y = Result[Index].y + Temporary_Summation.y;
		}
		__syncthreads();
	}


	//CorrelationCalculation��˫float��������Լ��㡣
	__global__ void CorrelationCalculation(float *Result, float *Left, float *Right, int Result_Length, int Input_Length)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Result_Length; Index += Total_Threads)
		{
			int I = Index - Result_Length / 2;
			for (int J = 0; J < Input_Length; J++)
			{
				int K = I + J;
				if (K >= 0 && K < Input_Length)
				{
					Result[I + Result_Length / 2] += Left[K] * Right[J];
				}
			}
		}
		__syncthreads();
	}

	//TwoFloatArrayScaleAndAddition��˫float������ķ�������ӡ�
	__global__ void TwoFloatArrayScaleAndAddition(float *Result, float *Left, float *Right, float Alpha, float Beta, int Length)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Length; Index += Total_Threads)
		{
			Result[Index] = Left[Index] * Alpha + Right[Index] * Beta;
		}
		__syncthreads();
	}

	//ConvertRealToComplex��ʵ��������ת����
	__global__ void ConvertRealToComplex(float2 *Result, float *Left, int Length)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Length; Index += Total_Threads)
		{
			Result[Index].x = Left[Index];
			Result[Index].y = Left[Index];
		}
		__syncthreads();
	}

	//ConvolutionSame��������㣨sameģʽ����
	__global__ void ConvolutionSame(float* Result, float* Signal_Data, float* Filter_Data, int Data_Length, int Filter_Order)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Data_Length + Filter_Order - 1; Index += Total_Threads)
		{
			Result[Index] = 0;
			for (int I = int(fmaxf(0, Index + 1 - Filter_Order)); I <= int(fminf(Index, Data_Length - 1)); I++)
			{
				Result[Index] += Signal_Data[I] * Filter_Data[Index - I];
			}
		}
		__syncthreads();
	}

	//CUDAExponetialDistributionAssistance��ָ���ֲ�Э����������CUDA��û�з���ָ���ֲ�����������ɺ���������ֻ����Ƹú����������float��ƽ���ֲ������������мӹ����Ӷ����ط���ָ���ֲ���float����������顣
	__global__ void ExponetialDistributionAssistance(float* OutPut_Random_Exponetial_Distribution_Data, float* InPut_Random_Exponetial_Distribution_Data, double lambda, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			if (InPut_Random_Exponetial_Distribution_Data[Index] > 0)
			{
				OutPut_Random_Exponetial_Distribution_Data[Index] = 1.0 - expf(-lambda * InPut_Random_Exponetial_Distribution_Data[Index]);
			}
		}
		__syncthreads();
	}

	//RayleighDistributionAssistance�������ֲ�Э����������CUDA��û�з��������ֲ�����������ɺ���������ֻ����Ƹú����������float��ƽ���ֲ������������мӹ����Ӷ����ط��������ֲ���float����������顣
	__global__ void RayleighDistributionAssistance(float* OutPut_Random_Rayleigh_Distribution_Data, float* InPut_Random_Rayleigh_Distribution_Data, float Rho, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			OutPut_Random_Rayleigh_Distribution_Data[Index] = 1.0 - expf(-(InPut_Random_Rayleigh_Distribution_Data[Index] * InPut_Random_Rayleigh_Distribution_Data[Index]) / (2.0 * Rho * Rho));
		}
		__syncthreads();
	}

	//WeibullDistributionAssistance���������ֲ�Э����������CUDA��û�з����������ֲ�����������ɺ���������ֻ����Ƹú����������float��ƽ���ֲ������������мӹ����Ӷ����ط����������ֲ���float����������顣
	__global__ void WeibullDistributionAssistance(float* OutPut_Random_Weibull_Distribution_Data, float* InPut_Random_Weibull_Distribution_Data, int K, double B, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			OutPut_Random_Weibull_Distribution_Data[Index] = 1.0 - expf(-B * (powf(InPut_Random_Weibull_Distribution_Data[Index], K)));
		}
		__syncthreads();
	}

	__device__ float AntiGamma(float X, float S)
	{
		float  A = 0;
		float Result = 0;
		for (int I = 0; I < 10; I++){
			A += pow(X, I) / tgamma(S + I + 1);
		}
		Result = (pow(X, S)*tgamma(S)*A*exp(-X)) / tgamma(S);
		return Result;
	}

	__global__ void Chi_squareDistributionAssistance(float* OutPut_Random_Chi_Square_Distribution_Data, float* InPut_Random_Chi_Square_Distribution_Data, float K, float X, int Total_Size)
	{
		int Total_Threads = gridDim.x * blockDim.x;
		int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
		float K_2 = K / 2;
		for (int Index = Thread_ID; Index < Total_Size; Index += Total_Threads)
		{
			OutPut_Random_Chi_Square_Distribution_Data[Index] = AntiGamma(InPut_Random_Chi_Square_Distribution_Data[Index] / 2, K_2) / tgamma(K_2);
		}
		__syncthreads();
	}

}