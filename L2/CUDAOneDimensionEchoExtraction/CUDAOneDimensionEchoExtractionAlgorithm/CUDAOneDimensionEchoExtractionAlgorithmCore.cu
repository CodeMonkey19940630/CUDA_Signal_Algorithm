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
	if ((Thread_ID >= Begin_Index) && (Thread_ID <= End_Index))//ֻ��һ�������ڵ��̷߳��ϸ�Ҫ��
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
	//��������
	//CFAR_Result_Address��Ϊ0��1����
	//CFAR_Input_Absolute_Address��Ϊ��ʵֵ����
	//Count_Of_Sampling_Point_Of_MonopulseΪ�������еĳ���
	//BlockSize�鳤��
	//��Ҫ��CFAR_Result_Address���е�����ĩβ��0��������Count_Of_Sampling_Point_Of_Monopulse��BlockSize���¼�������GPU�Դ��ַ����CFAR_Result_Address�����ݸ��ƽ�����
	int GridSize = (Count_Of_Sampling_Point_Of_Monopulse / BlockSize) + 1;

	bool *CFAR_Result_Zero_Padding;//GPU
	int *Echo_Begin_End_Index_Record_GPU;//GPU
	int *Echo_Begin_End_Index_Record_CPU;//CPU
	checkCudaErrors(cudaMalloc((void **)&CFAR_Result_Zero_Padding, GridSize * BlockSize * sizeof(bool)));//GPU
	checkCudaErrors(cudaMalloc((void **)&Echo_Begin_End_Index_Record_GPU, GridSize * BlockSize * sizeof(int)));//GPU
	Echo_Begin_End_Index_Record_CPU = (int *)malloc(GridSize * BlockSize * sizeof(int));//CPU

	checkCudaErrors(cudaMemset(CFAR_Result_Zero_Padding, 0, GridSize * BlockSize * sizeof(bool)));//���µ�GPU�Դ��ַ���г�ʼ��Ϊ0��
	checkCudaErrors(cudaMemset(Echo_Begin_End_Index_Record_GPU, 0, GridSize * BlockSize * sizeof(int)));//���µ�GPU�Դ��ַ���г�ʼ��Ϊ0��
	memset(Echo_Begin_End_Index_Record_CPU, 0, GridSize * BlockSize * sizeof(int));//CPU

	checkCudaErrors(cudaMemcpy(CFAR_Result_Zero_Padding, CFAR_Result_Address, Count_Of_Sampling_Point_Of_Monopulse * sizeof(bool), cudaMemcpyDeviceToDevice));//��GPU��CFAR_Result_Address���ݸ��Ƶ�GPU��CFAR_Result_Zero_Padding��
	EchoCollection << <GridSize, BlockSize >> >(Echo_Begin_End_Index_Record_GPU, CFAR_Result_Zero_Padding, Count_Of_Sampling_Point_Of_Monopulse);//�ز�ʶ��
	//ʹ��cudaMemcpy����ʽͬ��������Ż�Ϊ��ҳ�ڴ潫�˻�ʧЧ��
	checkCudaErrors(cudaMemcpy(Echo_Begin_End_Index_Record_CPU, Echo_Begin_End_Index_Record_GPU, GridSize * BlockSize * sizeof(int), cudaMemcpyDeviceToHost));//��Echo_Begin_End_Index_Record���ݸ��ƻ������ˣ������Echo_Begin_End_Index_Record_List�С�
	//��CPU��ѹ��Echo_Begin_End_Index_Record_CPU��
	std::vector<int> Echo_Begin_End_Index_Record_Compress_List;
	for (int Index = 0; Index < GridSize * BlockSize; Index++)
	{
		if (Echo_Begin_End_Index_Record_CPU[Index] != 0)
		{
			Echo_Begin_End_Index_Record_Compress_List.push_back(Echo_Begin_End_Index_Record_CPU[Index]);
		}
	}
	//pair��⣬��Echo_Count�ǲ��Ǵ���0��ż��
	int Echo_Count = 0;
	Echo_Count = Echo_Begin_End_Index_Record_Compress_List.size();
	if (Echo_Count > 0)
	{
		if ((Echo_Count % 2) != 0)
		{
			Echo_Begin_End_Index_Record_Compress_List.insert(Echo_Begin_End_Index_Record_Compress_List.begin(), 0);//ֻ���׵�ַλ�õ�����Ϊ1ʱ���п���Ϊ������
			Echo_Count = Echo_Count + 1;
		}
		if (Echo_Count > 0)
		{	//��ʼ�����ɶԷų���
			for (auto Index = 0; Index < Echo_Count; Index += 2)
			{
				Echo_Begin_End_Index_Pair_Result.push_back(std::make_pair(Echo_Begin_End_Index_Record_Compress_List[Index], Echo_Begin_End_Index_Record_Compress_List[Index + 1]));
				//����Ѱ�Ҵ�С�ĺ˺�����
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
				checkCudaErrors(cudaMemcpy(CFAR_Input_Absolute_Address_CPU, CFAR_Input_Absolute_Address, Count_Of_Sampling_Point_Of_Monopulse * sizeof(float), cudaMemcpyDeviceToHost));//��GPU��CFAR_Result_Address���ݸ��Ƶ�GPU��CFAR_Result_Zero_Padding��
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
			//�����ж�����û�лز�
			printf("Still without any Echo!\n");
		}
	}
	else
	{
		//ѹ��û�лز�
		printf("Without any Echo!\n");
	}
}
