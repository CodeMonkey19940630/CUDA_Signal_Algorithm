#include "CUDAOneDimensionEchoExtractionAlgorithmCore.cuh"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"

__device__ __forceinline__ float AtomicMinFloat(float* addr, float value) {
	float old;
	old = !signbit(value) ? __int_as_float(atomicMin((int*)addr, __float_as_int(value))) :
		__uint_as_float(atomicMax((unsigned int*)addr, __float_as_uint(value)));

	return old;
}

__device__ __forceinline__ float AtomicMaxFloat(float* addr, float value) {
	float old;
	old = !signbit(value) ? __int_as_float(atomicMax((int*)addr, __float_as_int(value))) :
		__uint_as_float(atomicMin((unsigned int*)addr, __float_as_uint(value)));

	return old;
}

__global__ void FindMax(float *Max_Temporary_Index, float *CFAR_Input_Absolute_Address, int Begin_Index, int End_Index)
{
	int Thread_ID = blockDim.x * blockIdx.x + threadIdx.x;
	if ((Thread_ID >= Begin_Index) && (Thread_ID <= End_Index))//只有一个区域内的线程符合该要求。
	{
		AtomicMaxFloat(Max_Temporary_Index, CFAR_Input_Absolute_Address[Thread_ID]);
	}
}

__global__ void EchoCollection(int *Echo_Begin_End_Index_Record, bool *CFAR_Result_Zero_Padding, int Count_Of_Sampling_Point_Of_Monopulse)
{
	int Thread_ID = blockDim.x * blockIdx.x + threadIdx.x;
	if (Thread_ID < Count_Of_Sampling_Point_Of_Monopulse)
	{
		if ((CFAR_Result_Zero_Padding[Thread_ID] == 0) && (CFAR_Result_Zero_Padding[Thread_ID + 1] == 1))
		{
			Echo_Begin_End_Index_Record[Thread_ID] = Thread_ID + 1;
		}
		if ((CFAR_Result_Zero_Padding[Thread_ID] == 1) && (CFAR_Result_Zero_Padding[Thread_ID + 1] == 0))
		{
			Echo_Begin_End_Index_Record[Thread_ID] = Thread_ID;
		}

	}
}

