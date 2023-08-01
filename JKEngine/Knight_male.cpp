#include "Knight_male.h"


namespace jk
{
	int Knight_male::mDir = 1;
	bool Knight_male::_switch = false;

	Knight_male::Knight_male()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Knight_male::~Knight_male()
	{
	}
	void Knight_male::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		//_rigidbody = AddComponent<RigidBody>();
		//_rigidbody->SetMass(1.f);

		//Skul_Head = new Skul_head();
		//Skul_Head->Initialize();
		//Scene* scene = SceneManager::GetActiveScene();
		//scene->AddGameObject(eLayerType::Item, Skul_Head);
		//Transform* tr_head = Skul_Head->GetComponent<Transform>();
		//tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
		//Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
		//Skul_Head->SetState(eState::Paused);

		at = AddComponent<Animator>();
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_A", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_B", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_C", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_D", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_E", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\BackDash", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Die", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\EnergeBall", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Explosion_Loop", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Glorggy", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Hit", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Intro", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Jump", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\LOL", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Potion", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger_Ready", this);

		//at->PlayAnimation(L"Knight_maleAttack_A", true);

		GameObject::Initialize();
	}
	void Knight_male::Update()
	{
		GameObject::Update();
	}
	void Knight_male::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Knight_male::Render()
	{
		GameObject::Render();
	}
	void Knight_male::OnCollisionEnter(Collider2D* other)
	{
	}
	void Knight_male::OnCollisionStay(Collider2D* other)
	{
	}
	void Knight_male::OnCollisionExit(Collider2D* other)
	{
	}
}