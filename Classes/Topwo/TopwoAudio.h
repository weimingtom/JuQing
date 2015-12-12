#ifndef __TOPWO_AUDIO_H__
#define __TOPWO_AUDIO_H__
#include "cocos2d.h"
using namespace cocos2d;
#include "TopwoDefine.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define AUDIO_EFFECT_BUTTON "audio/button.mp3"
#define AUDIO_EFFECT_WRONG "audio/wrong.mp3"
#define AUDIO_MUSIC_GAME_BJ "audio/bj.mp3"

//������
class TopwoAudio : public CCObject
{
public:
	TopwoAudio();
	virtual ~TopwoAudio();
	virtual bool init();
	CREATE_FUNC(TopwoAudio);

	//����
	twbool getSoundState(twbool is_switch);
	twbool getEffectState(twbool is_switch);
	twbool getMusicState(twbool is_switch);

	bool playEffect(const char* effect);
	bool playMusic(const char* music);
private:

	twbool __is_effect;//��Ч����
	twbool __is_music;//���ֿ���
};

#endif  //__TOPWO_AUDIO_H__
