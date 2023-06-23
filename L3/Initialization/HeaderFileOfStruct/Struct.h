//结构体定义。
#ifndef STRUCT_H
#define STRUCT_H
struct complex
{
	float x;
	float y;
};
struct SignalParameter
{
	int Kernel_Size_D1;
	int Kernel_Size_D2;
	int Kernel_Size_D3;
	int Kernel_Padded_Size_D1;
	int Kernel_Padded_Size_D2;
	int Kernel_Padded_Size_D3;
	int Kernel_Padded_Result_Size_D1;
	int Kernel_Padded_Result_Size_D2;
	int Kernel_Padded_Result_Size_D3;
	int Signal_Size_D1;
	int Signal_Size_D2;
	int Signal_Size_D3;
	int Signal_Padded_Size_D1;
	int Signal_Padded_Size_D2;
	int Signal_Padded_Size_D3;
	int Signal_Padded_Result_Size_D1;
	int Signal_Padded_Result_Size_D2;
	int Signal_Padded_Result_Size_D3;
};
#endif