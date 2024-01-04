#pragma once
#include "jkGameObject.h"


namespace jk
{
	class HP_Frame : public GameObject
	{
	public:
		HP_Frame(const std::wstring& path);
		virtual ~HP_Frame();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		void SetSwitch(bool set) { _SwitchOn = set; }	

	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

		int	mDir = 1;
		bool	_SwitchOn = false;
	};
}