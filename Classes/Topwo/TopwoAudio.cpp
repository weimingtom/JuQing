#include "TopwoAudio.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

TopwoAudio::TopwoAudio()
:__is_effect(true)
, __is_music(true)
, __playing_music_id(0)
{
}

TopwoAudio::~TopwoAudio()
{
}

bool TopwoAudio::init()
{
	//预加载音乐
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(getMusicById(1));
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(getMusicById(2));

	//预加载音效
	SimpleAudioEngine::sharedEngine()->preloadEffect(getEffectById(1));

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
bool TopwoAudio::playEffect(int effect_id)
{
	if (!__is_effect)
	{
		return false;
	}

	SimpleAudioEngine::sharedEngine()->playEffect(getEffectById(effect_id));
	return true;
}

//播放音乐
bool TopwoAudio::playMusic(int music_id)
{
	if (__playing_music_id != music_id)
	{
		__playing_music_id = music_id;
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(getMusicById(music_id), true);
	}

	if (!__is_music)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		return false;
	}
	return true;
}
const char* TopwoAudio::getMusicById(int id)
{
	const char* ret = "";
	switch (id)
	{
	case 1:
		ret = "audios/music_bg_home.mp3";
		break;
	case 2:
		ret = "audios/music_bg_dialog.mp3";
		break;
	default:
		break;
	}
	return ret;
}
const char* TopwoAudio::getEffectById(int id)
{
	const char* ret = "";
	switch (id)
	{
	case 1:
		ret = "audios/effect_button.mp3";
		break;
	default:
		break;
	}
	return ret;
}