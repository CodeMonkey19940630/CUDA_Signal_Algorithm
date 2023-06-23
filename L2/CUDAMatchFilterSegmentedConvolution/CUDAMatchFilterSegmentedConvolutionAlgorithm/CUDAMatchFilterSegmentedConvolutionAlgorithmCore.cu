#include "CUDAMatchFilterSegmentedConvolutionAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"
int CalculateSectionLength(int N) 
{
	// calculate section length M that M + N - 1 is powers of 2 and M is close to N
	int fFFT_Length = 1;
	while ((2 * N) > fFFT_Length)
	{
		fFFT_Length *= 2;
	}
	return fFFT_Length + 1 - N;
}

int CalculatePaddedLength(int M, int Input_Data_Size)
{
	// calculate the padded length of long signal that the padded length is multiplies of M
	int fFFT_Length = 0;
	while (fFFT_Length < Input_Data_Size)
	{
		fFFT_Length += M;
	}
	return fFFT_Length;
}

/*
CORE FUNCTIONS that perform segmented convolution using overlap-add/overlap-save method
Four versions of segmented convolution include: overlap-add, in-place version of overlap-add
(without creating a buffer to store output), overlap-save, in-place version of overlap-save
*/
/*
The following comments of the use of parameters apply to all four versions
of segmented convolution function
@param [in] Plan
cufft plan used for fft operations of each segmented convolution 每一分段卷积FFT所需句饼
@param [in] Input_Long_Signal
input array of long signal to be conducted convolution 进行分段卷积的长信号地址
@param [in] Input_Short_Signal
input array of short signal to be conducted convolution 进行分段卷积的短信号地址
@param [out] y
output array that stores convolution result 存储卷积结果的地址
@param [in] Input_Long_Signal_Size
size of data elements of long signal (after zero-padding to be multiplies of M) 长信号数据元素长度
@param [in] y_len
size of data elements of output array 卷积输出结果数据元素长度
@param [in] M
size of each section for sectioned convolution 分段卷积每一段数据元素长度
@param [in] N
size of data elements for short signal 短信号数据元素长度
@param [in] scaleFactor
parameter used in ComplexPointwiseMulAndScale kernel function
*/
void ConvolutionOverlapSaveInPlace(cufftHandle Plan, cufftComplex *Input_Long_Signal, cufftComplex *Input_Short_Signal, int Input_Long_Signal_Size, int M, int N, float Scale_Factor)
{
	// allocate GPU memory for buffer
	cufftComplex *Buffer;
	checkCudaErrors(cudaMalloc(&Buffer, (M + N - 1) * sizeof(cufftComplex)));
	// copy the first section of x to buffer
	// set the first N - 1 elements to 0
	checkCudaErrors(cudaMemset(Buffer, 0, (N - 1) * sizeof(cufftComplex)));
	checkCudaErrors(cudaMemcpy(Buffer + N - 1, Input_Long_Signal, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
	// set block parameters
	// ALERT: assume N + M - 1 is multiplies of 32 (launch integral warps)
	int BlockSize = ((N + M - 1) > 512) ? 512 : N + M - 1;
	int GridSize = ((N + M - 1) % BlockSize == 0) ? (N + M - 1) / BlockSize : (N + M - 1) / BlockSize + 1;
	int Start = -N + 1;
	int End = Input_Long_Signal_Size;
	int Stride = M;
	// partition array x into M-length sub-arrays (in overlap-save fashion) and perform convolution separately
	cufftResult Result;
	for (int Index = Start; Index < End; Index += Stride)
	{

		// perform FFT operation on buffer (which stores each section of x per iteration)
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_FORWARD);
		if (Result != CUFFT_SUCCESS) {
			printf("Error with in-place FFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}

		// perform convolution on each section
		CUDAMathematicsFoundationArithmeticNamespace::ComplexPointwiseMultiplicationAndScale << <GridSize, BlockSize >> >(Buffer, Input_Short_Signal, N + M - 1, Scale_Factor);

		// perform IFFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_INVERSE);
		if (Result != CUFFT_SUCCESS)
		{
			printf("Error with in-place IFFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}

		// copy partial array of x (next section) to buffer
		checkCudaErrors(cudaMemcpy(Buffer, Input_Long_Signal + Index + M, (M + N - 1) * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));

		// copy partial Result to output array
		if ((Index + M + N - 1) >= (Input_Long_Signal_Size + N - 1))
		{
			checkCudaErrors(cudaMemcpy(Input_Long_Signal + Index + N - 1, Buffer + N - 1, (Input_Long_Signal_Size - Index) * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
		else
		{
			checkCudaErrors(cudaMemcpy(Input_Long_Signal + Index + N - 1, Buffer + N - 1, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
	}
	// clean buffer data
	checkCudaErrors(cudaFree(Buffer));
}


void ConvolutionOverlapSave(cufftHandle Plan, cufftComplex *Input_Long_Signal, cufftComplex *Input_Short_Signal, cufftComplex *Output_Signal, int Input_Long_Signal_Size, int Output_Signal_Size, int M, int N, float Scale_Factor)
{
	// allocate GPU memory for buffers
	cufftComplex *Buffer;
	checkCudaErrors(cudaMalloc(&Buffer, (M + N - 1) * sizeof(cufftComplex)));
	// set block parameters
	// ALERT: assume N + M - 1 is multiplies of 32 (launch integral warps)
	unsigned BlockSize = ((N + M - 1) > 512) ? 512 : N + M - 1;
	unsigned GridSize = ((N + M - 1) % BlockSize == 0) ? (N + M - 1) / BlockSize : ((N + M - 1) / BlockSize + 1);
	int Start = -N + 1;
	int End = Input_Long_Signal_Size;
	int Stride = M;
	// partition array x into M-length sub-arrays (in overlap-save fashion) and perform convolution separately
	cufftResult Result;
	for (int Index = Start; Index < End; Index += Stride)
	{
		// copy partial array of x to buffer
		if (Index < 0)
		{
			// set first N - 1 elements to zero for the first section
			checkCudaErrors(cudaMemset(Buffer, 0, (N - 1) * sizeof(cufftComplex)));
			// copy the last M elements to the buffer
			checkCudaErrors(cudaMemcpy(Buffer + N - 1, Input_Long_Signal, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
		else if ((Index + M + N - 1) >= Input_Long_Signal_Size)
		{
			// set the buffer to zero for the last section
			checkCudaErrors(cudaMemset(Buffer, 0, (M + N - 1) * sizeof(cufftComplex)));
			// copy in-array elements to the buffer
			checkCudaErrors(cudaMemcpy(Buffer, Input_Long_Signal + Index, (Input_Long_Signal_Size - Index) * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
		else
		{
			checkCudaErrors(cudaMemcpy(Buffer, Input_Long_Signal + Index, (M + N - 1) * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
		// perform FFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_FORWARD);
		if (Result != CUFFT_SUCCESS) 
		{
			printf("Error with in-place FFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}
		// perform convolution on each section
		CUDAMathematicsFoundationArithmeticNamespace::ComplexPointwiseMultiplicationAndScale << <GridSize, BlockSize >> >(Buffer, Input_Short_Signal, N + M - 1, Scale_Factor);
		// perform IFFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_INVERSE);
		if (Result != CUFFT_SUCCESS)
		{
			printf("Error with in-place IFFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}

		// copy partial Result to output array
		if ((Index + M + N - 1) >= Output_Signal_Size)
		{
			checkCudaErrors(cudaMemcpy(Output_Signal + Index + N - 1, Buffer + N - 1, (Output_Signal_Size - Index - N + 1) * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
		else
		{
			checkCudaErrors(cudaMemcpy(Output_Signal + Index + N - 1, Buffer + N - 1, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		}
	}
	// clean buffer data
	checkCudaErrors(cudaFree(Buffer));
}


void ConvolutionOverlapAdd(cufftHandle Plan, cufftComplex *Input_Long_Signal, cufftComplex *Input_Short_Signal, cufftComplex *Output_Signal, int Input_Long_Signal_Size, int Output_Signal_Size, int M, int N, float Scale_Factor)
{
	// allocate GPU memory for buffer
	cufftComplex *Buffer;
	checkCudaErrors(cudaMalloc(&Buffer, (N + M - 1) * sizeof(cufftComplex)));
	// set output array values to zero
	checkCudaErrors(cudaMemset(Output_Signal, 0, Output_Signal_Size * sizeof(cufftComplex)));
	// set block parameters
	// ALERT: assume N + M - 1 is multiplies of 32 (launch integral warps)
	int BlockSize = ((N + M - 1) > 512) ? 512 : N + M - 1;
	int GridSize = ((N + M - 1) % BlockSize == 0) ? (N + M - 1) / BlockSize : (N + M - 1) / BlockSize + 1;
	// partition array x into M-length sub-arrays and perform convolution separately
	cufftResult Result;
	for (int Index = 0; Index < Input_Long_Signal_Size; Index += M)
	{
		// clear the buffer before fft operation per iteration
		// copy each section from input signal to buffer
		checkCudaErrors(cudaMemset(Buffer, 0, (M + N - 1) * sizeof(cufftComplex)));
		checkCudaErrors(cudaMemcpy(Buffer, Input_Long_Signal + Index, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
		// perform FFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_FORWARD);
		if (Result != CUFFT_SUCCESS)
		{
			printf("Error with in-place FFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}
		// perform convolution on each section
		CUDAMathematicsFoundationArithmeticNamespace::ComplexPointwiseMultiplicationAndScale << <GridSize, BlockSize >> >(Buffer, Input_Short_Signal, N + M - 1, Scale_Factor);
		// perform IFFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_INVERSE);
		if (Result != CUFFT_SUCCESS)
		{
			printf("Error with in-place IFFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}
		// add partial Result (N + M - 1 elements) to the output array
		// perform overlap-add
		CUDAMathematicsFoundationArithmeticNamespace::ComplexArrayAddition << <GridSize, BlockSize >> >(Output_Signal + Index, Buffer, N + M - 1);

	}
	// clean buffer data
	checkCudaErrors(cudaFree(Buffer));
}


void ConvolutionOverlapAddInPlace(cufftHandle Plan, cufftComplex *Input_Long_Signal, cufftComplex *Input_Short_Signal, int Input_Long_Signal_Size, int M, int N, float Scale_Factor)
{
	// allocate GPU memory for buffer
	cufftComplex *Buffer;
	checkCudaErrors(cudaMalloc(&Buffer, (N + M - 1) * sizeof(cufftComplex)));
	// clear the buffer and copy the first M-length section of input array to the buffer
	checkCudaErrors(cudaMemset(Buffer, 0, (M + N - 1) * sizeof(cufftComplex)));
	checkCudaErrors(cudaMemcpy(Buffer, Input_Long_Signal, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
	// set the first M-length section of input array to 0
	checkCudaErrors(cudaMemset(Input_Long_Signal, 0, M*sizeof(cufftComplex)));
	// set block parameters
	// ALERT: assume N + M - 1 is multiplies of 32 (launch integral warps)
	int BlockSize = ((N + M - 1) > 512) ? 512 : N + M - 1;
	int GridSize = ((N + M - 1) % BlockSize == 0) ? (N + M - 1) / BlockSize : ((N + M - 1) / BlockSize + 1);
	// partition array x into M-length sub-arrays and perform convolution separately
	cufftResult Result;
	for (int Index = 0; Index < Input_Long_Signal_Size; Index += M)
	{

		// perform FFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_FORWARD);
		if (Result != CUFFT_SUCCESS)
		{
			printf("Error with in-place FFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}
		// perform convolution on each section
		CUDAMathematicsFoundationArithmeticNamespace::ComplexPointwiseMultiplicationAndScale << <GridSize, BlockSize >> >(Buffer, Input_Short_Signal, N + M - 1, Scale_Factor);
		// perform IFFT operation on each section
		Result = cufftExecC2C(Plan, Buffer, Buffer, CUFFT_INVERSE);
		if (Result != CUFFT_SUCCESS)
		{
			printf("Error with in-place IFFT operation on section of long signal. cuFFT Error code in %dth iteration: %d\n", Index, Result);
			return;
		}
		// perform boundary check
		if ((Index + M) < Input_Long_Signal_Size)
		{
			// clear the buffer before fft operation per iteration
			// copy next section from input array to buffer
			checkCudaErrors(cudaMemset(Buffer, 0, (M + N - 1) * sizeof(cufftComplex)));
			checkCudaErrors(cudaMemcpy(Buffer, Input_Long_Signal + Index + M, M * sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
			// set next section of input array to 0
			checkCudaErrors(cudaMemset(Input_Long_Signal + Index + M, 0, M * sizeof(cufftComplex)));
		}
		// add partial Result (N + M - 1 elements) to the output array
		// perform overlap-add
		CUDAMathematicsFoundationArithmeticNamespace::ComplexArrayAddition << <GridSize, BlockSize >> >(Input_Long_Signal + Index, Buffer, N + M - 1);

	}
	checkCudaErrors(cudaFree(Buffer));
}



void CUDAMatchFilterSegmentedConvolutionAlgorithmCore(cufftHandle Plan, float2* Signal_Padded_G, float2 *Kernel_Padded_Result_G,  int Kenel_Padded_Size,  int Pulse_Size, float Scale_Factor)
{
	//paddedsize：快时间维长信号的长度，补0后的值
	//kenel_padded_size：有效的发射信号脉冲宽度的长度，短信号，实际上应该是脉冲宽度对应的采样数
	//pulsesize：快时间维长信号的长度，没有补0的值

	// calculate the section length for input longer signal and output array
	int IsectionLength = CalculateSectionLength(Kenel_Padded_Size);
	// calculate the approximate length of input signal that equals to multiplies of IsectionLength 
	int Signal_padded_G_padded_len = CalculatePaddedLength(IsectionLength, Pulse_Size);
	// perform FFT operation on kernel_padded_result_G_fft
	cufftResult Result = cufftExecC2C(Plan, Kernel_Padded_Result_G, Kernel_Padded_Result_G, CUFFT_FORWARD);
	if (Result != CUFFT_SUCCESS)
	{  // check if cufft plan is successfully destroyed
		printf("Error with in-place FFT operation on short signal. cuFFT Error code: %d\n", Result);
		return;
	}

	// uncomment the code if using out-of-place version of segmented convolution functions
	// create a buffer that stores Signal_Padded_G data and perform zero-padding
	/*
	cufftComplex* signal_padded_G_copy;
	unsigned signal_padded_G_copy_len = calcPaddedLength(IsectionLength, Pulse_Size);
	checkCudaErrors(cudaMalloc(&signal_padded_G_copy, signal_padded_G_copy_len*sizeof(cufftComplex)));
	checkCudaErrors(cudaMemset(signal_padded_G_copy, 0, signal_padded_G_copy_len *sizeof(cufftComplex)));
	checkCudaErrors(cudaMemcpy(signal_padded_G_copy, signal_padded_G, Pulse_Size*sizeof(cufftComplex), cudaMemcpyDeviceToDevice));
	*/

	// perform sectioned convolution using overlap-add/overlap-save
	/*
	ConvolutionOverlapAdd(plan, signal_padded_G_copy, Kernel_Padded_Result_G, (cufftComplex *)signal_padded_G, signal_padded_G_copy_len, signal_padded_G_copy_len + Kenel_Padded_Size - 1, isectionLength, Kenel_Padded_Size, Scale_Factor);
	ConvolutionOverlapSave(plan, signal_padded_G_copy, Kernel_Padded_Result_G, (cufftComplex *)signal_padded_G, signal_padded_G_copy_len, signal_padded_G_copy_len + Kenel_Padded_Size - 1, isectionLength, Kenel_Padded_Size, Scale_Factor);
	*/
	ConvolutionOverlapAddInPlace(Plan, Signal_Padded_G, Kernel_Padded_Result_G, Signal_padded_G_padded_len, IsectionLength, Kenel_Padded_Size, Scale_Factor);
	/*
	ConvolutionOverlapSaveInPlace(Plan, Signal_Padded_G, Kernel_Padded_Result_G, Signal_padded_G_padded_len, IsectionLength, Kenel_Padded_Size, Scale_Factor);
	*/
}