void CUDAOneDimensionEchoExtractionAlgorithmCore(std::vector<std::pair<int, int>> &Echo_Begin_End_Index_Pair_Result, std::vector<std::pair<int, float>> &Max_Result, bool *CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse, int BlockSize)
{
	//参数解释
	//CFAR_Result_Address中为0，1序列
	//CFAR_Input_Absolute_Address中为真实值序列
	//Count_Of_Sampling_Point_Of_Monopulse为以上序列的长度
	//BlockSize块长度
	//因要对CFAR_Result_Address，中的内容末尾补0所以依赖Count_Of_Sampling_Point_Of_Monopulse与BlockSize从新计算申请GPU显存地址并将CFAR_Result_Address，内容复制进来。
	int GridSize = (Count_Of_Sampling_Point_Of_Monopulse / BlockSize) + 1;

	bool *CFAR_Result_Zero_Padding;//GPU
	int *Echo_Begin_End_Index_Record_GPU;//GPU
	int *Echo_Begin_End_Index_Record_CPU;//CPU
	checkCudaErrors(cudaMalloc((void **)&CFAR_Result_Zero_Padding, GridSize * BlockSize * sizeof(bool)));//GPU
	checkCudaErrors(cudaMalloc((void **)&Echo_Begin_End_Index_Record_GPU, GridSize * BlockSize * sizeof(int)));//GPU
	Echo_Begin_End_Index_Record_CPU = (int *)malloc(GridSize * BlockSize * sizeof(int));//CPU

	checkCudaErrors(cudaMemset(CFAR_Result_Zero_Padding, 0, GridSize * BlockSize * sizeof(bool)));//对新的GPU显存地址进行初始化为0。
	checkCudaErrors(cudaMemset(Echo_Begin_End_Index_Record_GPU, 0, GridSize * BlockSize * sizeof(int)));//对新的GPU显存地址进行初始化为0。
	memset(Echo_Begin_End_Index_Record_CPU, 0, GridSize * BlockSize * sizeof(int));//CPU

	checkCudaErrors(cudaMemcpy(CFAR_Result_Zero_Padding, CFAR_Result_Address, Count_Of_Sampling_Point_Of_Monopulse * sizeof(bool), cudaMemcpyDeviceToDevice));//将GPU中CFAR_Result_Address数据复制到GPU中CFAR_Result_Zero_Padding。
	EchoCollection << <GridSize, BlockSize >> >(Echo_Begin_End_Index_Record_GPU, CFAR_Result_Zero_Padding, Count_Of_Sampling_Point_Of_Monopulse);//回波识别
	//使用cudaMemcpy的隐式同步，如果优化为锁页内存将退化失效。
	checkCudaErrors(cudaMemcpy(Echo_Begin_End_Index_Record_CPU, Echo_Begin_End_Index_Record_GPU, GridSize * BlockSize * sizeof(int), cudaMemcpyDeviceToHost));//将Echo_Begin_End_Index_Record数据复制回主机端，存放在Echo_Begin_End_Index_Record_List中。
	//在CPU端压缩Echo_Begin_End_Index_Record_CPU。
	std::vector<int> Echo_Begin_End_Index_Record_Compress_List;
	for (int Index = 0; Index < GridSize * BlockSize; Index++)
	{
		if (Echo_Begin_End_Index_Record_CPU[Index] != 0)
		{
			Echo_Begin_End_Index_Record_Compress_List.push_back(Echo_Begin_End_Index_Record_CPU[Index]);
		}
	}
	//pair检测，看Echo_Count是不是大于0的偶数
	int Echo_Count = 0;
	Echo_Count = Echo_Begin_End_Index_Record_Compress_List.size();
	if (Echo_Count > 0)
	{
		if ((Echo_Count % 2) != 0)
		{
			Echo_Begin_End_Index_Record_Compress_List.insert(Echo_Begin_End_Index_Record_Compress_List.begin(), 0);//只有首地址位置的内容为1时才有可能为奇数。
			Echo_Count = Echo_Count + 1;
		}
		if (Echo_Count > 0)
		{	//开始结束成对放出。
			for (auto Index = 0; Index < Echo_Count; Index += 2)
			{
				Echo_Begin_End_Index_Pair_Result.push_back(std::make_pair(Echo_Begin_End_Index_Record_Compress_List[Index], Echo_Begin_End_Index_Record_Compress_List[Index + 1]));
				//调用寻找大小的核函数。
				float * Max_Temporary_GPU;
				float *Max_Temporary_CPU;
				checkCudaErrors(cudaMalloc((void **)&Max_Temporary_GPU, 1 * sizeof(float)));
				checkCudaErrors(cudaMemset(Max_Temporary_GPU, 0, 1 * sizeof(float)));
				Max_Temporary_CPU = (float *)malloc(1 * sizeof(float));//CPU
				memset(Max_Temporary_CPU, 0, 1 * sizeof(float));//CPU
				FindMax << <GridSize, BlockSize >> >(Max_Temporary_GPU, CFAR_Input_Absolute_Address, Echo_Begin_End_Index_Record_Compress_List[Index], Echo_Begin_End_Index_Record_Compress_List[Index + 1]);
				checkCudaErrors(cudaMemcpy(Max_Temporary_CPU, Max_Temporary_GPU, 1 * sizeof(float), cudaMemcpyDeviceToHost));
				float Max_Value = 0.0;
				int Max_Index = 0;
				float * CFAR_Input_Absolute_Address_CPU = (float *)malloc(Count_Of_Sampling_Point_Of_Monopulse * sizeof(float));//CPU
				checkCudaErrors(cudaMemcpy(CFAR_Input_Absolute_Address_CPU, CFAR_Input_Absolute_Address, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float), cudaMemcpyDeviceToHost));//将GPU中CFAR_Result_Address数据复制到GPU中CFAR_Result_Zero_Padding。
				for (int Index = Echo_Begin_End_Index_Record_Compress_List[Index]; Index <= Echo_Begin_End_Index_Record_Compress_List[Index + 1]; Index++)
				{
					if (CFAR_Input_Absolute_Address_CPU[Index] > Max_Value)
					{
						Max_Value = CFAR_Input_Absolute_Address_CPU[Index];
						Max_Index = Index;
					}
				}
				Max_Result.push_back(std::make_pair(Max_Index, Max_Temporary_CPU[0]));
			}
		}
		else
		{
			//还是判定依旧没有回波
			printf("Still without any Echo!\n");
		}
	}
	else
	{
		//压根没有回波
		printf("Without any Echo!\n");
	}
}
