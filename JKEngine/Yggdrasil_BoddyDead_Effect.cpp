#include "Yggdrasil_BoddyDead_Effect.h"

namespace jk
{
	Yggdrasil_BoddyDead_Effect::Yggdrasil_BoddyDead_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_BoddyDead_Effect::~Yggdrasil_BoddyDead_Effect()
	{
	}
	void Yggdrasil_BoddyDead_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();		
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Die_Effect", this, 0);

		
		at->PlayAnimation(L"BodyYggdrasilBody_Die_Effect", false);
		GameObject::Initialize();
	}
	void Yggdrasil_BoddyDead_Effect::Update()
	{

		mTime = static_cast<float>(Time::DeltaTime());
		if (mTime > 1)
		{
			this->SetState(eState::Paused);
		}

		GameObject::Update();
	}
	void Yggdrasil_BoddyDead_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_BoddyDead_Effect::Render()
	{		
		GameObject::Render();
	}

	void Yggdrasil_BoddyDead_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_BoddyDead_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_BoddyDead_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_BoddyDead_Effect::AlphaEffect_Start()
	{
		//at->PlayAnimation(L"BodyYggdrasilBody_Die_Effect", false);
	}
	void Yggdrasil_BoddyDead_Effect::AlphaEffect_End()
	{
	}
	void Yggdrasil_BoddyDead_Effect::BindConstantBuffer()
	{
		renderer::_AlphaBlendCB _Alphacb = {};
		_Alphacb._Alpha.x = mTime;
		_Alphacb._Alpha.y = _Time;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::AlphaBlend];
		cb->SetData(&_Alphacb);
		cb->Bind(eShaderStage::PS);
	}
	void Yggdrasil_BoddyDead_Effect::Compelete()
	{
	}


}