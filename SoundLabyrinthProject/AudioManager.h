#pragma once
#include "Singleton.h"
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Implementation {
	Implementation();
	~Implementation();

	void Update();

	FMOD::Studio::System* mpStudioSystem;
	FMOD::System* mpSystem;

	int mnNextChannelId;
	typedef map<string, FMOD::Sound*> SoundMap;
	typedef map<int, FMOD::Channel*> ChannelMap;

	SoundMap mSounds;
	ChannelMap mChannels;
};

class AudioManager
{

public:
	friend class Singleton<AudioManager>;

private:
	AudioManager();
	AudioManager(const AudioManager&);
	~AudioManager();

public:

	void Init();
	void Update();
	void Shutdown();

	static int ErrorCheck(FMOD_RESULT result);
	void LoadSound(const string &strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	void UnLoadSound(const string &strSoundName);
	int PlaySounds(const string &strSoundName, float pitch = 1.0f);

	Implementation* sgpImplementation = nullptr;

};

typedef Singleton<AudioManager> Audio;