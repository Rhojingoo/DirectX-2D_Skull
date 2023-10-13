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

		void Play(const std::string& soundID);

		void Stop(const std::string& soundID);

		void SetLoop(bool loop);

		void SetClipAndLoad(const std::wstring& path, const std::string& soundID);
	//	void SetClipAndLoad(std::shared_ptr<AudioClip> clip, const std::string& soundID);
		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }	


		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }

	private:
		std::shared_ptr<AudioClip> mAudioClip;

	};
}
