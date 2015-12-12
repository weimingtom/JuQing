#include "TopwoAudio.h"

TopwoAudio::TopwoAudio()
:__is_effect(true)
, __is_music(true)
{
}

TopwoAudio::~TopwoAudio()
{
}

bool TopwoAudio::init()
{
	//预加载音乐
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(AUDIO_MUSIC_GAME_BJ);

	//预加载音效
	SimpleAudioEngine::sharedEngine()->preloadEffect(AUDIO_EFFECT_BUTTON);

	return true;
}

//获取声音状态
twbool TopwoAudio::getSoundState(twbool is_switch)
{
	twbool sound_state1 = false, sound_state2 = false;
	sound_state1 = getEffectState(is_switch);
	sound_state2 = getMusicState(is_switch);
	return sound_state1 || sound_state2;
}
//获取音效状态
twbool TopwoAudio::getEffectState(twbool is_switch)
{
	if (is_switch)
	{//需要拨动音效开关
		//先拨动一下音效开关
		__is_effect = (!__is_effect);

		//拨动完之后的音效状态
		if (!__is_effect)
		{//当前音效状态是关着的，那就把正在播放的音效停掉
			SimpleAudioEngine::sharedEngine()->stopAllEffects();
		}
	}

	return __is_effect;
}
//获取音乐状态
twbool TopwoAudio::getMusicState(twbool is_switch)
{
	if (is_switch)
	{//需要拨动音乐开关
		//先拨动一下音乐开关
		__is_music = (!__is_music);

		//拨动完之后的音乐状态
		if (!__is_music)
		{//当前音效状态是关着的，那就把正在播放的音乐暂停
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
		else
		{//当前音效状态是开着的，那就把继续播放音乐
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
	}

	return __is_music;
}

//播放音效
bool TopwoAudio::playEffect(const char* effect)
{
	if (!__is_effect)
	{
		return false;
	}

	SimpleAudioEngine::sharedEngine()->playEffect(effect);
	return true;
}

//播放音乐
bool TopwoAudio::playMusic(const char* music)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(music, true);

	if (!__is_music)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		return false;
	}
	return true;
}