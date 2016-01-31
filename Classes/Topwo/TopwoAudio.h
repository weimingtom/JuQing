#ifndef __TOPWO_AUDIO_H__
#define __TOPWO_AUDIO_H__
#include "cocos2d.h"
using namespace cocos2d;
#include "TopwoDefine.h"

//音频类
class TopwoAudio : public CCObject
{
public:
	TopwoAudio();
	virtual ~TopwoAudio();
	virtual bool init();
	CREATE_FUNC(TopwoAudio);

	//声音
	twbool getSoundState(twbool is_switch);
	twbool getEffectState(twbool is_switch);
	twbool getMusicState(twbool is_switch);

	bool playEffect(int effect_id);
	bool playMusic(int music_id);
private:
	const char* getMusicById(int id);
	const char* getEffectById(int id);

	twbool __is_effect;//音效开关
	twbool __is_music;//音乐开关
	int __playing_music_id;
};

#endif  //__TOPWO_AUDIO_H__
