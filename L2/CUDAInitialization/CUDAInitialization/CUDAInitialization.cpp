// CUDAInitialization.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDAInitialization.h"
namespace CUDAInitializationNamespace
{
	CUDAInitialization::CUDAInitialization()
	{
		this->Kernel_Size_D1 = 0;
		this->Kernel_Size_D2 = 0;
		this->Kernel_Size_D3 = 0;
		this->Kernel_Float_In_GPU = nullptr;
		this->Kernel_Float2_In_GPU = nullptr;

		this->Kernel_Padded_Size_D1 = 0;
		this->Kernel_Padded_Size_D2 = 0;
		this->Kernel_Padded_Size_D3 = 0;
		this->Kernel_Padded_Float_In_GPU = nullptr;
		this->Kernel_Padded_Float2_In_GPU = nullptr;

		this->Kernel_Padded_Result_Size_D1 = 0;
		this->Kernel_Padded_Result_Size_D2 = 0;
		this->Kernel_Padded_Result_Size_D3 = 0;
		this->Kernel_Padded_Result_Float_In_GPU = nullptr;
		this->Kernel_Padded_Result_Float2_In_GPU = nullptr;

		this->Signal_Size_D1 = 0;
		this->Signal_Size_D2 = 0;
		this->Signal_Size_D3 = 0;
		this->Signal_Float_In_GPU = nullptr;
		this->Signal_Float2_In_GPU = nullptr;

		this->Signal_Padded_Size_D1 = 0;
		this->Signal_Padded_Size_D2 = 0;
		this->Signal_Padded_Size_D3 = 0;
		this->Signal_Padded_Float_In_GPU = nullptr;
		this->Signal_Padded_Float2_In_GPU = nullptr;

		this->Signal_Padded_Result_Size_D1 = 0;
		this->Signal_Padded_Result_Size_D2 = 0;
		this->Signal_Padded_Result_Size_D3 = 0;
		this->Signal_Padded_Result_Float_In_GPU = nullptr;
		this->Signal_Padded_Result_Float2_In_GPU = nullptr;

		/*this->Initialization_Function_List.push_back({ "InitializeKernelFloat_In_GPU", &CUDAInitialization::InitializeKernelFloat_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeKernelFloat2_In_GPU", &CUDAInitialization::InitializeKernelFloat2_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeKernelPaddedFloat_In_GPU", &CUDAInitialization::InitializeKernelPaddedFloat_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeKernelPaddedFloat2_In_GPU", &CUDAInitialization::InitializeKernelPaddedFloat2_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeKernelPaddedResultFloat_In_GPU", &CUDAInitialization::InitializeKernelPaddedResultFloat_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeKernelPaddedResultFloat2_In_GPU", &CUDAInitialization::InitializeKernelPaddedResultFloat2_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeSignalFloat_In_GPU", &CUDAInitialization::InitializeSignalFloat_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeSignalFloat2_In_GPU", &CUDAInitialization::InitializeSignalFloat2_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeSignalPaddedFloat_In_GPU", &CUDAInitialization::InitializeSignalPaddedFloat_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeSignalPaddedFloat2_In_GPU", &CUDAInitialization::InitializeSignalPaddedFloat2_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeSignalPaddedResultFloat_In_GPU", &CUDAInitialization::InitializeSignalPaddedResultFloat_In_GPU });
		this->Initialization_Function_List.push_back({ "InitializeSignalPaddedResultFloat2_In_GPU", &CUDAInitialization::InitializeSignalPaddedResultFloat2_In_GPU });

		this->Copy_Float_To_Float_Function_List.push_back({ "CopyKernelFloatDataFromHostToDecive", &CUDAInitialization::CopyKernelFloatDataFromHostToDecive });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopyKernelFloatDataFromDeciveToHost", &CUDAInitialization::CopyKernelFloatDataFromDeciveToHost });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopyKernelPaddedFloatDataFromHostToDecive", &CUDAInitialization::CopyKernelPaddedFloatDataFromHostToDecive });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopyKernelPaddedFloatDataFromDeciveToHost", &CUDAInitialization::CopyKernelPaddedFloatDataFromDeciveToHost });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopyKernelPaddedResultFloatDataFromHostToDecive", &CUDAInitialization::CopyKernelPaddedResultFloatDataFromHostToDecive });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopyKernelPaddedResultFloatDataFromDeciveToHost", &CUDAInitialization::CopyKernelPaddedResultFloatDataFromDeciveToHost });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopySignalFloatDataFromHostToDecive", &CUDAInitialization::CopySignalFloatDataFromHostToDecive });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopySignalFloatDataFromDeciveToHost", &CUDAInitialization::CopySignalFloatDataFromDeciveToHost });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopySignalPaddedFloatDataFromHostToDecive", &CUDAInitialization::CopySignalPaddedFloatDataFromHostToDecive });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopySignalPaddedFloatDataFromDeciveToHost", &CUDAInitialization::CopySignalPaddedFloatDataFromDeciveToHost });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopySignalPaddedResultFloatDataFromHostToDecive", &CUDAInitialization::CopySignalPaddedResultFloatDataFromHostToDecive });
		this->Copy_Float_To_Float_Function_List.push_back({ "CopySignalPaddedResultFloatDataFromDeciveToHost", &CUDAInitialization::CopySignalPaddedResultFloatDataFromDeciveToHost });

		this->Copy_Complex_To_Float2_Function_List.push_back({ "CopyKernelFloat2DataFromHostToDecive", &CUDAInitialization::CopyKernelFloat2DataFromHostToDecive });
		this->Copy_Float2_To_Complex_Function_List.push_back({ "CopyKernelFloat2DataFromDeciveToHost", &CUDAInitialization::CopyKernelFloat2DataFromDeciveToHost });
		this->Copy_Complex_To_Float2_Function_List.push_back({ "CopyKernelPaddedFloat2DataFromHostToDecive", &CUDAInitialization::CopyKernelPaddedFloat2DataFromHostToDecive });
		this->Copy_Float2_To_Complex_Function_List.push_back({ "CopyKernelPaddedFloat2DataFromDeciveToHost", &CUDAInitialization::CopyKernelPaddedFloat2DataFromDeciveToHost });
		this->Copy_Complex_To_Float2_Function_List.push_back({ "CopyKernelPaddedResultFloat2DataFromHostToDecive", &CUDAInitialization::CopyKernelPaddedResultFloat2DataFromHostToDecive });
		this->Copy_Float2_To_Complex_Function_List.push_back({ "CopyKernelPaddedResultFloat2DataFromDeciveToHost", &CUDAInitialization::CopyKernelPaddedResultFloat2DataFromDeciveToHost });
		this->Copy_Complex_To_Float2_Function_List.push_back({ "CopySignalFloat2DataFromHostToDecive", &CUDAInitialization::CopySignalFloat2DataFromHostToDecive });
		this->Copy_Float2_To_Complex_Function_List.push_back({ "CopySignalFloat2DataFromDeciveToHost", &CUDAInitialization::CopySignalFloat2DataFromDeciveToHost });
		this->Copy_Complex_To_Float2_Function_List.push_back({ "CopySignalPaddedFloat2DataFromHostToDecive", &CUDAInitialization::CopySignalPaddedFloat2DataFromHostToDecive });
		this->Copy_Float2_To_Complex_Function_List.push_back({ "CopySignalPaddedFloat2DataFromDeciveToHost", &CUDAInitialization::CopySignalPaddedFloat2DataFromDeciveToHost });
		this->Copy_Complex_To_Float2_Function_List.push_back({ "CopySignalPaddedResultFloat2DataFromHostToDecive", &CUDAInitialization::CopySignalPaddedResultFloat2DataFromHostToDecive });
		this->Copy_Float2_To_Complex_Function_List.push_back({ "CopySignalPaddedResultFloat2DataFromDeciveToHost", &CUDAInitialization::CopySignalPaddedResultFloat2DataFromDeciveToHost });*/
	}
	CUDAInitialization::~CUDAInitialization()
	{
		//***************************************************************
		if (this->Kernel_Float_In_CPU != nullptr)
		{
			free(this->Kernel_Float_In_CPU);
		}
		if (this->Kernel_Float2_In_CPU != nullptr)
		{
			free(this->Kernel_Float2_In_CPU);
		}
		if (this->Kernel_Float_In_GPU != nullptr)
		{
			cudaFree(this->Kernel_Float_In_GPU);
		}
		if (this->Kernel_Float2_In_GPU != nullptr)
		{
			cudaFree(this->Kernel_Float2_In_GPU);
		}
		//***************************************************************
		if (this->Kernel_Padded_Float_In_CPU != nullptr)
		{
			free(this->Kernel_Padded_Float_In_CPU);
		}
		if (this->Kernel_Padded_Float2_In_CPU != nullptr)
		{
			free(this->Kernel_Padded_Float2_In_CPU);
		}
		if (this->Kernel_Padded_Float_In_GPU != nullptr)
		{
			cudaFree(this->Kernel_Padded_Float_In_GPU);
		}
		if (this->Kernel_Padded_Float2_In_GPU != nullptr)
		{
			cudaFree(this->Kernel_Padded_Float2_In_GPU);
		}
		//***************************************************************
		if (this->Kernel_Padded_Result_Float_In_CPU != nullptr)
		{
			free(this->Kernel_Padded_Result_Float_In_CPU);
		}
		if (this->Kernel_Padded_Result_Float2_In_CPU != nullptr)
		{
			free(this->Kernel_Padded_Result_Float2_In_CPU);
		}
		if (this->Kernel_Padded_Result_Float_In_GPU != nullptr)
		{
			cudaFree(this->Kernel_Padded_Result_Float_In_GPU);
		}
		if (this->Kernel_Padded_Result_Float2_In_GPU != nullptr)
		{
			cudaFree(this->Kernel_Padded_Result_Float2_In_GPU);
		}
		//***************************************************************
		if (this->Signal_Float_In_CPU != nullptr)
		{
			free(this->Signal_Float_In_CPU);
		}
		if (this->Signal_Float2_In_CPU != nullptr)
		{
			free(this->Signal_Float2_In_CPU);
		}
		if (this->Signal_Float_In_GPU != nullptr)
		{
			cudaFree(this->Signal_Float_In_GPU);
		}
		if (this->Signal_Float2_In_GPU != nullptr)
		{
			cudaFree(this->Signal_Float2_In_GPU);
		}
		//***************************************************************
		if (this->Signal_Padded_Float_In_CPU != nullptr)
		{
			free(this->Signal_Padded_Float_In_CPU);
		}
		if (this->Signal_Padded_Float2_In_CPU != nullptr)
		{
			free(this->Signal_Padded_Float2_In_CPU);
		}
		if (this->Signal_Padded_Float_In_GPU != nullptr)
		{
			cudaFree(this->Signal_Padded_Float_In_GPU);
		}
		if (this->Signal_Padded_Float2_In_GPU != nullptr)
		{
			cudaFree(this->Signal_Padded_Float2_In_GPU);
		}
		//***************************************************************
		if (this->Signal_Padded_Result_Float_In_CPU != nullptr)
		{
			free(this->Signal_Padded_Result_Float_In_CPU);
		}
		if (this->Signal_Padded_Result_Float2_In_CPU != nullptr)
		{
			free(this->Signal_Padded_Result_Float2_In_CPU);
		}
		if (this->Signal_Padded_Result_Float_In_GPU != nullptr)
		{
			cudaFree(this->Signal_Padded_Result_Float_In_GPU);
		}
		if (this->Signal_Padded_Result_Float2_In_GPU != nullptr)
		{
			cudaFree(this->Signal_Padded_Result_Float2_In_GPU);
		}
	}
//****************************************************************************************************************************
	void CUDAInitialization::InitializeKernelFloat_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Size_D1 = Size_X;
		this->Kernel_Size_D2 = Size_Y;
		this->Kernel_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Float_In_CPU != nullptr)
			{
				free(this->Kernel_Float_In_CPU);
			}
			this->Kernel_Float_In_CPU = (float *)malloc(Total_Size * sizeof(float));
			memset(this->Kernel_Float_In_CPU, 0, Total_Size * sizeof(float));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Size_D1 = Size_X;
		this->Kernel_Size_D2 = Size_Y;
		this->Kernel_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Float2_In_CPU != nullptr)
			{
				free(this->Kernel_Float2_In_CPU);
			}
			this->Kernel_Float2_In_CPU = (complex *)malloc(Total_Size * sizeof(complex));
			memset(this->Kernel_Float2_In_CPU,0, Total_Size * sizeof(complex));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelFloat_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Size_D1 = Size_X;
		this->Kernel_Size_D2 = Size_Y;
		this->Kernel_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Float_In_GPU != nullptr)
			{
				cudaFree(this->Kernel_Float_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Kernel_Float_In_GPU), Total_Size * sizeof(float)));
			checkCudaErrors(cudaMemset(this->Kernel_Float_In_GPU, 0, Total_Size * sizeof(float)));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Size_D1 = Size_X;
		this->Kernel_Size_D2 = Size_Y;
		this->Kernel_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Float2_In_GPU != nullptr)
			{
				cudaFree(this->Kernel_Float2_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Kernel_Float2_In_GPU), Total_Size * sizeof(float2)));
			checkCudaErrors(cudaMemset(this->Kernel_Float2_In_GPU, 0, Total_Size * sizeof(float2)));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelFloatDataFromHostToDecive(float * Destination, float * Source)
	{
		int Total_Size = this->Kernel_Size_D1 * this->Kernel_Size_D2 * this->Kernel_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy kernel float data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel float data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelFloatDataFromDeciveToHost(float * Destination, float * Source)
	{
		int Total_Size = this->Kernel_Size_D1 * this->Kernel_Size_D2 * this->Kernel_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyDeviceToHost));
			std::cout << "Copy kernel float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel float data from device to host failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelFloat2DataFromHostToDecive(float2 * Destination, complex * Source)
	{
		int Total_Size = this->Kernel_Size_D1 * this->Kernel_Size_D2 * this->Kernel_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			for (int Index = 0; Index < Total_Size; Index+=2)
			{
				Temporary[Index] = Source[Index].x;
				Temporary[Index+1] = Source[Index].y;
			}
			checkCudaErrors(cudaMemcpy(Destination, Temporary, 2 * Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy kernel float2 data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel float2 data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelFloat2DataFromDeciveToHost(complex * Destination, float2 * Source)
	{
		int Total_Size = this->Kernel_Size_D1 * this->Kernel_Size_D2 * this->Kernel_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			checkCudaErrors(cudaMemcpy(Temporary, Source, Total_Size * sizeof(float2), cudaMemcpyDeviceToHost));
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Destination[Index].x = Temporary[Index];
				Destination[Index].y = Temporary[Index+1];
			}
			std::cout << "Copy kernel float2 data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel float2 data from device to host failed!" << std::endl;
		}
	}



//****************************************************************************************************************************
	void CUDAInitialization::InitializeKernelPaddedFloat_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Size_D1 = Size_X;
		this->Kernel_Padded_Size_D2 = Size_Y;
		this->Kernel_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Float_In_CPU != nullptr)
			{
				free(this->Kernel_Padded_Float_In_CPU);
			}
			this->Kernel_Padded_Float_In_CPU = (float *)malloc(Total_Size * sizeof(float));
			memset(this->Kernel_Padded_Float_In_CPU, 0, Total_Size * sizeof(float));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelPaddedFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Size_D1 = Size_X;
		this->Kernel_Padded_Size_D2 = Size_Y;
		this->Kernel_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Float2_In_CPU != nullptr)
			{
				free(this->Kernel_Padded_Float2_In_CPU);
			}
			this->Kernel_Padded_Float2_In_CPU = (complex *)malloc(Total_Size * sizeof(complex));
			memset(this->Kernel_Padded_Float2_In_CPU, 0, Total_Size * sizeof(complex));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelPaddedFloat_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Size_D1 = Size_X;
		this->Kernel_Padded_Size_D2 = Size_Y;
		this->Kernel_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Float_In_GPU != nullptr)
			{
				cudaFree(this->Kernel_Padded_Float_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Kernel_Padded_Float_In_GPU), Total_Size * sizeof(float)));
			checkCudaErrors(cudaMemset(this->Kernel_Padded_Float_In_GPU, 0, Total_Size * sizeof(float)));
			std::cout << "Kernel padded float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Kernel padded float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelPaddedFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Size_D1 = Size_X;
		this->Kernel_Padded_Size_D2 = Size_Y;
		this->Kernel_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Float2_In_GPU != nullptr)
			{
				cudaFree(this->Kernel_Padded_Float2_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Kernel_Padded_Float2_In_GPU), Total_Size * sizeof(float2)));
			checkCudaErrors(cudaMemset(this->Kernel_Padded_Float2_In_GPU, 0, Total_Size * sizeof(float2)));
			std::cout << "Kernel padded float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Kernel padded float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedFloatDataFromHostToDecive(float * Destination, float * Source)
	{
		int Total_Size = this->Kernel_Padded_Size_D1 * this->Kernel_Padded_Size_D2 * this->Kernel_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy kernel padded float data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded float data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedFloatDataFromDeciveToHost(float * Destination, float * Source)
	{
		int Total_Size = this->Kernel_Padded_Size_D1 * this->Kernel_Padded_Size_D2 * this->Kernel_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyDeviceToHost));
			std::cout << "Copy kernel padded float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded float data from device to host failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedFloat2DataFromHostToDecive(float2 * Destination, complex * Source)
	{
		int Total_Size = this->Kernel_Padded_Size_D1 * this->Kernel_Padded_Size_D2 * this->Kernel_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Temporary[Index] = Source[Index].x;
				Temporary[Index + 1] = Source[Index].y;
			}
			checkCudaErrors(cudaMemcpy(Destination, Temporary, 2 * Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy kernel padded float2 data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded float2 data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedFloat2DataFromDeciveToHost(complex * Destination, float2 * Source)
	{
		int Total_Size = this->Kernel_Padded_Size_D1 * this->Kernel_Padded_Size_D2 * this->Kernel_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			checkCudaErrors(cudaMemcpy(Temporary, Source, Total_Size * sizeof(float2), cudaMemcpyDeviceToHost));
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Destination[Index].x = Temporary[Index];
				Destination[Index].y = Temporary[Index + 1];
			}
			std::cout << "Copy kernel padded float data2 from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded float data2 from device to host failed!" << std::endl;
		}
	}




