//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#ifdef INITIALIZATION_EXPORTS
#define INITIALISATION_EXPORTS __declspec(dllexport)
#else
#define INITIALISATION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "InitializationModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
namespace GPUSignalAlgorithm
{
	class INITIALISATION_EXPORTS InitializationPlugin
	{
	public:
		InitializationPlugin();
		~InitializationPlugin();
		InitializationModule * PluginInitialization();
	private:
		InitializationModule * Initialization_Module_Pointer;
	};
}
#endif

