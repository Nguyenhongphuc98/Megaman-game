#include "Sound.h"

Sound*			Sound::__instance = nullptr;

Sound::Sound()
{
	this->init();
	this->_isMute = false;
	this->loadSound((char*)SOUND_MEGAMANDIE);
	this->loadSound((char*)SOUND_MEGAMAN_SHOOTLV1);
	this->loadSound((char*)SOUND_MEGAMAN_SHOOTLV2);
	this->loadSound((char*)SOUND_ENEMIDISTROY);
	this->loadSound((char*)SOUND_GET_ITEM);
	this->loadSound((char*)SOUND_MEGAMAN_JUMP);
}

void Sound::init()
{
	this->_primaryBuffer = 0;
	HRESULT result;

	DSBUFFERDESC bufferDesc; //describe the buffer

	result = DirectSoundCreate8(NULL, &this->_soundDevice, NULL);

	if (FAILED(result))
	{
		//Global::GLPostMessage("Can not create device");
	}

	result = this->_soundDevice->SetCooperativeLevel(G_hWnd, DSSCL_PRIORITY); // set the cooperative level.

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = this->_soundDevice->CreateSoundBuffer(&bufferDesc, &_primaryBuffer, NULL);

	if (FAILED(result))
	{
		//Global::GLPostMessage("Can not create primaryBuffer");
	}
	this->_volumne = 100.0f;
	this->_isMute = false;
}


Sound::~Sound()
{
}

Sound* Sound::Instance()
{
	if (!__instance)
		__instance = new Sound();
	return __instance;
}


void Sound::setVolume(float percentage, std::string name)
{
	this->_volumne = percentage;
	//set all
	if (name == "")
	{
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (auto buffer = this->_listSoundBuffer.begin(); buffer != this->_listSoundBuffer.end(); buffer++)
			buffer->second->SetVolume(volumne);
	}
	else
	{
		auto buffer = this->_listSoundBuffer.find(name);
		if (buffer == this->_listSoundBuffer.end())
			return;
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		buffer->second->SetVolume(volumne);
	}
}

void Sound::play(std::string name, bool isLoop, int times, float volumne)
{
	if (name == "")
		return;

	if (volumne != -1)
		this->setVolume(volumne, name);

	//If player want to mute -> don't play sound
	if (this->_isMute)
		return;

	//get buffer
	auto buffer = this->_listSoundBuffer.find(name);

	//If the name is not exists => load it
	if (buffer == this->_listSoundBuffer.end())
	{
		this->loadSound((char*)name.c_str());
		buffer = this->_listSoundBuffer.find(name);
	}

	if (isLoop)
		buffer->second->Play(0, 0, DSBPLAY_LOOPING);
	else
	{
		buffer->second->Stop();
		buffer->second->SetCurrentPosition(0);
		buffer->second->Play(0, 0, times - 1);
	}
}

void Sound::stop(std::string name)
{
	if (name == "")
	{
		for (auto buffer = this->_listSoundBuffer.begin(); buffer != this->_listSoundBuffer.end(); buffer++)
		{
			buffer->second->Stop();
			buffer->second->SetCurrentPosition(0);
		}
	}
	else
	{
		auto buffer = this->_listSoundBuffer.find(name);
		if (buffer == this->_listSoundBuffer.end())
			return;
		buffer->second->Stop();
	}
}


void Sound::loadSound(char * path)
{
	//If exists => go out
	if (this->_listSoundBuffer.find(path) != this->_listSoundBuffer.end())
		return;

	FILE* filePtr;
	WaveHeader waveHeader;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	//Open the file
	int error = fopen_s(&filePtr, path, "rb");
	if (error != 0)
	{
		//Global::GLPostMessage("can't load %s", path);
		return;
	}

	fread(&waveHeader, sizeof(waveHeader), 1, filePtr);
	if ((waveHeader.format[0] != 'W') || (waveHeader.format[1] != 'A') ||
		(waveHeader.format[2] != 'V') || (waveHeader.format[3] != 'E'))
	{
		//Global::GLPostMessage("file format does not support %s", path);
		return;
	}

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeader.sampleRate;
	waveFormat.wBitsPerSample = waveHeader.bitsPerSample;
	waveFormat.nChannels = waveHeader.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;

	this->_soundDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;

	if (FAILED(result))
	{
		//Global::GLPostMessage(" Can not create secondaryBuffers %s", path);
		return;
	}
	fseek(filePtr, sizeof(WaveHeader), SEEK_SET);

	wavData = new unsigned char[waveHeader.dataSize];

	fread(wavData, waveHeader.dataSize, 1, filePtr);

	error = fclose(filePtr);

	if (error != 0)
	{
		//Global::GLPostMessage("Can't close file %s", path);
	}

	result = (*pSecondaryBuffer)->Lock(0, waveHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if (FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeader.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if (wavData != NULL)
		delete wavData;
	wavData = 0;
	long tempVolume = (this->_volumne) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);

	this->_listSoundBuffer[path] = secondaryBuffer;
}


