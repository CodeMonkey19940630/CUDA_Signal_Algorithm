#ifndef CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_H
#define CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_H
#ifdef CUDAMATHEMATICSFOUNDATIONARITHMETIC_EXPORTS
#define CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS __declspec(dllexport)
#else
#define CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include <stdio.h>
#include <math.h>
//备用CUDA检测函数，如果开启
//#include "helper_string.h"
//#include "helper_cuda.h"
//#include "helper_functions.h"
//CUDAMathematicsFoundationArithmeticCore.cu文件中的所有函数声明
namespace CUDAMathematicsFoundationArithmeticNamespace
{
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexArrayAddition(float2* Left, float2 *Right, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexArraySubtraction(float2 *Left, float2 *Right, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexArrayAbsolute(float *Result, float2 *Left, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexPointwiseMultiplicationAndScale(float2 *Left, const float2 *Right, int Total_Size, float Scale);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexConjugate(float2 *Left, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void FloatArrayAddition(float* Left, float *Right, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void FloatArrayScale(float *Left, float Scale, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexArrayScale(float2 *Left, float Scale, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void RealConvolution(float *Result, float *Left, float *Right, int Length_Left, int Length_Right, int Length_Result);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ComplexConvolution(float2 *Result, float2 *Left, float2 *Right, int Length_Left, int Length_Right, int Length_Result);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void RealComplexConvolution(float2 *Result, float2 *Left, float *Right, int Length_Left, int Length_Right, int Length_Result);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void CorrelationCalculation(float *Result, float *Left, float *Right, int Result_Length, int Input_Length);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void TwoFloatArrayScaleAndAddition(float *Result, float *Left, float *Right, float Alpha, float Beta, int Length);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ConvertRealToComplex(float2 *Result, float *Left, int Length);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ConvolutionSame(float* Result, float* Signal_Data, float* Filter_Data, int Data_Length, int Filter_Order);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ExponetialDistributionAssistance(float* OutPut_Random_Exponetial_Distribution_Data, float* InPut_Random_Exponetial_Distribution_Data, double lambda, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void RayleighDistributionAssistance(float* OutPut_Random_Rayleigh_Distribution_Data, float* InPut_Random_Rayleigh_Distribution_Data, float Rho, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void WeibullDistributionAssistance(float* OutPut_Random_Weibull_Distribution_Data, float* InPut_Random_Weibull_Distribution_Data, int K, double B, int Total_Size);
	CUDA_MATHEMATICS_FOUNDATION_ARITHMETIC_EXPORTS  __global__ void ChiSquareDistributionAssistance(float* OutPut_Random_Chi_Square_Distribution_Data, float* InPut_Random_Chi_Square_Distribution_Data, float K, float X, int Total_Size);

}
#endif