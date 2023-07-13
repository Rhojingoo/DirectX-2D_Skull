#pragma once
#include "Include_Common.h"
#include "BG.h"

namespace jk
{
	class Cloud : public BG
	{
	public:
		Cloud();
		Cloud(Vector3 mPos);
		virtual ~Cloud();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

	private:		
		MeshRenderer* meshrenderer;
		Transform* tr;
		float mTime;
		float _Time;
		Vector3 _Pos;
	};
}