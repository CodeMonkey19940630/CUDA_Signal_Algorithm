#include "CUDATwoDimensionEchoExtractionAlgorithmCore.h"
#include "../CUDAHeaderFileOfHierarchy1DLL/CUDAMathematicsFoundationArithmeticCore.cuh"

//���㷨��ѭ��-�ݹ��ϵķ�ʽ����ά0��1�������ݽ��з�Ⱥ�����ڶ෽���ԭ������ԭ�򣩸�����Ϊ��ֵ�ý���벿��������ļ��㽻��GPUȥִ�У����Ը��㷨ֻ��CPU����ɷ֡�
//�ڴ������˵��ǻۣ�����Ƴ����õ�CUDA�汾�����ǲ�̫���ˡ�
//X��Y����0��ʼ��Up��Down��Left��Right������λ�á�
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
//ע�⣡ʹ�øõݹ��㷨�Ĳ�����������ʵ0��1�������ݵ�int�������ݸ��������ݸ�����ʼ����ԭ����Ϊ���գ��ٶ�Ӧλ�ô��Ӧλ�õ�0��1���ݣ���ַ��
void ClusterByRecursion(int * Head_Address, int X, int Y, int Width, int Height, int Cluster_ID, bool &Conditional_Variable)
{

	int * Current_Position = Head_Address + Y * Width + X;
	if ((*Current_Position) == 1)
	{
		*Current_Position = Cluster_ID;//�����ֵ���1��Ԫ�ر��ΪCluster��IDֵ��Cluster��IDֵ����������0��1������ֵ��ע�⡣
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
	int Cluster_ID = 2;//Cluster ID����ʼ��ֵ
	std::vector<int> Cluster_ID_List;
	//���ݸ�������
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
	//ѭ������CUDA�㷨���ġ�
	//�Ȳ���Cluster_ID_List������û�ж�����
	if (!Cluster_ID_List.empty())
	{
		for (auto Cluster_ID = Cluster_ID_List.begin(); Cluster_ID != Cluster_ID_List.end(); Cluster_ID++)
		{
			//�Ƚϴ�С�ĺ���
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
			//�����ĸ������1��ֵ�߽����ꡣ
			int Offset = Index_Temporary;
			int Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//���ڵ�Y����
			int X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//���ڵ�X����

			//Up
			while ((Y_Offset - 1) >= 0 && Copy_Data_CPU[Offset - Count_Of_Sampling_Point_Of_Monopulse] != 0)
			{
				Offset = Offset - Count_Of_Sampling_Point_Of_Monopulse;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Up.push_back(std::make_pair(X_Offset, Y_Offset));
			//Down
			Offset = Index_Temporary;//����
			Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//����Y����
			X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//����X����
			while ((Y_Offset + 1) < Count_Of_Pulse_Group && Copy_Data_CPU[Offset + Count_Of_Sampling_Point_Of_Monopulse] != 0)
			{
				Offset = Offset + Count_Of_Sampling_Point_Of_Monopulse;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Down.push_back(std::make_pair(X_Offset, Y_Offset));
			//Left
			Offset = Index_Temporary;//����
			Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//����Y����
			X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//����X����
			while ((X_Offset - 1) >= 0 && Copy_Data_CPU[Offset - 1] != 0)
			{
				Offset = Offset - 1;
				Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;
				X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;
			}
			Left.push_back(std::make_pair(X_Offset, Y_Offset));
			//Right
			Offset = Index_Temporary;//����
			Y_Offset = Offset / Count_Of_Sampling_Point_Of_Monopulse;//����Y����
			X_Offset = Offset % Count_Of_Sampling_Point_Of_Monopulse;//����X����
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
		//0��1������ȫ��0��Ҳ����˵û�м�⵽Ŀ�ꡣ
		std::cout << "There is no target here!" << std::endl;
	}
}