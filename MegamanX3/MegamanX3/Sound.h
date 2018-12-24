#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__
#include<dsound.h>
#include<Windows.h>
#include<map>
#include"Global.h"
//============================================================
//BackGround
//============================================================
#define SOUND_MEGAMANDIE "SourceSound//megaman_die.wav"
#define SOUND_MEGAMAN_SHOOTLV1 "SourceSound//shootlevel1.wav"
#define SOUND_MEGAMAN_SHOOTLV2 "SourceSound//shootlevel2.wav"
#define SOUND_ENEMIDISTROY "SourceSound//enemi_destroy.wav" //====
#define SOUND_GET_ITEM "SourceSound//get_item.wav" //=====
#define SOUND_MEGAMAN_JUMP "SourceSound//megaman_jump.wav"



class Sound
{
public:
	struct WaveHeader
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
private:
	static Sound*				__instance;
	std::map<std::string, IDirectSoundBuffer8*> _listSoundBuffer;
	bool						_isMute;
	IDirectSoundBuffer*			_primaryBuffer;
	IDirectSound8*				_soundDevice;
	float						_volumne;
public:
	~Sound();
	static Sound*				Instance();
	void						setVolume(float percentage, std::string name = "");
	void						play(std::string name, bool isLoop = false, int times = 1, float volumne = -1);
	void						stop(std::string name = "");
	void						SetMute() { this->_isMute = !this->_isMute; }

private:
	Sound();
	void						init();
	void						loadSound(char* path);
	

};

#endif __SOUND_H__