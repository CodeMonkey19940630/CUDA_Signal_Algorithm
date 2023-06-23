#include "CUDATwoDimensionEchoExtractionAlgorithmCore.h"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"

//该算法以循环-递归结合的方式将二维0，1矩阵数据进行分群，由于多方面的原因（性能原因）个人认为不值得将后半部分求坐标的计算交给GPU去执行，所以该算法只有CPU代码成分。
//期待后来人的智慧，能设计出更好的CUDA版本，我是不太行了。
//X，Y均从0开始。Up，Down，Left，Right都返回位置。
int * Up(int * Current_Position, int Width)
{
	int * Up_Position = Current_Position - Width;
	return Up_Position;
}
int * Down(int * Current_Position, int Width)
{
	int * Down_Position = Current_Position + Width;
	return Down_Position;
}
int * Left(int * Current_Position)
{
	int * Left_Position = Current_Position - 1;
	return Left_Position;
}
int * Right(int * Current_Position)
{
	int * Right_Position = Current_Position + 1;
	return Right_Position;
}
//注意！使用该递归算法的参数必须是真实0，1序列数据的int类型数据副本（数据副本开始，以原数据为参照，再对应位置存对应位置的0，1数据）地址。
void ClusterByRecursion(int * Head_Address, int X, int Y, int Width, int Height, int Cluster_ID, bool &Conditional_Variable)
{

	int * Current_Position = Head_Address + Y * Width + X;
	if ((*Current_Position) == 1)
	{
		*Current_Position = Cluster_ID;//将发现的是1的元素标记为Cluster的ID值。Cluster的ID值必须区别于0，1这两个值，注意。
		Conditional_Variable = true;
	}
	if (((Y - 1) >= 0) && (*(Up(Current_Position, Width)) == 1))
	{
		//up
		ClusterByRecursion(Head_Address, X, Y - 1, Width, Height, Cluster_ID, Conditional_Variable);

	}
	if (((Y + 1) <= Height) && (*(Down(Current_Position, Width)) == 1))
	{
		//Down
		ClusterByRecursion(Head_Address, X, Y + 1, Width, Height, Cluster_ID, Conditional_Variable);
	}
	if (((X - 1) >= 0) && (*(Left(Current_Position)) == 1))
	{
		//Left
		ClusterByRecursion(Head_Address, X - 1, Y, Width, Height, Cluster_ID, Conditional_Variable);
	}
	if (((X + 1) >= Width) && (*(Right(Current_Position)) == 1))
	{
		//Right
		ClusterByRecursion(Head_Address, X + 1, Y, Width, Height, Cluster_ID, Conditional_Variable);
	}
	
}

void CUDATwoDimensionEchoExtractionAlgorithmCore(std::vector<std::pair<int, int>> &Up, std::vector<std::pair<int, int>> &Down, std::vector<std::pair<int, int>> &Left, std::vector<std::pair<int, int>> &Right, std::vector<std::pair<int, float>> &Max_Result, bool * CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int BlockSize)
{
	int Cluster_ID = 2;//Cluster ID的起始数值
	std::vector<int> Cluster_ID_List;
	//数据副本产生
	int * Copy_Data_CPU = (int *)malloc(Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group * sizeof(int));
	memset(Copy_Data_CPU, 0, Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group * sizeof(int));
	for (int Index = 0; Index < Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group; Index++)
	{
		if (CFAR_Result_Address[Index] == 1)
		{
			Copy_Data_CPU[Index] = 1;
		}
	}
	for (int Y_Index = 0; Y_Index < Count_Of_Pulse_Group; Y_Index++)
	{
		for (int X_Index = 0; X_Index < Count_Of_Sampling_Point_Of_Monopulse; X_Index++)
		{
			bool Conditional_Variable = false;
			ClusterByRecursion(Copy_Data_CPU, X_Index, Y_Index, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Cluster_ID, Conditional_Variable);
			if (Conditional_Variable == true)
			{
				Cluster_ID_List.push_back(Cluster_ID);
			}
			Cluster_ID++;
		}
	}
	//循环调用CUDA算法核心。
	//先测试Cluster_ID_List里面有没有东西。
	if (!Cluster_ID_List.empty())
	{
		for (auto Cluster_ID = Cluster_ID_List.begin(); Cluster_ID != Cluster_ID_List.end(); Cluster_ID++)
		{
			//比较大小的函数
			float Max_Temporary = 0;
			int Index_Temporary = 0;
			for (int Index = 0; Index < Count_Of_Sampling_Point_Of_Monopulse * Count_Of_Pulse_Group; Index++)
			{
				if (Copy_Data_CPU[Index] == (*Cluster_ID))
				{
					if (CFAR_Input_Absolute_Address[Index] >= Max_Temporary)
					{
						Max_Temporary = CFAR_Input_Absolute_Address[Index];
						Index_Temporary = Index;
					}
				}
			}
			Max_Result.push_back(std::make_pair(Index_Temporary, Max_Temporary));
			//计算四个方向的1数值边界坐标。
			int Offset = Index_Temporary;
			int Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//现在的Y坐标
			int X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//现在的X坐标

			//Up
			while ((Y_Offset - 1) >= 0 && Copy_Data_CPU[Offset - Count_Of_Sampling_Point_Of_Monopulse] != 0)
			{
				Offset = Offset - Count_Of_Sampling_Point_Of_Monopulse;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Up.push_back(std::make_pair(X_Offset, Y_Offset));
			//Down
			Offset = Index_Temporary;//重置
			Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//重置Y坐标
			X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//重置X坐标
			while ((Y_Offset + 1) < Count_Of_Pulse_Group && Copy_Data_CPU[Offset + Count_Of_Sampling_Point_Of_Monopulse] != 0)
			{
				Offset = Offset + Count_Of_Sampling_Point_Of_Monopulse;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Down.push_back(std::make_pair(X_Offset, Y_Offset));
			//Left
			Offset = Index_Temporary;//重置
			Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//重置Y坐标
			X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//重置X坐标
			while ((X_Offset - 1) >= 0 && Copy_Data_CPU[Offset - 1] != 0)
			{
				Offset = Offset - 1;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Left.push_back(std::make_pair(X_Offset, Y_Offset));
			//Right
			Offset = Index_Temporary;//重置
			Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//重置Y坐标
			X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//重置X坐标
			while ((X_Offset + 1) < Count_Of_Sampling_Point_Of_Monopulse && Copy_Data_CPU[Offset + 1] != 0)
			{
				Offset = Offset + 1;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Right.push_back(std::make_pair(X_Offset, Y_Offset));
		}
	}
	else
	{
		//0，1矩阵中全是0，也就是说没有检测到目标。
		std::cout << "There is no target here!" << std::endl;
	}
}