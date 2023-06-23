//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef ECHOSIGNALGENERATOR_H
#define ECHOSIGNALGENERATOR_H
#ifdef ECHOSIGNALGENERATOR_EXPORTS
#define ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllexport)
#else
#define ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "EchoSignalGeneratorModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
namespace GPUSignalAlgorithm
{
	class ECHO_SIGNAL_GENERATOR_EXPORTS EchoSignalGeneratorPlugin
	{
	public:
		EchoSignalGeneratorPlugin();
		~EchoSignalGeneratorPlugin();
		EchoSignalGeneratorModule * PluginEchoSignalGenerator();
	private:
		EchoSignalGeneratorModule * Echo_Signal_Generator_Module_Pointer;
	};
}
#endif

