#pragma once
#include "jkGameObject.h"
#include "jkMeshRenderer.h"
#include "jkTransform.h"

namespace jk
{
	class Cloud : public GameObject
	{
	public:
		enum class CloudType
		{
			UVMode,
			NoneUVMode,
		};

		Cloud();
		Cloud(Vector3 mPos);
		virtual ~Cloud();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		CloudType mCloudType;
		MeshRenderer* meshrenderer;
		Transform* tr;
		float mTime;
		Vector3 _Pos;
		Vector3 _mPos;
	};
}