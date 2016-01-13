#include "LayerExercise.h"

LayerExercise::LayerExercise()
:__level(1)
{

}
LayerExercise::~LayerExercise()
{
}
bool LayerExercise::init()
{
    // 1. super init first
    if (!CCLayer::init() )
    {
        return false;
	}

	initUI();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);

    return true;
}
//初始化UI
bool LayerExercise::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//关闭项
	CCMenuItemImage *item_close = CCMenuItemImage::create(
		"images/btn_close_1_0.png",
		"images/btn_close_1_0.png",
		this,
		menu_selector(LayerExercise::menuCallbackClose));
	CCSize size_item_close = item_close->getContentSize();
	item_close->setPosition(ccp(vs.width * 0.8f, vs.height * 0.8f));

	//标题
	__sp_title = CCSprite::create("images/LayerExercise_low_title.png");
	this->addChild(__sp_title);
	CCSize size_sp_title = __sp_title->getContentSize();
	__sp_title->setPosition(ccp(vs.width * 0.5f, vs.height * 0.8f));

	//向左项
	__item_to_left = CCMenuItemSprite::create(
		CCSprite::create("images/btn_arrow_green_0.png"),
		CCSprite::create("images/btn_arrow_green_0.png"),
		this,
		menu_selector(LayerExercise::menuCallbackToLeft));
	__item_to_left->setPosition(ccp(vs.width * 0.5f - size_sp_title.width * 1.5f, vs.height * 0.8f));

	//向右项
	__item_to_right = CCMenuItemSprite::create(
		CCSprite::create("images/btn_arrow_green_0.png"),
		CCSprite::create("images/btn_arrow_green_0.png"),
		this,
		menu_selector(LayerExercise::menuCallbackToRight));
	__item_to_right->setPosition(ccp(vs.width * 0.5f + size_sp_title.width* 1.5f, vs.height * 0.8f));

	//体魄项
	__item_tipo = CCMenuItemSprite::create(
		CCSprite::create("images/LayerExercise_low_1_0.png"),
		CCSprite::create("images/LayerExercise_low_1_1.png"),
		this,
		menu_selector(LayerExercise::menuCallbackTipo));
	CCSize size_item_tipo = __item_tipo->getContentSize();
	__item_tipo->setPosition(ccp(vs.width * 0.5f - size_item_tipo.width * 2.2f, vs.height * 0.5f));

	CCSprite* sp_gold = CCSprite::create("images/LayerExercise_gold.png");
	__item_tipo->addChild(sp_gold, 10);
	CCSize size_sp_gold = sp_gold->getContentSize();
	sp_gold->setPosition(ccp(size_item_tipo.width * 0.24f, size_item_tipo.height * 0.34f));
	CCLabelAtlas *la_gold = CCLabelAtlas::create("-500", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_tipo->addChild(la_gold, 10, 100);
	la_gold->setAnchorPoint(ccp(0, 0.5f));
	la_gold->setPosition(ccp(size_item_tipo.width * 0.24f + size_sp_gold.width * 0.6f, size_item_tipo.height * 0.34f));
	CCSprite* sp_physical = CCSprite::create("images/LayerExercise_physical.png");
	__item_tipo->addChild(sp_physical, 10);
	CCSize size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_item_tipo.width * 0.3f, size_item_tipo.height * 0.23f));
	CCLabelAtlas *la_physical = CCLabelAtlas::create("-15", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_tipo->addChild(la_physical, 10, 101);
	la_physical->setAnchorPoint(ccp(0, 0.5f));
	la_physical->setPosition(ccp(size_item_tipo.width * 0.3f + size_sp_physical.width * 0.6f, size_item_tipo.height * 0.23f));
	CCSprite* sp_item_name = CCSprite::create("images/LayerExercise_tipo.png");
	__item_tipo->addChild(sp_item_name, 10);
	CCSize size_sp_item_name = sp_item_name->getContentSize();
	sp_item_name->setPosition(ccp(size_item_tipo.width * 0.34f, size_item_tipo.height * 0.12f));
	CCLabelAtlas *la_tipo = CCLabelAtlas::create("+2", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_tipo->addChild(la_tipo, 10, 102);
	la_tipo->setAnchorPoint(ccp(0, 0.5f));
	la_tipo->setPosition(ccp(size_item_tipo.width * 0.34f + size_sp_item_name.width * 0.6f, size_item_tipo.height * 0.12f));


	//魅力项
	__item_meili = CCMenuItemSprite::create(
		CCSprite::create("images/LayerExercise_low_2_0.png"),
		CCSprite::create("images/LayerExercise_low_2_1.png"),
		this,
		menu_selector(LayerExercise::menuCallbackMeili));
	CCSize size_item_meili = __item_meili->getContentSize();
	__item_meili->setPosition(ccp(vs.width * 0.5f - size_item_tipo.width* 1.1f, vs.height * 0.5f));

	sp_gold = CCSprite::create("images/LayerExercise_gold.png");
	__item_meili->addChild(sp_gold, 10);
	size_sp_gold = sp_gold->getContentSize();
	sp_gold->setPosition(ccp(size_item_tipo.width * 0.24f, size_item_tipo.height * 0.34f));
	la_gold = CCLabelAtlas::create("-500", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_meili->addChild(la_gold, 10, 100);
	la_gold->setAnchorPoint(ccp(0, 0.5f));
	la_gold->setPosition(ccp(size_item_tipo.width * 0.24f + size_sp_gold.width * 0.6f, size_item_tipo.height * 0.34f));
	sp_physical = CCSprite::create("images/LayerExercise_physical.png");
	__item_meili->addChild(sp_physical, 10);
	size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_item_tipo.width * 0.3f, size_item_tipo.height * 0.23f));
	la_physical = CCLabelAtlas::create("-15", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_meili->addChild(la_physical, 10, 101);
	la_physical->setAnchorPoint(ccp(0, 0.5f));
	la_physical->setPosition(ccp(size_item_tipo.width * 0.3f + size_sp_physical.width * 0.6f, size_item_tipo.height * 0.23f));
	sp_item_name = CCSprite::create("images/LayerExercise_meili.png");
	__item_meili->addChild(sp_item_name, 10);
	size_sp_item_name = sp_item_name->getContentSize();
	sp_item_name->setPosition(ccp(size_item_tipo.width * 0.34f, size_item_tipo.height * 0.12f));
	la_tipo = CCLabelAtlas::create("+2", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_meili->addChild(la_tipo, 10, 102);
	la_tipo->setAnchorPoint(ccp(0, 0.5f));
	la_tipo->setPosition(ccp(size_item_tipo.width * 0.34f + size_sp_item_name.width * 0.6f, size_item_tipo.height * 0.12f));

	//智力项
	__item_zhili = CCMenuItemSprite::create(
		CCSprite::create("images/LayerExercise_low_3_0.png"),
		CCSprite::create("images/LayerExercise_low_3_1.png"),
		this,
		menu_selector(LayerExercise::menuCallbackZhili));
	CCSize size_item_zhili = __item_zhili->getContentSize();
	__item_zhili->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	sp_gold = CCSprite::create("images/LayerExercise_gold.png");
	__item_zhili->addChild(sp_gold, 10);
	size_sp_gold = sp_gold->getContentSize();
	sp_gold->setPosition(ccp(size_item_tipo.width * 0.24f, size_item_tipo.height * 0.34f));
	la_gold = CCLabelAtlas::create("-500", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_zhili->addChild(la_gold, 10, 100);
	la_gold->setAnchorPoint(ccp(0, 0.5f));
	la_gold->setPosition(ccp(size_item_tipo.width * 0.24f + size_sp_gold.width * 0.6f, size_item_tipo.height * 0.34f));
	sp_physical = CCSprite::create("images/LayerExercise_physical.png");
	__item_zhili->addChild(sp_physical, 10);
	size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_item_tipo.width * 0.3f, size_item_tipo.height * 0.23f));
	la_physical = CCLabelAtlas::create("-15", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_zhili->addChild(la_physical, 10, 101);
	la_physical->setAnchorPoint(ccp(0, 0.5f));
	la_physical->setPosition(ccp(size_item_tipo.width * 0.3f + size_sp_physical.width * 0.6f, size_item_tipo.height * 0.23f));
	sp_item_name = CCSprite::create("images/LayerExercise_zhili.png");
	__item_zhili->addChild(sp_item_name, 10);
	size_sp_item_name = sp_item_name->getContentSize();
	sp_item_name->setPosition(ccp(size_item_tipo.width * 0.34f, size_item_tipo.height * 0.12f));
	la_tipo = CCLabelAtlas::create("+2", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_zhili->addChild(la_tipo, 10, 102);
	la_tipo->setAnchorPoint(ccp(0, 0.5f));
	la_tipo->setPosition(ccp(size_item_tipo.width * 0.34f + size_sp_item_name.width * 0.6f, size_item_tipo.height * 0.12f));

	//情商项
	__item_eq = CCMenuItemSprite::create(
		CCSprite::create("images/LayerExercise_low_4_0.png"),
		CCSprite::create("images/LayerExercise_low_4_1.png"),
		this,
		menu_selector(LayerExercise::menuCallbackEq));
	CCSize size_item_eq = __item_eq->getContentSize();
	__item_eq->setPosition(ccp(vs.width * 0.5f + size_item_tipo.width * 1.1f, vs.height * 0.5f));

	sp_gold = CCSprite::create("images/LayerExercise_gold.png");
	__item_eq->addChild(sp_gold, 10);
	size_sp_gold = sp_gold->getContentSize();
	sp_gold->setPosition(ccp(size_item_tipo.width * 0.24f, size_item_tipo.height * 0.34f));
	la_gold = CCLabelAtlas::create("-500", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_eq->addChild(la_gold, 10, 100);
	la_gold->setAnchorPoint(ccp(0, 0.5f));
	la_gold->setPosition(ccp(size_item_tipo.width * 0.24f + size_sp_gold.width * 0.6f, size_item_tipo.height * 0.34f));
	sp_physical = CCSprite::create("images/LayerExercise_physical.png");
	__item_eq->addChild(sp_physical, 10);
	size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_item_tipo.width * 0.3f, size_item_tipo.height * 0.23f));
	la_physical = CCLabelAtlas::create("-15", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_eq->addChild(la_physical, 10, 101);
	la_physical->setAnchorPoint(ccp(0, 0.5f));
	la_physical->setPosition(ccp(size_item_tipo.width * 0.3f + size_sp_physical.width * 0.6f, size_item_tipo.height * 0.23f));
	sp_item_name = CCSprite::create("images/LayerExercise_eq.png");
	__item_eq->addChild(sp_item_name, 10);
	size_sp_item_name = sp_item_name->getContentSize();
	sp_item_name->setPosition(ccp(size_item_tipo.width * 0.34f, size_item_tipo.height * 0.12f));
	la_tipo = CCLabelAtlas::create("+2", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_eq->addChild(la_tipo, 10, 102);
	la_tipo->setAnchorPoint(ccp(0, 0.5f));
	la_tipo->setPosition(ccp(size_item_tipo.width * 0.34f + size_sp_item_name.width * 0.6f, size_item_tipo.height * 0.12f));

	//感性项
	__item_ganxing = CCMenuItemSprite::create(
		CCSprite::create("images/LayerExercise_low_5_0.png"),
		CCSprite::create("images/LayerExercise_low_5_1.png"),
		this,
		menu_selector(LayerExercise::menuCallbackGanxing));
	CCSize size_item_ganxing = __item_ganxing->getContentSize();
	__item_ganxing->setPosition(ccp(vs.width * 0.5f + size_item_tipo.width * 2.2f, vs.height * 0.5f));

	sp_gold = CCSprite::create("images/LayerExercise_gold.png");
	__item_ganxing->addChild(sp_gold, 10);
	size_sp_gold = sp_gold->getContentSize();
	sp_gold->setPosition(ccp(size_item_tipo.width * 0.24f, size_item_tipo.height * 0.34f));
	la_gold = CCLabelAtlas::create("-500", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_ganxing->addChild(la_gold, 10, 100);
	la_gold->setAnchorPoint(ccp(0, 0.5f));
	la_gold->setPosition(ccp(size_item_tipo.width * 0.24f + size_sp_gold.width * 0.6f, size_item_tipo.height * 0.34f));
	sp_physical = CCSprite::create("images/LayerExercise_physical.png");
	__item_ganxing->addChild(sp_physical, 10);
	size_sp_physical = sp_physical->getContentSize();
	sp_physical->setPosition(ccp(size_item_tipo.width * 0.3f, size_item_tipo.height * 0.23f));
	la_physical = CCLabelAtlas::create("-15", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_ganxing->addChild(la_physical, 10, 101);
	la_physical->setAnchorPoint(ccp(0, 0.5f));
	la_physical->setPosition(ccp(size_item_tipo.width * 0.3f + size_sp_physical.width * 0.6f, size_item_tipo.height * 0.23f));
	sp_item_name = CCSprite::create("images/LayerExercise_ganxing.png");
	__item_ganxing->addChild(sp_item_name, 10);
	size_sp_item_name = sp_item_name->getContentSize();
	sp_item_name->setPosition(ccp(size_item_tipo.width * 0.34f, size_item_tipo.height * 0.12f));
	la_tipo = CCLabelAtlas::create("+2", "fonts/atlas/number_style_4.png", 12, 15, '+');
	__item_ganxing->addChild(la_tipo, 10, 102);
	la_tipo->setAnchorPoint(ccp(0, 0.5f));
	la_tipo->setPosition(ccp(size_item_tipo.width * 0.34f + size_sp_item_name.width * 0.6f, size_item_tipo.height * 0.12f));
	
	CCMenu *menu = CCMenu::create(item_close, __item_to_left, __item_to_right, __item_tipo, __item_meili, __item_zhili, __item_eq, __item_ganxing, NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	updateMe();
	
	return true;
}
void LayerExercise::updateMe()
{
	CCSprite* normal_sprite = NULL;
	CCSprite* selected_sprite = NULL;
	if (__level == 1)
	{
		//标题
		__sp_title->setTexture(CCTextureCache::sharedTextureCache()->addImage("images/LayerExercise_low_title.png"));
		//向左项
		__item_to_left->setNormalImage(CCSprite::create("images/btn_arrow_green_0.png"));
		__item_to_left->setSelectedImage(CCSprite::create("images/btn_arrow_green_0.png"));
		CCSize size_item_to_left = __item_to_left->getContentSize();
		normal_sprite = static_cast<CCSprite*>(__item_to_left->getNormalImage());
		selected_sprite = static_cast<CCSprite*>(__item_to_left->getSelectedImage());
		normal_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		selected_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		normal_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setScale(1.2f);
		normal_sprite->setFlipX(true);
		selected_sprite->setFlipX(true);

		//向右项
		__item_to_right->setNormalImage(CCSprite::create("images/btn_arrow_green_0.png"));
		__item_to_right->setSelectedImage(CCSprite::create("images/btn_arrow_green_0.png"));
		CCSize size_item_to_right = __item_to_right->getContentSize();
		normal_sprite = static_cast<CCSprite*>(__item_to_right->getNormalImage());
		selected_sprite = static_cast<CCSprite*>(__item_to_right->getSelectedImage());
		normal_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		selected_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		normal_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setScale(1.2f);

		//体魄项
		__item_tipo->setNormalImage(CCSprite::create("images/LayerExercise_low_1_0.png"));
		__item_tipo->setSelectedImage(CCSprite::create("images/LayerExercise_low_1_1.png"));
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->setString("-500");
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->setString("-15");
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->setString("+2");
		//魅力项
		__item_meili->setNormalImage(CCSprite::create("images/LayerExercise_low_2_0.png"));
		__item_meili->setSelectedImage(CCSprite::create("images/LayerExercise_low_2_1.png"));
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(100))->setString("-500");
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(101))->setString("-15");
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(102))->setString("+2");
		//智力项
		__item_zhili->setNormalImage(CCSprite::create("images/LayerExercise_low_3_0.png"));
		__item_zhili->setSelectedImage(CCSprite::create("images/LayerExercise_low_3_1.png"));
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(100))->setString("-500");
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(101))->setString("-15");
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(102))->setString("+2");
		//情商项
		__item_eq->setNormalImage(CCSprite::create("images/LayerExercise_low_4_0.png"));
		__item_eq->setSelectedImage(CCSprite::create("images/LayerExercise_low_4_1.png"));
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(100))->setString("-500");
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(101))->setString("-15");
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(102))->setString("+2");
		//感性项
		__item_ganxing->setNormalImage(CCSprite::create("images/LayerExercise_low_5_0.png"));
		__item_ganxing->setSelectedImage(CCSprite::create("images/LayerExercise_low_5_1.png"));
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(100))->setString("-500");
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(101))->setString("-15");
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(102))->setString("+2");
	}
	else if (__level == 2)
	{
		//标题
		__sp_title->setTexture(CCTextureCache::sharedTextureCache()->addImage("images/LayerExercise_mid_title.png"));
		//向左项
		__item_to_left->setNormalImage(CCSprite::create("images/btn_arrow_blue_0.png"));
		__item_to_left->setSelectedImage(CCSprite::create("images/btn_arrow_blue_0.png"));
		CCSize size_item_to_left = __item_to_left->getContentSize();
		normal_sprite = static_cast<CCSprite*>(__item_to_left->getNormalImage());
		selected_sprite = static_cast<CCSprite*>(__item_to_left->getSelectedImage());
		normal_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		selected_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		normal_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setScale(1.2f);
		normal_sprite->setFlipX(true);
		selected_sprite->setFlipX(true);

		//向右项
		__item_to_right->setNormalImage(CCSprite::create("images/btn_arrow_blue_0.png"));
		__item_to_right->setSelectedImage(CCSprite::create("images/btn_arrow_blue_0.png"));
		CCSize size_item_to_right = __item_to_right->getContentSize();
		normal_sprite = static_cast<CCSprite*>(__item_to_right->getNormalImage());
		selected_sprite = static_cast<CCSprite*>(__item_to_right->getSelectedImage());
		normal_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		selected_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		normal_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setScale(1.2f);

		//体魄项
		__item_tipo->setNormalImage(CCSprite::create("images/LayerExercise_mid_1_0.png"));
		__item_tipo->setSelectedImage(CCSprite::create("images/LayerExercise_mid_1_1.png"));
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->setString("-1000");
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->setString("-30");
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->setString("+5");
		//魅力项
		__item_meili->setNormalImage(CCSprite::create("images/LayerExercise_mid_2_0.png"));
		__item_meili->setSelectedImage(CCSprite::create("images/LayerExercise_mid_2_1.png"));
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(100))->setString("-1000");
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(101))->setString("-30");
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(102))->setString("+5");
		//智力项
		__item_zhili->setNormalImage(CCSprite::create("images/LayerExercise_mid_3_0.png"));
		__item_zhili->setSelectedImage(CCSprite::create("images/LayerExercise_mid_3_1.png"));
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(100))->setString("-1000");
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(101))->setString("-30");
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(102))->setString("+5");
		//情商项
		__item_eq->setNormalImage(CCSprite::create("images/LayerExercise_mid_4_0.png"));
		__item_eq->setSelectedImage(CCSprite::create("images/LayerExercise_mid_4_1.png"));
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(100))->setString("-1000");
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(101))->setString("-30");
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(102))->setString("+5");
		//感性项
		__item_ganxing->setNormalImage(CCSprite::create("images/LayerExercise_mid_5_0.png"));
		__item_ganxing->setSelectedImage(CCSprite::create("images/LayerExercise_mid_5_1.png"));
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(100))->setString("-1000");
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(101))->setString("-30");
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(102))->setString("+5");
	}
	else if (__level == 3)
	{
		//标题
		__sp_title->setTexture(CCTextureCache::sharedTextureCache()->addImage("images/LayerExercise_high_title.png"));
		//向左项
		__item_to_left->setNormalImage(CCSprite::create("images/btn_arrow_orange_0.png"));
		__item_to_left->setSelectedImage(CCSprite::create("images/btn_arrow_orange_0.png"));
		CCSize size_item_to_left = __item_to_left->getContentSize();
		normal_sprite = static_cast<CCSprite*>(__item_to_left->getNormalImage());
		selected_sprite = static_cast<CCSprite*>(__item_to_left->getSelectedImage());
		normal_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		selected_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		normal_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setScale(1.2f);
		normal_sprite->setFlipX(true);
		selected_sprite->setFlipX(true);

		//向右项
		__item_to_right->setNormalImage(CCSprite::create("images/btn_arrow_orange_0.png"));
		__item_to_right->setSelectedImage(CCSprite::create("images/btn_arrow_orange_0.png"));
		CCSize size_item_to_right = __item_to_right->getContentSize();
		normal_sprite = static_cast<CCSprite*>(__item_to_right->getNormalImage());
		selected_sprite = static_cast<CCSprite*>(__item_to_right->getSelectedImage());
		normal_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		selected_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		normal_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setPosition(ccp(size_item_to_left.width * 0.5f, size_item_to_left.height * 0.5f));
		selected_sprite->setScale(1.2f);

		//体魄项
		__item_tipo->setNormalImage(CCSprite::create("images/LayerExercise_high_1_0.png"));
		__item_tipo->setSelectedImage(CCSprite::create("images/LayerExercise_high_1_1.png"));
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->setString("-1500");
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->setString("-45");
		static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->setString("+10");
		//魅力项
		__item_meili->setNormalImage(CCSprite::create("images/LayerExercise_high_2_0.png"));
		__item_meili->setSelectedImage(CCSprite::create("images/LayerExercise_high_2_1.png"));
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(100))->setString("-1500");
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(101))->setString("-45");
		static_cast<CCLabelAtlas*>(__item_meili->getChildByTag(102))->setString("+10");
		//智力项
		__item_zhili->setNormalImage(CCSprite::create("images/LayerExercise_high_3_0.png"));
		__item_zhili->setSelectedImage(CCSprite::create("images/LayerExercise_high_3_1.png"));
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(100))->setString("-1500");
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(101))->setString("-45");
		static_cast<CCLabelAtlas*>(__item_zhili->getChildByTag(102))->setString("+10");
		//情商项
		__item_eq->setNormalImage(CCSprite::create("images/LayerExercise_high_4_0.png"));
		__item_eq->setSelectedImage(CCSprite::create("images/LayerExercise_high_4_1.png"));
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(100))->setString("-1500");
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(101))->setString("-45");
		static_cast<CCLabelAtlas*>(__item_eq->getChildByTag(102))->setString("+10");
		//感性项
		__item_ganxing->setNormalImage(CCSprite::create("images/LayerExercise_high_5_0.png"));
		__item_ganxing->setSelectedImage(CCSprite::create("images/LayerExercise_high_5_1.png"));
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(100))->setString("-1500");
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(101))->setString("-45");
		static_cast<CCLabelAtlas*>(__item_ganxing->getChildByTag(102))->setString("+10");
	}
}
void LayerExercise::menuCallbackToLeft(CCObject* pSender)
{
	if (__level == 1)
	{
		__level = 3;
	}
	else if (__level == 2)
	{
		__level = 1;
	}
	else if (__level == 3)
	{
		__level = 2;
	}
	updateMe();
}

