#include "jkAudioSource.h"

#include "jkAudioClip.h"
#include "jkTransform.h"
#include "jkGameObject.h"

namespace jk
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
	{

	}

	AudioSource::~AudioSource()
	{

	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 forward = tr->Foward();
		
		
		if (mAudioClip)
		{
			mAudioClip->Set3DAttributes(pos, forward);
		}


		for (auto& pair : mAudioClips)
		{
			std::shared_ptr<AudioClip> clip = pair.second;
			if (clip)
			{
				clip->Set3DAttributes(pos, forward);
			}
		}
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}
	void AudioSource::Play(const std::string& name, bool loop)
	{
		auto it = mAudioClips.find(name);
		if (it != mAudioClips.end())
		{
			it->second->Play();
			it->second->SetLoop(loop);
		}
	}


	void AudioSource::Stop()
	{
		mAudioClip->Stop();
	}
	void AudioSource::Stop(const std::string& name)
	{
		auto it = mAudioClips.find(name);
		if (it != mAudioClips.end())
		{
			it->second->Stop();
		}
	}

	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
}