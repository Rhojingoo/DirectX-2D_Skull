#pragma once
#include "Include_Common.h"

namespace jk
{
	class Alpha_Blend : public GameObject
	{
	public:
		Alpha_Blend();
		virtual ~Alpha_Blend();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		void BindConstantBuffer();

	private:
		Vector3 _Pos = Vector3();
		float _Time = 0.f;
		float mTime = 0.f;
	};
}