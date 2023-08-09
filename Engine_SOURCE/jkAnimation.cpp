#include "jkAnimation.h"
#include "jkTime.h"
#include "jkAnimator.h"
#include "jkRenderer.h"
#include "jkConstantBuffer.h"


namespace jk
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{

	}

	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;

			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
				mbComplete = true;
			}
		}
	}
	void Animation::Render()
	{
	}

	//Create(key, mImageAtlas, Vector2(0.0), Vector2(width, height), fileCount);
	void Animation::Create(std::wstring name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		SetKey(name);
		mAtlas = atlas;

		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		//Vector2 mAtlasSize = Vector2(atlas.get()->GetWidth(), atlas.get()->GetHeight());

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(size.x / width, size.y / height);
			//sprite.atlasSize = Vector2(1000.0f / width, 1000.0f / height);
			//sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);
			sprite.duration = duration;

			mSprites.push_back(sprite);
		}

	}

	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShader(graphics::eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = 1;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}
}