//****************************************************************************************************************************
	void CUDAInitialization::InitializeKernelPaddedResultFloat_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Result_Size_D1 = Size_X;
		this->Kernel_Padded_Result_Size_D2 = Size_Y;
		this->Kernel_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Result_Float_In_CPU != nullptr)
			{
				free(this->Kernel_Padded_Result_Float_In_CPU);
			}
			this->Kernel_Padded_Result_Float_In_CPU = (float *)malloc(Total_Size * sizeof(float));
			memset(this->Kernel_Padded_Result_Float_In_CPU, 0, Total_Size * sizeof(float));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelPaddedResultFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Result_Size_D1 = Size_X;
		this->Kernel_Padded_Result_Size_D2 = Size_Y;
		this->Kernel_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Result_Float2_In_CPU != nullptr)
			{
				free(this->Kernel_Padded_Result_Float2_In_CPU);
			}
			this->Kernel_Padded_Result_Float2_In_CPU = (complex *)malloc(Total_Size * sizeof(complex));
			memset(this->Kernel_Padded_Result_Float2_In_CPU, 0, Total_Size * sizeof(complex));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelPaddedResultFloat_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Result_Size_D1 = Size_X;
		this->Kernel_Padded_Result_Size_D2 = Size_Y;
		this->Kernel_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Result_Float_In_GPU != nullptr)
			{
				cudaFree(this->Kernel_Padded_Result_Float_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Kernel_Padded_Result_Float_In_GPU), Total_Size * sizeof(float)));
			checkCudaErrors(cudaMemset(this->Kernel_Padded_Result_Float_In_GPU, 0, Total_Size * sizeof(float)));
			std::cout << "Kernel padded result float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Kernel padded result float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeKernelPaddedResultFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Kernel_Padded_Result_Size_D1 = Size_X;
		this->Kernel_Padded_Result_Size_D2 = Size_Y;
		this->Kernel_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Kernel_Padded_Result_Float2_In_GPU != nullptr)
			{
				cudaFree(this->Kernel_Padded_Result_Float2_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Kernel_Padded_Result_Float2_In_GPU), Total_Size * sizeof(float2)));
			checkCudaErrors(cudaMemset(this->Kernel_Padded_Result_Float2_In_GPU, 0, Total_Size * sizeof(float2)));
			std::cout << "Kernel padded result float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Kernel padded result float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedResultFloatDataFromHostToDecive(float * Destination, float * Source)
	{
		int Total_Size = this->Kernel_Padded_Result_Size_D1 * this->Kernel_Padded_Result_Size_D2 * this->Kernel_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy kernel padded result float data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded result float data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedResultFloatDataFromDeciveToHost(float * Destination, float * Source)
	{
		int Total_Size = this->Kernel_Padded_Result_Size_D1 * this->Kernel_Padded_Result_Size_D2 * this->Kernel_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyDeviceToHost));
			std::cout << "Copy kernel padded result float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded result float data from device to host failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedResultFloat2DataFromHostToDecive(float2 * Destination, complex * Source)
	{
		int Total_Size = this->Kernel_Padded_Result_Size_D1 * this->Kernel_Padded_Result_Size_D2 * this->Kernel_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Temporary[Index] = Source[Index].x;
				Temporary[Index + 1] = Source[Index].y;
			}
			checkCudaErrors(cudaMemcpy(Destination, Temporary, 2 * Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy kernel padded result float2 data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded result float2 data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopyKernelPaddedResultFloat2DataFromDeciveToHost(complex * Destination, float2 * Source)
	{
		int Total_Size = this->Kernel_Padded_Result_Size_D1 * this->Kernel_Padded_Result_Size_D2 * this->Kernel_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			checkCudaErrors(cudaMemcpy(Temporary, Source, Total_Size * sizeof(float2), cudaMemcpyDeviceToHost));
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Destination[Index].x = Temporary[Index];
				Destination[Index].y = Temporary[Index + 1];
			}
			std::cout << "Copy kernel padded result float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy kernel padded result float data from device to host failed!" << std::endl;
		}
	}




