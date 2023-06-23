#include "CUDASegmentedConvolutionAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"

__global__ void Fliper(int Signal_Length, float2* Signal, float2* Signal_Padded)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int j = 0;
	for (unsigned int i = Thread_ID; i < Signal_Length - 1; i += Total_Threads)
	{
		j = Signal_Length - i - 2;
		Signal_Padded[i] = Signal[j];
	}
}

__global__ void TranPosition(int Signal_Length, float2* Signal, int Signal_Padded_Length, float2* Signal_Padded)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int j = 0;
	for (unsigned int i = Thread_ID; i < Signal_Length; i += Total_Threads)
	{
		j = i + Signal_Padded_Length - 1;
		Signal_Padded[i] = Signal[j];
	}
}


__global__ void TranPositionB(int Signal_Length, float2* Signal, int Signal_Padded_Length, float2* Signal_Padded)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int j = 0;
	for (int i = Thread_ID; i < Signal_Length; i += Total_Threads)
	{
		j = i + Signal_Padded_Length - 1;
		Signal_Padded[i] = Signal[j];
	}
}

__global__ void TranPositionC(int Signal_Length, float2* Signal, int Signal_Padded_Length, float2* Signal_Padded, int FFT_Length)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int j = 0;
	int k = 0;
	for (int i = Thread_ID; i < Signal_Length; i += Total_Threads)
	{
		j = i + Signal_Padded_Length - 1;
		k = FFT_Length - 1 - Signal_Length + i;
		Signal_Padded[j] = Signal[k];
	}
}

__global__ void TranPositionD(int Signal_Length, float2* Signal, int Signal_Padded_Length, float2* Signal_Padded)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int j = 0;
	for (int i = Thread_ID; i < Signal_Length; i += Total_Threads)
	{
		j = Signal_Padded_Length + i;
		Signal_Padded[i] = Signal[j];
	}
}

__global__ void TranPositionE(int Signal_Length, float2* Signal, int Signal_Padded_Length, float2* Signal_Padded, int N3, int FFT_Length)
{
	const int numThreads = blockDim.x * gridDim.x;
	const int threadID = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned int j = 0;
	unsigned int k = 0;
	for (unsigned int i = threadID; i < Signal_Length; i += numThreads)
	{
		j = i + Signal_Padded_Length - 1;
		k = FFT_Length - 1 - N3 + i;
		Signal_Padded[j] = Signal[k];
	}
	return;

}

__global__ void TranPositionZ(int Signal_Length, float2* Signal, int Signal_Padded_Length, float2* Signal_Padded)
{
	int Total_Threads = gridDim.x * blockDim.x;
	int Thread_ID = blockIdx.x * blockDim.x + threadIdx.x;
	int j = 0;
	for (int i = Thread_ID; i < Signal_Length; i += Total_Threads)
	{
		j = i + Signal_Padded_Length - 1;
		Signal_Padded[j] = Signal[i];
	}
}

int CalculateSectionLength(int Kernel_Length)
{
	// Calculate section length M that M + N - 1 is powers of 2 and M is close to N
	int FFT_Length = 1;
	while ((2 * Kernel_Length) > FFT_Length)
	{
		FFT_Length *= 2;
	}
	return FFT_Length;
}

