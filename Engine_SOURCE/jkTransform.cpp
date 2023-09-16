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
		// �̵� ȸ�� ũ�� ����
	}

	void Transform::LateUpdate()
	{
		// �������� ���� ��ġ���� ������Ʈ.
		// 1. ���� ��� ����
		// - ũ�� ��ȯ ���
		mWorld = Matrix::Identity;
		Matrix scale = Matrix::CreateScale(mScale);

		// - ȸ�� ��ȯ ���
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
