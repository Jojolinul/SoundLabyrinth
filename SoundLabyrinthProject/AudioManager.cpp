#include "AudioManager.h"

Implementation::Implementation() 
{

	mpStudioSystem = NULL;
	AudioManager::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	AudioManager::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

	mpSystem = NULL;
	AudioManager::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));

}

Implementation::~Implementation()
{

	AudioManager::ErrorCheck(mpStudioSystem->unloadAll());
	AudioManager::ErrorCheck(mpStudioSystem->release());

}

void Implementation::Update()
{

	vector<ChannelMap::iterator> pStoppedChannels;
	for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
	{
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		if (!bIsPlaying)
		{
			pStoppedChannels.push_back(it);
		}
	}
	for (auto& it : pStoppedChannels)
	{
		mChannels.erase(it);
	}
	AudioManager::ErrorCheck(mpStudioSystem->update());

}

AudioManager::AudioManager()
{
	
}

void AudioManager::Init()
{
	sgpImplementation = new Implementation;
}

void AudioManager::Update()
{
	sgpImplementation->Update();
}

void AudioManager::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt != sgpImplementation->mSounds.end())
		return;

	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= b3d ? FMOD_3D : FMOD_2D;
	eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* pSound = nullptr;
	AudioManager::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
	if (pSound) {
		sgpImplementation->mSounds[strSoundName] = pSound;
	}

}

void AudioManager::UnLoadSound(const std::string& strSoundName)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
		return;

	AudioManager::ErrorCheck(tFoundIt->second->release());
	sgpImplementation->mSounds.erase(tFoundIt);
}

int AudioManager::PlaySounds(const string& strSoundName, float pitch)
{
	int nChannelId = sgpImplementation->mnNextChannelId;
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	
	FMOD::Channel* pChannel = nullptr;
	AudioManager::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
	if (pChannel)
	{

		AudioManager::ErrorCheck(pChannel->setPaused(false));
		AudioManager::ErrorCheck(pChannel->setPitch(pitch));
		sgpImplementation->mChannels[nChannelId] = pChannel;
	}
	return nChannelId;
}


int AudioManager::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		cout << "FMOD ERROR " << result << endl;
		return 1;
	}
	return 0;
}

void AudioManager::Shutdown()
{
	delete sgpImplementation;
}

AudioManager::~AudioManager()
{
}