void CUDASegmentedConvolutionAlgorithmCore(cufftHandle Plan, int BlockSize, int Signal_Length, int Kernel_Length, float2* Signal, float2 *Kernel)
{
	int U = 0;
	cufftComplex *Padded_Buffer, *Piece_Buffer, *Kernel_Buffer, *Kernel_Fliper;
	int FFT_Length = CalculateSectionLength(Kernel_Length);
	int Overlap_Length = FFT_Length - Kernel_Length;
	int	Convolution_Length = Signal_Length + Kernel_Length - 1;
	int Piece_count = (Convolution_Length + Overlap_Length - 1) / Overlap_Length;
	int The_Last = Convolution_Length%Overlap_Length;
	int Total_Length = 0;
	if (The_Last == 0){
		Total_Length = Signal_Length + Kernel_Length;
	}
	else{
		Total_Length = (Piece_count - 1)*Overlap_Length + FFT_Length;
	}
	checkCudaErrors(cudaMalloc((void**)&Padded_Buffer, Total_Length * sizeof(cufftComplex)));
	checkCudaErrors(cudaMalloc((void**)&Piece_Buffer, FFT_Length * sizeof(cufftComplex)));
	checkCudaErrors(cudaMalloc((void**)&Kernel_Buffer, FFT_Length * sizeof(cufftComplex)));
	checkCudaErrors(cudaMalloc((void**)&Kernel_Fliper, Kernel_Length * sizeof(cufftComplex)));

	checkCudaErrors(cudaMemset(Padded_Buffer, 0, Total_Length * sizeof(cufftComplex)));
	checkCudaErrors(cudaMemset(Piece_Buffer, 0, FFT_Length * sizeof(cufftComplex)));
	checkCudaErrors(cudaMemset(Kernel_Buffer, 0, FFT_Length * sizeof(cufftComplex)));
	checkCudaErrors(cudaMemset(Kernel_Fliper, 0, Kernel_Length * sizeof(cufftComplex)));

	int GridSize = (Signal_Length + BlockSize - 1) / BlockSize;
	TranPositionZ << <GridSize, BlockSize >> > (Signal_Length, Signal, Kernel_Length + 1, Padded_Buffer);
	GridSize = (Kernel_Length + BlockSize - 1) / BlockSize;
	Fliper << <GridSize, BlockSize >> >(Kernel_Length, Kernel, Kernel_Fliper);
	CUDAMathematicsFoundationArithmeticNamespace::ComplexConjugate << <GridSize, BlockSize >> >(Kernel_Fliper, Kernel_Length);
	TranPosition << <GridSize, BlockSize >> > (Kernel_Length, Kernel_Fliper, 1, Kernel_Buffer);
	cufftExecC2C(Plan, Kernel_Buffer, Kernel_Buffer, CUFFT_FORWARD);//¹²éîÃ»×ö
	for (int Trans = 1; Trans <= ((Piece_count - 1)*Overlap_Length + 1); Trans += Overlap_Length)
	{
		GridSize = (FFT_Length + BlockSize - 1) / BlockSize;
		TranPositionB << <GridSize, BlockSize >> >(FFT_Length, Padded_Buffer, Trans, Piece_Buffer);
		cufftExecC2C(Plan, Piece_Buffer, Piece_Buffer, CUFFT_FORWARD);
		CUDAMathematicsFoundationArithmeticNamespace::ComplexPointwiseMultiplicationAndScale << <GridSize, BlockSize >> >(Piece_Buffer, Kernel_Buffer, FFT_Length, 1.0f / FFT_Length);
		cufftExecC2C(Plan, Piece_Buffer, Piece_Buffer, CUFFT_INVERSE);
		if (U < Piece_count - 1)
		{
			GridSize = (Overlap_Length + BlockSize - 1) / BlockSize;
			TranPositionC << <GridSize, BlockSize >> > (Overlap_Length, Piece_Buffer, Trans, Signal, FFT_Length);
		}
		else
		{
			GridSize = (The_Last + BlockSize - 1) / BlockSize;
			TranPositionE << <GridSize, BlockSize >> >(The_Last, Piece_Buffer, Overlap_Length * (Piece_count - 1), Signal, Overlap_Length, FFT_Length);
		}
		U = U + 1;
	}
	GridSize = (Signal_Length + BlockSize - 1) / BlockSize;
	TranPositionD << <GridSize, BlockSize >> >(Signal_Length, Signal, Kernel_Length, Signal);
	checkCudaErrors(cudaFree(Padded_Buffer));
	checkCudaErrors(cudaFree(Piece_Buffer));
	checkCudaErrors(cudaFree(Kernel_Buffer));
	checkCudaErrors(cudaFree(Kernel_Fliper));
}