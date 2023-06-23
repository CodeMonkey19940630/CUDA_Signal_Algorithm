//只对外暴露IJamComponentFactory接口类
#ifndef MATCHFILTER_H
#define MATCHFILTER_H
#ifdef MATCHFILTER_EXPORTS
#define MATCH_FILTER_EXPORTS __declspec(dllexport)
#else
#define MATCH_FILTER_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "MatchFilterModule.h"
//PulseDopplerRadarDisplay接口类定义
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