//****************************************************************************************************************************
	void CUDAInitialization::InitializeSignalFloat_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Size_D1 = Size_X;
		this->Signal_Size_D2 = Size_Y;
		this->Signal_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Float_In_CPU != nullptr)
			{
				free(this->Signal_Float_In_CPU);
			}
			this->Signal_Float_In_CPU = (float *)malloc(Total_Size * sizeof(float));
			memset(this->Signal_Float_In_CPU, 0, Total_Size * sizeof(float));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Size_D1 = Size_X;
		this->Signal_Size_D2 = Size_Y;
		this->Signal_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Float2_In_CPU != nullptr)
			{
				free(this->Signal_Float2_In_CPU);
			}
			this->Signal_Float2_In_CPU = (complex *)malloc(Total_Size * sizeof(complex));
			memset(this->Signal_Float2_In_CPU, 0, Total_Size * sizeof(complex));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalFloat_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Size_D1 = Size_X;
		this->Signal_Size_D2 = Size_Y;
		this->Signal_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Float_In_GPU != nullptr)
			{
				cudaFree(this->Signal_Float_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Signal_Float_In_GPU), Total_Size * sizeof(float)));
			checkCudaErrors(cudaMemset(this->Signal_Float_In_GPU, 0, Total_Size * sizeof(float)));
			std::cout << "Signal float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Signal float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Size_D1 = Size_X;
		this->Signal_Size_D2 = Size_Y;
		this->Signal_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Float2_In_GPU != nullptr)
			{
				cudaFree(this->Signal_Float2_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Signal_Float2_In_GPU), Total_Size * sizeof(float2)));
			checkCudaErrors(cudaMemset(this->Signal_Float2_In_GPU, 0, Total_Size * sizeof(float2)));
			std::cout << "Signal float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Signal float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalFloatDataFromHostToDecive(float * Destination, float * Source)
	{
		int Total_Size = this->Signal_Size_D1 * this->Signal_Size_D2 * this->Signal_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy signal float data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal float data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalFloatDataFromDeciveToHost(float * Destination, float * Source)
	{
		int Total_Size = this->Signal_Size_D1 * this->Signal_Size_D2 * this->Signal_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyDeviceToHost));
			std::cout << "Copy signal float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal float data from device to host failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalFloat2DataFromHostToDecive(float2 * Destination, complex * Source)
	{
		int Total_Size = this->Signal_Size_D1 * this->Signal_Size_D2 * this->Signal_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Temporary[Index] = Source[Index].x;
				Temporary[Index + 1] = Source[Index].y;
			}
			checkCudaErrors(cudaMemcpy(Destination, Temporary, 2 * Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy signal float2 data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal float2 data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalFloat2DataFromDeciveToHost(complex * Destination, float2 * Source)
	{
		int Total_Size = this->Signal_Size_D1 * this->Signal_Size_D2 * this->Signal_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			checkCudaErrors(cudaMemcpy(Temporary, Source, Total_Size * sizeof(float2), cudaMemcpyDeviceToHost));
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Destination[Index].x = Temporary[Index];
				Destination[Index].y = Temporary[Index + 1];
			}
			std::cout << "Copy signal float2 data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal float2 data from device to host failed!" << std::endl;
		}
	}




