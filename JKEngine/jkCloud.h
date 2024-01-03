#pragma once
#include "BG.h"

namespace jk
{
	class Cloud : public BG
	{
	public:
		Cloud(const std::wstring& path);
		Cloud(Vector3 _Pos);
		virtual ~Cloud();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

	private:		
		class MeshRenderer* _MeshRenderer;
		Transform* tr;
		float _Time;
		float _Time2;
		Vector3 _Pos;
	};
}