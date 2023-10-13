#include "jkAudioClip.h"
#include "jkTransform.h"

namespace jk
{
	AudioClip::AudioClip()
		: Resource(eResourceType::AudioClip)
		, mChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1e10f)
		, mbLoop(false)		
	{

	}

	AudioClip::~AudioClip()
	{
	}

	HRESULT AudioClip::Load(const std::wstring& path, const std::string& soundID)
	{
		std::string cPath(path.begin(), path.end());
		FMOD::Sound* newSound;
		if (!Fmod::CreateSound(cPath, &newSound))
			return S_FALSE;

		if (mSounds.find(soundID) != mSounds.end()) {
			
			return S_FALSE;
		}

		mSounds[soundID] = newSound;
		return S_OK;
	}

	void AudioClip::Play(const std::string& soundID)
	{
		auto it = mSounds.find(soundID);
		if (it != mSounds.end())
		{
			FMOD::Channel* channel = nullptr;
			auto channelIt = mChannels.find(soundID);

			if (channelIt != mChannels.end())
			{
				channel = channelIt->second;
				bool isPlaying = false;
				channel->isPlaying(&isPlaying);

				if (isPlaying)
					return;  // 혹은 채널을 새로 생성하여 오버랩 되게 할 수 있습니다.
			}

			Fmod::SoundPlay(it->second, &channel);

			if (mbLoop)
				channel->setMode(FMOD_LOOP_NORMAL);
			else
				channel->setMode(FMOD_LOOP_OFF);

			mChannels[soundID] = channel;  // 채널 업데이트 혹은 저장
		}

	}

	void AudioClip::Stop(const std::string& soundID)
	{

		auto it = mChannels.find(soundID);
		if (it != mChannels.end())
		{
			it->second->stop();
		}
	}

	void AudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
	{

		for (auto& [id, channel] : mChannels)
		{
			FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
			FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

			channel->set3DAttributes(&fmodPos, &fmodVel);
		}
	}
}

