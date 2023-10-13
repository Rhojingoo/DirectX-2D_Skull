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
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play(const std::string& soundID)
	{
		mAudioClip->Play(soundID);
	}

	void AudioSource::Stop(const std::string& soundID)
	{
		mAudioClip->Stop(soundID);
	}

	void AudioSource::SetClipAndLoad(const std::wstring& path, const std::string& soundID)
	{
		if (!mAudioClip) {
			mAudioClip = std::make_shared<AudioClip>();
		}
		mAudioClip->Load(path, soundID);
	}

	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
}