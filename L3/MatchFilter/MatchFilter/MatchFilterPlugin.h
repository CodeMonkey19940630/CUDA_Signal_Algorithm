//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef MATCHFILTER_H
#define MATCHFILTER_H
#ifdef MATCHFILTER_EXPORTS
#define MATCH_FILTER_EXPORTS __declspec(dllexport)
#else
#define MATCH_FILTER_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "MatchFilterModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
namespace GPUSignalAlgorithm
{
	class MATCH_FILTER_EXPORTS MatchFilterPlugin
	{
	public:
		MatchFilterPlugin();
		~MatchFilterPlugin();
		MatchFilterModule * PluginMatchFilter();
	private:
		MatchFilterModule * Match_Filter_Module_Pointer;
	};
}
#endif

