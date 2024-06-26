#pragma once
#include "jkGameObject.h"


namespace jk
{
	class Attack_HitBox : public GameObject
	{
	public:
		Attack_HitBox();
		virtual ~Attack_HitBox();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);	
		
	};
}