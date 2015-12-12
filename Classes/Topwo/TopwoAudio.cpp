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
	//Ԥ��������
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(AUDIO_MUSIC_GAME_BJ);

	//Ԥ������Ч
	SimpleAudioEngine::sharedEngine()->preloadEffect(AUDIO_EFFECT_BUTTON);

	return true;
}

//��ȡ����״̬
twbool TopwoAudio::getSoundState(twbool is_switch)
{
	twbool sound_state1 = false, sound_state2 = false;
	sound_state1 = getEffectState(is_switch);
	sound_state2 = getMusicState(is_switch);
	return sound_state1 || sound_state2;
}
//��ȡ��Ч״̬
twbool TopwoAudio::getEffectState(twbool is_switch)
{
	if (is_switch)
	{//��Ҫ������Ч����
		//�Ȳ���һ����Ч����
		__is_effect = (!__is_effect);

		//������֮�����Ч״̬
		if (!__is_effect)
		{//��ǰ��Ч״̬�ǹ��ŵģ��ǾͰ����ڲ��ŵ���Чͣ��
			SimpleAudioEngine::sharedEngine()->stopAllEffects();
		}
	}

	return __is_effect;
}
//��ȡ����״̬
twbool TopwoAudio::getMusicState(twbool is_switch)
{
	if (is_switch)
	{//��Ҫ�������ֿ���
		//�Ȳ���һ�����ֿ���
		__is_music = (!__is_music);

		//������֮�������״̬
		if (!__is_music)
		{//��ǰ��Ч״̬�ǹ��ŵģ��ǾͰ����ڲ��ŵ�������ͣ
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
		else
		{//��ǰ��Ч״̬�ǿ��ŵģ��ǾͰѼ�����������
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
	}

	return __is_music;
}

//������Ч
bool TopwoAudio::playEffect(const char* effect)
{
	if (!__is_effect)
	{
		return false;
	}

	SimpleAudioEngine::sharedEngine()->playEffect(effect);
	return true;
}

//��������
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