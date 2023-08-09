#include "jkAnimator.h"
#include "jkResources.h"


namespace jk
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, reverse(0)
	{
	}


	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}


		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}


	void Animator::Initialize()
	{
	}


	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		if (mActiveAnimation->IsComplete() && mbLoop)
		{
			Events* events
				= FindEvents(mActiveAnimation->GetKey());
			if (events)
				events->completeEvent();

			mActiveAnimation->Reset();
		}

		mActiveAnimation->LateUpdate();
	}


	void Animator::LateUpdate()
	{
	}


	void Animator::Render()
	{
	}

	//Create(key, mImageAtlas, Vector2(0.0), Vector2(width, height), fileCount);
	void Animator::Create(const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetKey(name);

		animation->Create(name
			, atlas
			, leftTop
			, size
			, columnLength
			, offset
			, duration);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (events != nullptr)
			return;

		events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}

	Animation* Animator::CreateAnimations(const std::wstring& path, GameObject* OBJ, int reverse_check)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;
		UINT Scanbos_H = 100;
		reverse = reverse_check;

		std::filesystem::path fs(path);
		std::vector<std::shared_ptr<Texture>> textures = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path().wstring(); // Use the full path from the iterator
			const std::wstring ext = p.path().extension();

			std::shared_ptr<Texture> tex = Resources::Load<Texture>(fileName, fullName);

			if (width < tex->GetWidth())
			{
				width = tex->GetWidth();
			}
			if (height < tex->GetHeight())
			{
				height = tex->GetHeight();
			}

			textures.push_back(tex);

			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		if (reverse == 0 )
		{	
			key += fs.filename();
		}
		else if (reverse == 1)
		{			
			key += fs.filename();
			key += L"R";
		}

		GameObject* ScaleSet = OBJ;
		ScaleSet->GetComponent<Transform>()->SetScale(Vector3(width , height, 1.0f));
		Collider2D* ColSET = OBJ->GetComponent<Collider2D>();
		ColSET->SetSize(Vector2(width/ fileCount, height/ fileCount));
		//ScaleSet->GetComponent<Transform>()->SetScale(Vector3(width* fileCount, height* fileCount, 1.0f));

		mImageAtlas = std::make_shared<graphics::Texture>();
		mImageAtlas->CreateTex(path, width, height, fileCount, reverse);

		Create(key, mImageAtlas, Vector2(0.0), Vector2(width, height), fileCount);

		return nullptr;
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}


	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;

		Events* events;
		if (prevAnimation != nullptr)
		{
			events = FindEvents(prevAnimation->GetKey());
			if (events)
				events->endEvent();
		}

		Animation* animation = FindAnimation(name);
		if (animation)
		{
			mActiveAnimation = animation;
		}

		events = FindEvents(mActiveAnimation->GetKey());
		if (events)
			events->startEvent();

		mbLoop = loop;
		mActiveAnimation->Reset();
	}


	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Binds();
	}


	std::function<void()>& Animator::StartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->startEvent.mEvent;
	}


	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->endEvent.mEvent;
	}
}
