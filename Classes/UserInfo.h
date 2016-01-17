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
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_npc, ArrOfDataNpc);//npc������
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_chapter, ArrOfDataSection);//�½ڵ�����
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_mission, ArrOfDataMission);//�½ڵ�����
	//���������
	CC_SYNTHESIZE(int, __plaid_days, PlaidDays);
	//��ǰ������ֵ
	CC_SYNTHESIZE(int, __cur_physical, CurrentPhysical);
	//��ǰ�Ľ�Ǯ
	CC_SYNTHESIZE(int, __cur_gold, CurrentGold);
	//��ǰ������1
	CC_SYNTHESIZE(int, __cur_tipo, CurrentTiPo);
	//��ǰ������2
	CC_SYNTHESIZE(int, __cur_meili, CurrentMeiLi);
	//��ǰ������3
	CC_SYNTHESIZE(int, __cur_zhili, CurrentZhiLi);
	//��ǰ������4
	CC_SYNTHESIZE(int, __cur_eq, CurrentEQ);
	//��ǰ�ĸ���5
	CC_SYNTHESIZE(int, __cur_ganxing, CurrentGanXing);
	//��ǰ����ID
	CC_SYNTHESIZE(int, __cur_mission_id, CurrentMissionId);
	//��ǰС��ID
	CC_SYNTHESIZE(int, __cur_section_id, CurrentSectionId);
	//��ǰ����ID
	CC_SYNTHESIZE(int, __cur_plot_id, CurrentPlotId);
	//��ǰ׷��Ŀ��
	CC_SYNTHESIZE(int, __cur_wooer, CurrentWooer);
	//��ǰ��Ʒ����
	CC_SYNTHESIZE(int, __cur_goods_level_tipo, CurrentGoodsLevelTiPo);
	//��ǰ��Ʒ����
	CC_SYNTHESIZE(int, __cur_goods_level_meili, CurrentGoodsLevelMeiLi);
	//��ǰ��Ʒ����
	CC_SYNTHESIZE(int, __cur_goods_level_zhili, CurrentGoodsLevelZhiLi);
	//��ǰ��Ʒ����
	CC_SYNTHESIZE(int, __cur_goods_level_eq, CurrentGoodsLevelEQ);
	//��ǰ��Ʒ����
	CC_SYNTHESIZE(int, __cur_goods_level_ganxing, CurrentGoodsLevelGanXing);
	//��ǰ�½�ID
	//CC_SYNTHESIZE(int, __cur_chapter_id, CurrentChapterId);
};

#endif  //__USER_INFO_H__