//****************************************************************************************************************************
	void CUDAInitialization::InitializeSignalPaddedFloat_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Size_D1 = Size_X;
		this->Signal_Padded_Size_D2 = Size_Y;
		this->Signal_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Float_In_CPU != nullptr)
			{
				free(this->Signal_Padded_Float_In_CPU);
			}
			this->Signal_Padded_Float_In_CPU = (float *)malloc(Total_Size * sizeof(float));
			memset(this->Signal_Padded_Float_In_CPU, 0, Total_Size * sizeof(float));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalPaddedFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Size_D1 = Size_X;
		this->Signal_Padded_Size_D2 = Size_Y;
		this->Signal_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Float2_In_CPU != nullptr)
			{
				free(this->Signal_Padded_Float2_In_CPU);
			}
			this->Signal_Padded_Float2_In_CPU = (complex *)malloc(Total_Size * sizeof(complex));
			memset(this->Signal_Padded_Float2_In_CPU, 0, Total_Size * sizeof(complex));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalPaddedFloat_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Size_D1 = Size_X;
		this->Signal_Padded_Size_D2 = Size_Y;
		this->Signal_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Float_In_GPU != nullptr)
			{
				cudaFree(this->Signal_Padded_Float_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Signal_Padded_Float_In_GPU), Total_Size * sizeof(float)));
			checkCudaErrors(cudaMemset(this->Signal_Padded_Float_In_GPU, 0, Total_Size * sizeof(float)));
			std::cout << "Signal padded float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Signal padded float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalPaddedFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Size_D1 = Size_X;
		this->Signal_Padded_Size_D2 = Size_Y;
		this->Signal_Padded_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Float2_In_GPU != nullptr)
			{
				cudaFree(this->Signal_Padded_Float2_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Signal_Padded_Float2_In_GPU), Total_Size * sizeof(float2)));
			checkCudaErrors(cudaMemset(this->Signal_Padded_Float2_In_GPU, 0, Total_Size * sizeof(float2)));
			std::cout << "Signal padded float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Signal padded float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedFloatDataFromHostToDecive(float * Destination, float * Source)
	{
		int Total_Size = this->Signal_Padded_Size_D1 * this->Signal_Padded_Size_D2 * this->Signal_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy signal float data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal float data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedFloatDataFromDeciveToHost(float * Destination, float * Source)
	{
		int Total_Size = this->Signal_Padded_Size_D1 * this->Signal_Padded_Size_D2 * this->Signal_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyDeviceToHost));
			std::cout << "Copy signal padded float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded float data from device to host failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedFloat2DataFromHostToDecive(float2 * Destination, complex * Source)
	{
		int Total_Size = this->Signal_Padded_Size_D1 * this->Signal_Padded_Size_D2 * this->Signal_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Temporary[Index] = Source[Index].x;
				Temporary[Index + 1] = Source[Index].y;
			}
			checkCudaErrors(cudaMemcpy(Destination, Temporary, 2 * Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy signal padded float2 data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded float2 data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedFloat2DataFromDeciveToHost(complex * Destination, float2 * Source)
	{
		int Total_Size = this->Signal_Padded_Size_D1 * this->Signal_Padded_Size_D2 * this->Signal_Padded_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			checkCudaErrors(cudaMemcpy(Temporary, Source, Total_Size * sizeof(float2), cudaMemcpyDeviceToHost));
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Destination[Index].x = Temporary[Index];
				Destination[Index].y = Temporary[Index + 1];
			}
			std::cout << "Copy signal padded float2 data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded float2 data from device to host failed!" << std::endl;
		}
	}



