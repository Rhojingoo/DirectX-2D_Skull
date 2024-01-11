#include "jkCollider2D.h"
#include "jkGameObject.h"
#include "jkRenderer.h"
#include "jkInput.h"

namespace jk
{	
	int Collider2D::_ColSwitch = 1;
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, _Scale(Vector2::One)
		, mCenter(Vector2::Zero)
		, _Colcheck(1)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}

	Collider2D::~Collider2D()
	{
	}

	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider2D::Update()
	{
		if (Input::GetKeyDown(eKeyCode::P))
		{
			_ColSwitch = -1;
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			_ColSwitch = 1;
		}
	}

	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 rotation =  tr->GetRotation();
		const float pi = 3.141592f;
		XM_PI;
		float degree = 180.f/ pi;
		rotation = rotation * degree;

		_Scale = tr->GetScale();
		_Scale.x *= mSize.x;
		_Scale.y *= mSize.y;
		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;
		mPosition = pos;


		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = _Scale;
		mesh.rotation = rotation; 
		mesh.type = mType;

	


		if (_ColSwitch == 1)
		{
			renderer::PushDebugMeshAttribute(mesh);
		}
	}

	void Collider2D::Render()
	{
		renderer::MoveCB trCB = {};
		trCB.mTime.x = _Colcheck;
		
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Move];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::PS);
	}

	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		GetOwner()->OnCollisionEnter(other);
	
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();
		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}

	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		GetOwner()->OnCollisionStay(other);

		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();
		for (Script* script : scripts)
		{			
			script->OnCollisionStay(other);
		}
	}

	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		GetOwner()->OnCollisionExit(other);
		
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();
		for (Script* script : scripts)
		{		
			script->OnCollisionExit(other);
		}
	}
}
