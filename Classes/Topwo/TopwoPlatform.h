#ifndef __TOPWO_PLATFORM_H__
#define __TOPWO_PLATFORM_H__

#include "cocos2d.h"

USING_NS_CC;


typedef void (CCObject::*SEL_CallFuncI)(int);
#define callfuncI_selector(_SELECTOR) (SEL_CallFuncI)(&_SELECTOR)

class TopwoPlatform : public CCObject
{
public:
	TopwoPlatform();
	virtual ~TopwoPlatform();
	virtual bool init();
	CREATE_FUNC(TopwoPlatform);
	

	// -------------------------------------------------------------
	//��ʾ�˳���
	void callShowExitDialog();
	//����ַ
	void callOpenURL(const char* pszUrl);
	//����֧��
	void callPay(int id, CCObject* target, SEL_CallFuncI callfun);
	//֧���ص�
	void payCallback(int status);

	//���õ�ǰ��ҵĵȼ�
	void setLevel(int level);
	//��Ϸ�ؿ���ʼ
	void levelBegin(const char* levelId);
	//��Ϸ�ؿ�ͨ��
	void levelComplete(const char* levelId);
	//��Ϸ�ؿ�ͨ��ʧ��
	void levelIdFail(const char* levelId);
	//��¼����������������
	void setCoinNum(int coinNum, const char* coinType);
	//�Զ����¼�
	void onEvent(const char* eventId);


	//չʾ�Ի������ǽ
	void showOffersWallDialog();

	//չʾ�Ի������
	void showShareWallDialog();

	//����
	void awardPoints(float f);
	//����
	void spendPoints(float f);
	//��ѯ����
	float queryPoints();

private:

	CCObject* __callbackListener;
	SEL_CallFuncI __callbackfunc;
};

#endif  //__TOPWO_PLATFORM_H__