void LayerExercise::menuCallbackToRight(CCObject* pSender)
{
	if (__level == 1)
	{
		__level = 2;
	}
	else if (__level == 2)
	{
		__level = 3;
	}
	else if (__level == 3)
	{
		__level = 1;
	}
	updateMe();
}
void LayerExercise::menuCallbackTipo(CCObject* pSender)
{
	int gold = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->getString());
	int physical = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->getString());
	int tipo = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->getString());

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentGold(user_info->getCurrentGold() + gold);
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() + physical);
	user_info->setCurrentTiPo(user_info->getCurrentTiPo() + tipo);
}
void LayerExercise::menuCallbackMeili(CCObject* pSender)
{
	int gold = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->getString());
	int physical = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->getString());
	int meili = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->getString());

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentGold(user_info->getCurrentGold() + gold);
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() + physical);
	user_info->setCurrentMeiLi(user_info->getCurrentMeiLi() + meili);
}
void LayerExercise::menuCallbackZhili(CCObject* pSender)
{
	int gold = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->getString());
	int physical = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->getString());
	int zhili = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->getString());

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentGold(user_info->getCurrentGold() + gold);
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() + physical);
	user_info->setCurrentZhiLi(user_info->getCurrentZhiLi() + zhili);
}
void LayerExercise::menuCallbackEq(CCObject* pSender)
{
	int gold = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->getString());
	int physical = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->getString());
	int eq = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->getString());

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentGold(user_info->getCurrentGold() + gold);
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() + physical);
	user_info->setCurrentEQ(user_info->getCurrentEQ() + eq);
}
void LayerExercise::menuCallbackGanxing(CCObject* pSender)
{
	int gold = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(100))->getString());
	int physical = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(101))->getString());
	int ganxing = atoi(static_cast<CCLabelAtlas*>(__item_tipo->getChildByTag(102))->getString());

	UserInfo* user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentGold(user_info->getCurrentGold() + gold);
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() + physical);
	user_info->setCurrentGanXing(user_info->getCurrentGanXing() + ganxing);
}
void LayerExercise::menuCallbackClose(CCObject* pSender)
{
	this->removeFromParent();
}
void LayerExercise::removeFromParent()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::removeFromParent();
}

bool LayerExercise::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerExercise::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerExercise::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerExercise::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}