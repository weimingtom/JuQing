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


	// 计算str字符数目
	int getUtf8Length(char *str);
	//get子串
	CCString* subUtfString(char *str, unsigned int start, unsigned int end);

	//获取对应key的字符串
	CCString *getXmlString(char *key);
	//获取对应Index的字符串
	CCString *getXmlString(int index);
	//获取xml中关键字里面是多句string
	CCString *getXmlArrayString(char *key, twlong index);

	void readRapidJSON(rapidjson::Document* doc, const char *file_name);
	const char* skipBOM(const char* p);


	//获取随机数
	twfloat getRandom();
	twdword getRandom(twdword max, twdword min = 0);

	//opengl坐标转地图坐标
	CCPoint toTileCoordinate(CCTMXTiledMap* tmx_tile_map, CCPoint position);
	//获取当前点所在块的中心的坐标
	CCPoint getTileCenterPoint(CCTMXTiledMap* tmx_tile_map, CCPoint position);
	//碰撞检测
	bool isRectCollision(CCRect rect1, CCRect rect2);
	//碰撞点是否在节点内
	bool isInNode(CCPoint, CCNode* node);

	//判断浮点数是否相等
	bool floatIsEquals(float f1, float f2);
	bool doubleIsEquals(double d1, double d2);

private:
	CCDictionary *__xml_dictionary;//xml在内存中的虚拟
};

#endif  //__TOPWO_FUNC_H__