//****************************************************************************************************************************
	void CUDAInitialization::InitializeSignalPaddedResultFloat_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{

		this->Signal_Padded_Result_Size_D1 = Size_X;
		this->Signal_Padded_Result_Size_D2 = Size_Y;
		this->Signal_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Result_Float_In_CPU != nullptr)
			{
				free(this->Signal_Padded_Result_Float_In_CPU);
			}
			this->Signal_Padded_Result_Float_In_CPU = (float *)malloc(Total_Size * sizeof(float));
			memset(this->Signal_Padded_Result_Float_In_CPU, 0, Total_Size * sizeof(float));
			std::cout << "Initialize kernel float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalPaddedResultFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Result_Size_D1 = Size_X;
		this->Signal_Padded_Result_Size_D2 = Size_Y;
		this->Signal_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Result_Float2_In_CPU != nullptr)
			{
				free(this->Signal_Padded_Result_Float2_In_CPU);
			}
			this->Signal_Padded_Result_Float2_In_CPU = (complex *)malloc(Total_Size * sizeof(complex));
			memset(this->Signal_Padded_Result_Float2_In_CPU, 0, Total_Size * sizeof(complex));
			std::cout << "Initialize kernel float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Initialize kernel float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalPaddedResultFloat_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Result_Size_D1 = Size_X;
		this->Signal_Padded_Result_Size_D2 = Size_Y;
		this->Signal_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Result_Float_In_GPU != nullptr)
			{
				cudaFree(this->Signal_Padded_Result_Float_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Signal_Padded_Result_Float_In_GPU), Total_Size * sizeof(float)));
			checkCudaErrors(cudaMemset(this->Signal_Padded_Result_Float_In_GPU, 0, Total_Size * sizeof(float)));
			std::cout << "Signal padded result float data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Signal padded result float data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::InitializeSignalPaddedResultFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z)
	{
		this->Signal_Padded_Result_Size_D1 = Size_X;
		this->Signal_Padded_Result_Size_D2 = Size_Y;
		this->Signal_Padded_Result_Size_D3 = Size_Z;
		int Total_Size = Size_X * Size_Y * Size_Z;
		if (Total_Size > 0)
		{
			if (this->Signal_Padded_Result_Float2_In_GPU != nullptr)
			{
				cudaFree(this->Signal_Padded_Result_Float2_In_GPU);
			}
			checkCudaErrors(cudaMalloc((void **)&(this->Signal_Padded_Result_Float2_In_GPU), Total_Size * sizeof(float2)));
			checkCudaErrors(cudaMemset(this->Signal_Padded_Result_Float2_In_GPU, 0, Total_Size * sizeof(float2)));
			std::cout << "Signal padded result float2 data address has been Initialized successfully!" << std::endl;
		}
		else
		{
			std::cout << "Signal padded result float2 data address has been Initialized failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedResultFloatDataFromHostToDecive(float * Destination, float * Source)
	{
		int Total_Size = this->Signal_Padded_Result_Size_D1 * this->Signal_Padded_Result_Size_D2 * this->Signal_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy signal padded result float data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded result float data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedResultFloatDataFromDeciveToHost(float * Destination, float * Source)
	{
		int Total_Size = this->Signal_Padded_Result_Size_D1 * this->Signal_Padded_Result_Size_D2 * this->Signal_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			checkCudaErrors(cudaMemcpy(Destination, Source, Total_Size * sizeof(float), cudaMemcpyDeviceToHost));
			std::cout << "Copy signal padded result float data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded result float data from device to host failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedResultFloat2DataFromHostToDecive(float2 * Destination, complex * Source)
	{
		int Total_Size = this->Signal_Padded_Result_Size_D1 * this->Signal_Padded_Result_Size_D2 * this->Signal_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Temporary[Index] = Source[Index].x;
				Temporary[Index + 1] = Source[Index].y;
			}
			checkCudaErrors(cudaMemcpy(Destination, Temporary, 2 * Total_Size * sizeof(float), cudaMemcpyHostToDevice));
			std::cout << "Copy signal padded result float2 data from host to device successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded result float2 data from host to device failed!" << std::endl;
		}
	}
	void CUDAInitialization::CopySignalPaddedResultFloat2DataFromDeciveToHost(complex * Destination, float2 * Source)
	{
		int Total_Size = this->Signal_Padded_Result_Size_D1 * this->Signal_Padded_Result_Size_D2 * this->Signal_Padded_Result_Size_D3;
		if ((Destination != nullptr) && (Source != nullptr) && (Total_Size != 0))
		{
			float * Temporary = (float *)malloc(2 * Total_Size * sizeof(float));//两倍的量
			checkCudaErrors(cudaMemcpy(Temporary, Source, Total_Size * sizeof(float2), cudaMemcpyDeviceToHost));
			for (int Index = 0; Index < Total_Size; Index += 2)
			{
				Destination[Index].x = Temporary[Index];
				Destination[Index].y = Temporary[Index + 1];
			}
			std::cout << "Copy signal padded result float2 data from device to host successfully!" << std::endl;
		}
		else
		{
			std::cout << "Copy signal padded result float2 data from device to host failed!" << std::endl;
		}
	}




//****************************************************************************************************************************
	//void CUDAInitialization::Procedure(std::string Function_name, int Size_D1, int Size_D2, int Size_D3)
	//{
	//	for (auto Iter = this->Initialization_Function_List.begin(); Iter != Initialization_Function_List.end(); Iter++)
	//	{
	//		if (Iter->first == Function_name)
	//		{
	//			(this->*(Iter->second))(Size_D1, Size_D2, Size_D3);
	//		}
	//	}
	//}
	//void CUDAInitialization::Procedure(std::string Function_name, float * Destination, float * Source)
	//{
	//	for (auto Iter = this->Copy_Float_To_Float_Function_List.begin(); Iter != Copy_Float_To_Float_Function_List.end(); Iter++)
	//	{
	//		if (Iter->first == Function_name)
	//		{
	//			(this->*(Iter->second))(Destination, Source);
	//		}
	//	}
	//}
	//void CUDAInitialization::Procedure(std::string Function_name, float2 * Destination, complex * Source)
	//{
	//	for (auto Iter = this->Copy_Complex_To_Float2_Function_List.begin(); Iter != Copy_Complex_To_Float2_Function_List.end(); Iter++)
	//	{
	//		if (Iter->first == Function_name)
	//		{
	//			(this->*(Iter->second))(Destination, Source);
	//		}
	//	}
	//}
	//void CUDAInitialization::Procedure(std::string Function_name, complex * Destination, float2 * Source)
	//{
	//	for (auto Iter = this->Copy_Float2_To_Complex_Function_List.begin(); Iter != Copy_Float2_To_Complex_Function_List.end(); Iter++)
	//	{
	//		if (Iter->first == Function_name)
	//		{
	//			(this->*(Iter->second))(Destination, Source);
	//		}
	//	}
	//}
}




