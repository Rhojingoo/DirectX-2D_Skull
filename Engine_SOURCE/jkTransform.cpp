#include "jkTransform.h"
#include "jkRenderer.h"
#include "jkConstantBuffer.h"
#include "jkCamera.h"

namespace jk
{
	using namespace jk::graphics;
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
	{//iloveyou
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		// 이동 회전 크기 변경
	}

	void Transform::LateUpdate()
	{
		// 렌더링에 사용될 위치값을 업데이트.
		// 1. 월드 행렬 생성
		// - 크기 변환 행렬
		mWorld = Matrix::Identity;
		Matrix scale = Matrix::CreateScale(mScale);

		// - 회전 변환 행렬
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);


		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}




	void Transform::Render()
	{

	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.world = mWorld;
		trCB.view = Camera::GetGpuViewMatrix();
		trCB.projection = Camera::GetGpuProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
	}
}
