#pragma once
#include "jkComponent.h"
#include "jkAudioClip.h"

namespace jk
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Play();
		void Play(const std::string& name, bool loop = false);
		void Stop();
		void Stop(const std::string& name);
		void SetLoop(bool loop);


		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }	
		void AddClip(const std::string& name, std::shared_ptr<AudioClip> clip)	{mAudioClips[name] = clip;}

		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }
		std::shared_ptr<AudioClip> GetClip(const std::string& name)
		{
			auto it = mAudioClips.find(name);
			if (it != mAudioClips.end())
				return it->second;
			else
				return nullptr;
		}


	private:
		std::shared_ptr<AudioClip> mAudioClip;
		std::unordered_map<std::string, std::shared_ptr<AudioClip>> mAudioClips;
	};
}
