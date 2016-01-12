#ifndef __TOPWO_FUNC_H__
#define __TOPWO_FUNC_H__
#include "cocos2d.h"
#include "TopwoDefine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class TopwoTools : public CCObject
{
public:
	TopwoTools();
	virtual ~TopwoTools();
	virtual bool init();
	CREATE_FUNC(TopwoTools);


	// ����str�ַ���Ŀ
	int getUtf8Length(char *str);
	//get�Ӵ�
	CCString* subUtfString(char *str, unsigned int start, unsigned int end);

	//��ȡ��Ӧkey���ַ���
	CCString *getXmlString(char *key);
	//��ȡ��ӦIndex���ַ���
	CCString *getXmlString(int index);
	//��ȡxml�йؼ��������Ƕ��string
	CCString *getXmlArrayString(char *key, twlong index);

	void readRapidJSON(rapidjson::Document* doc, const char *file_name);
	const char* skipBOM(const char* p);


	//��ȡ�����
	twfloat getRandom();
	twdword getRandom(twdword max, twdword min = 0);

	//opengl����ת��ͼ����
	CCPoint toTileCoordinate(CCTMXTiledMap* tmx_tile_map, CCPoint position);
	//��ȡ��ǰ�����ڿ�����ĵ�����
	CCPoint getTileCenterPoint(CCTMXTiledMap* tmx_tile_map, CCPoint position);
	//��ײ���
	bool isRectCollision(CCRect rect1, CCRect rect2);
	//��ײ���Ƿ��ڽڵ���
	bool isInNode(CCPoint, CCNode* node);

	//�жϸ������Ƿ����
	bool floatIsEquals(float f1, float f2);

private:
	CCDictionary *__xml_dictionary;//xml���ڴ��е�����
};

#endif  //__TOPWO_FUNC_H__
