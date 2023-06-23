#include "CUDAMatchFilterAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
void CUDAMatchFilterAlgorithmCore(cufftHandle Plan_Forward, cufftHandle Plan_Backword, int BlockSize, int Baseband_Total_Size, int ScaleFactor, float2 * Baseband_Signal, float2 * Baseband_Frequency_Domain_Signal_Kernel)
{
	checkCudaErrors(cufftExecC2C(Plan_Forward, (cufftComplex *)Baseband_Signal, (cufftComplex *)Baseband_Signal, CUFFT_FORWARD));
	unsigned int GridSize = (Baseband_Total_Size + BlockSize - 1) / BlockSize;
	//使用基础函数库内容。
	CUDAMathematicsFoundationArithmeticNamespace::ComplexPointwiseMultiplicationAndScale << <GridSize, BlockSize >> >(Baseband_Signal, Baseband_Frequency_Domain_Signal_Kernel, BlockSize, ScaleFactor);
	checkCudaErrors(cufftExecC2C(Plan_Backword, (cufftComplex *)Baseband_Signal, (cufftComplex *)Baseband_Signal, CUFFT_INVERSE));

}