#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <utility>
//对外暴露void CUDAEchoSignalGeneratorAlgorithmCore()核函数,参数待定。
extern void CUDAOneDimensionEchoExtractionAlgorithmCore(std::vector<std::pair<int, int>> &Echo_Begin_End_Index_Pair_Result, std::vector<std::pair<int, float>> &Max_Result, bool *CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse, int BlockSize);

