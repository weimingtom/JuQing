#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "DataNpc.h"
#include "DataSection.h"
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
	void addDataSectionToArray(DataSection* chapter_data);
	DataSection* getDataSectionFromArray(int id);
	void addDataMissionToArray(DataMission* mission_data);
	DataMission* getDataMissionFromArray(int id);

private:
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_npc, ArrOfDataNpc);//npc的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_chapter, ArrOfDataSection);//章节的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_mission, ArrOfDataMission);//章节的数据
	//玩过得天数
	CC_SYNTHESIZE(int, __plaid_days, PlaidDays);
	//当前的体力值
	CC_SYNTHESIZE(int, __cur_physical, CurrentPhysical);
	//当前的金钱
	CC_SYNTHESIZE(int, __cur_gold, CurrentGold);
	//当前的体魄1
	CC_SYNTHESIZE(int, __cur_tipo, CurrentTiPo);
	//当前的魅力2
	CC_SYNTHESIZE(int, __cur_meili, CurrentMeiLi);
	//当前的智力3
	CC_SYNTHESIZE(int, __cur_zhili, CurrentZhiLi);
	//当前的情商4
	CC_SYNTHESIZE(int, __cur_eq, CurrentEQ);
	//当前的感性5
	CC_SYNTHESIZE(int, __cur_ganxing, CurrentGanXing);
	//当前任务ID
	CC_SYNTHESIZE(int, __cur_mission_id, CurrentMissionId);
	//当前小节ID
	CC_SYNTHESIZE(int, __cur_section_id, CurrentSectionId);
	//当前剧情ID
	CC_SYNTHESIZE(int, __cur_plot_id, CurrentPlotId);
	//当前追求目标
	CC_SYNTHESIZE(int, __cur_wooer, CurrentWooer);
	//当前物品体魄
	CC_SYNTHESIZE(int, __cur_goods_level_tipo, CurrentGoodsLevelTiPo);
	//当前物品魅力
	CC_SYNTHESIZE(int, __cur_goods_level_meili, CurrentGoodsLevelMeiLi);
	//当前物品智力
	CC_SYNTHESIZE(int, __cur_goods_level_zhili, CurrentGoodsLevelZhiLi);
	//当前物品情商
	CC_SYNTHESIZE(int, __cur_goods_level_eq, CurrentGoodsLevelEQ);
	//当前物品感性
	CC_SYNTHESIZE(int, __cur_goods_level_ganxing, CurrentGoodsLevelGanXing);
	//当前章节ID
	//CC_SYNTHESIZE(int, __cur_chapter_id, CurrentChapterId);
};

#endif  //__USER_INFO_H__