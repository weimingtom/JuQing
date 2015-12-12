#include "TopwoTools.h"

TopwoTools::TopwoTools()
{

}

TopwoTools::~TopwoTools()
{
	__xml_dictionary->release();
}

bool TopwoTools::init()
{
	if (CCFileUtils::sharedFileUtils()->isFileExist("fonts/strings.xml"))
	{
		__xml_dictionary = CCDictionary::createWithContentsOfFile("fonts/strings.xml");
		if (__xml_dictionary)
			__xml_dictionary->retain();
	}

	return true;
}
CCString *TopwoTools::getXmlString(char *key)
{
	return (CCString*)(__xml_dictionary->objectForKey(key));
}

CCString *TopwoTools::getXmlString(int index)
{
	return ((CCString*)__xml_dictionary->objectForKey(index));
}

CCString *TopwoTools::getXmlArrayString(char *key, twlong index)
{
	CCArray* array = CCArray::createWithArray(((CCArray*)__xml_dictionary->objectForKey(key)));	
	return ((CCString*)array->objectAtIndex(index));
}

twfloat TopwoTools::getRandom()
{
	return (getRandom(100,0)/100.0);
}
twdword TopwoTools::getRandom(twdword max, twdword min)
{
	if (max < min)
		return 0;
	twdword random= (twdword)std::rand();
	random = min + (random % (max - min + 1));
	return random;
}
//opengl坐标转地图坐标 position是相对于地图原点的坐标
CCPoint TopwoTools::toTileCoordinate(CCTMXTiledMap* tmx_tile_map, CCPoint position)
{
	CCSize tile_size = tmx_tile_map->getTileSize();
	CCSize map_size = tmx_tile_map->getMapSize();
	twint x = position.x / tile_size.width;
	twint y = position.y / tile_size.height;
	y = map_size.height - (y + 1);
	return ccp(x, y);
}
CCPoint TopwoTools::getTileCenterPoint(CCTMXTiledMap* tmx_tile_map, CCPoint position)
{
	CCSize tile_size = tmx_tile_map->getTileSize();
	twint x = position.x / tile_size.width;
	twint y =  position.y/ tile_size.height;
	return ccp(x*tile_size.width + tile_size.width*0.5, y* tile_size.height + tile_size.height*0.5);
}
//碰撞检测
bool TopwoTools::isRectCollision(CCRect rect1, CCRect rect2)
{
	float x1 = rect1.origin.x;//矩形1中心点的横坐标  
	float y1 = rect1.origin.y;//矩形1中心点的纵坐标  
	float w1 = rect1.size.width;//矩形1的宽度  
	float h1 = rect1.size.height;//矩形1的高度  
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;

	if (x1 + w1*0.5<x2 - w2*0.5)
		return false;//矩形1在矩形2左方，两者无碰撞  
	else if (x1 - w1*0.5>x2 + w2*0.5)
		return false;//矩形1在矩形2右方，两者无碰撞  
	else if (y1 + h1*0.5<y2 - h2*0.5)
		return false;//矩形1在矩形2下方，两者无碰撞  
	else if (y1 - h1*0.5>y2 + h2*0.5)
		return false;//矩形1在矩形2上方，两者无碰撞  

	return true;
}

//点是否在节点内
twbool TopwoTools::isInNode(CCPoint touch_point, CCNode* node)
{
	if (abs(touch_point.x - node->getPositionX()) <= node->getContentSize().width*node->getScaleX()*0.5f &&
		abs(touch_point.y - node->getPositionY()) <= node->getContentSize().height*node->getScaleY()*0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TopwoTools::readRapidJSON(rapidjson::Document* doc, const char *file_name)
{
	unsigned long file_data_size = 0;
	do {
		CC_BREAK_IF(doc == NULL || !CCFileUtils::sharedFileUtils()->isFileExist(file_name));
		unsigned char* file_data = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename(file_name).c_str(), "r", &file_data_size);
		CC_BREAK_IF(file_data == NULL || strcmp((char*)file_data, "") == 0);
		CCLOG("%s", file_data);
		std::string file_str((const char*)file_data, file_data_size);
		CC_SAFE_DELETE_ARRAY(file_data);
		doc->Parse<rapidjson::kParseDefaultFlags>(file_str.c_str());
		CC_BREAK_IF(doc->HasParseError());
		break;
	} while (0);

		//生成json文档对像
		/*if (!m_doc.IsObject())
		{
			return;
		}*/

		/*
		for (unsigned int i = 1; i<doc->Size(); i++)
		{
			//逐个提取数组元素（声明的变量必须为引用） 
			rapidjson::Value &v = (*doc)[i];
			int id;//ID 
			std::string name;//名称
			int hp;//血量 
			int Defense;//防御力 
			int attack;//攻击力 
			int passable;//是否可穿透（通行） 
			//判断各属性是否存在（可以支持中文（UTF8格式）） 
			//if (v.HasMember("ID") && v.HasMember(A2U("名称")) && v.HasMember(A2U("血量"))
			//	&& v.HasMember(A2U("防御力")) && v.HasMember(A2U("攻击力")) && v.HasMember(A2U("可穿透")))
			//{
			//		//按属性提取数据 
			//		id = v["ID"].GetInt();
			//		name = v[A2U("名称")].GetString();
			//		hp = v[A2U("血量")].GetInt();
			//		Defense = v[A2U("防御力")].GetInt();
			//		attack = v[A2U("攻击力")].GetInt();
			//		passable = v[A2U("可穿透")].GetInt();
			//		log(A2U("ID:%d,名称:%s,血量:%d,防御力:%d,攻击力:%d,可穿透性:%s"),
			//		id, name.c_str(), hp, Defense, attack, (passable ? "true" : "false"));
			//}
			int a = 0;
			id = v[a++].GetInt();
			name = v[a++].GetString();
			hp = v[a++].GetInt();
			Defense = v[a++].GetInt();
			attack = v[a++].GetInt();
			passable = v[a++].GetInt();
			CCLOG("ID:%d,名称:%s,血量:%d,防御力:%d,攻击力:%d,可穿透性:%s",
			id, name.c_str(), hp, Defense, attack, (passable ? "true" : "false");
		}
		*/

		//获取JSon中数组的方法
		//const rapidjson::Value& v = m_doc["pets"];
		//if (v.IsArray()) {
		//	//这里一定要注意  变量i 一定要是   unsigned int  不然会报错
		//	for (unsigned int i = 0; i< v.Size(); ++i) {

		//		const rapidjson::Value &val = v[i];
		//		CCLOG("%s", val.GetString());
		//	}
		//}
		//else
		//{
		//	const rapidjson::Value& val = v["stuAge"];
		//	CCLOG("val.GetString() = %s", val.GetString());
		//}
}
