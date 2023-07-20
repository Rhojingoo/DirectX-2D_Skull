#pragma once
#include "Include_Common.h"


namespace jk
{
	class Mid_GR_1_2 : public BG
	{
	public:
		Mid_GR_1_2();
		virtual ~Mid_GR_1_2();

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