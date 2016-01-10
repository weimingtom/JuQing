#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "DataNpc.h"
#include "DataChapter.h"
#include "DataMission.h"

USING_NS_CC;

class UserInfo : public CCObject
{
public:
	UserInfo();
	virtual ~UserInfo();
	bool init();
	CREATE_FUNC(UserInfo);

	void addDataNpcToArray(DataNpc* npc_data);
	DataNpc* getDataNpcFromArray(int id);
	void addDataChapterToArray(DataChapter* chapter_data);
	DataChapter* getDataChapterFromArray(int id);
	void addDataMissionToArray(DataMission* mission_data);
	DataMission* getDataMissionFromArray(int id);

private:
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_npc, ArrOfDataNpc);//npc的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_chapter, ArrOfDataChapter);//章节的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_mission, ArrOfDataMission);//章节的数据
	//玩过得天数
	CC_SYNTHESIZE(int, __plaid_days, PlaidDays);
	//当前的体力值
	CC_SYNTHESIZE(int, __cur_physical, CurrentPhysical);
	//当前的金钱
	CC_SYNTHESIZE(int, __cur_gold, CurrentGold);
	//当前的体魄
	CC_SYNTHESIZE(int, __cur_tipo, CurrentTiPo);
	//当前的魅力
	CC_SYNTHESIZE(int, __cur_meili, CurrentMeiLi);
	//当前的智力
	CC_SYNTHESIZE(int, __cur_zhili, CurrentZhiLi);
	//当前的情商
	CC_SYNTHESIZE(int, __cur_eq, CurrentEQ);
	//当前的感性
	CC_SYNTHESIZE(int, __cur_ganxing, CurrentGanXing);
	//当前任务ID
	CC_SYNTHESIZE(int, __cur_mission_id, CurrentMissionId);
	//当前小节ID
	CC_SYNTHESIZE(int, __cur_section_id, CurrentSectionId);
	//当前剧情ID
	CC_SYNTHESIZE(int, __cur_plot_id, CurrentPlotId);
	//当前追求目标
	CC_SYNTHESIZE(int, __cur_wooer, CurrentWooer);
	//当前章节ID
	//CC_SYNTHESIZE(int, __cur_chapter_id, CurrentChapterId);
};

#endif  //__USER_INFO_H__