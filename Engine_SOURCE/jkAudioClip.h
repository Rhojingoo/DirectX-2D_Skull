#pragma once
#include "jkResource.h"
#include "jkFmod.h"

//#include <Fmod/fmod_studio.hpp>
//#include <Fmod/fmod.hpp>
//#include <Fmod/fmod_common.h>
//#include <Fmod/fmod_codec.h>

//#include "..\External\Include\\DirectXTex\DirectXTex.h"

namespace jk
{
	using namespace jk::math;
	class AudioClip : public Resource
	{
		public:
			AudioClip();
			~AudioClip();

			virtual HRESULT Load(const std::wstring& path) override { return 0; };
			virtual HRESULT Load(const std::wstring& path, const std::string& soundID);
			void Play(const std::string& soundID);
			void Stop(const std::string& soundID);
			void Set3DAttributes(const Vector3 pos, const Vector3 vel);
			void SetLoop(bool loop) { mbLoop = loop; }

		private:
			std::map<std::string, FMOD::Sound*> mSounds;
			std::map<std::string, FMOD::Channel*> mChannels;
			FMOD::Channel* mChannel;
			bool mbLoop;
			float mMinDistance;
			float mMaxDistance;
	};
}

