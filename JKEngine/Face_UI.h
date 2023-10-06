#pragma once
#include "Include_Common.h"

namespace jk
{
	class Face_UI : public GameObject
	{
	public:
		Face_UI(const std::wstring& path);
		virtual ~Face_UI();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;
	};
}