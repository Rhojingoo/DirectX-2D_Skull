#pragma once
#include "Include_Common.h"

namespace jk
{
	class Mini_Boss : public GameObject
	{
	public:
		Mini_Boss();
		virtual ~Mini_Boss();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetPlayer(GameObject* set) { _player = set; }
		GameObject* Getplayer() { return _player; }
		Vector3 GetPlayerPos() { return _playerpos; }

	private : 
		static GameObject* _player;
		Vector3 _playerpos = Vector3( 0.f,0.f,0.f );
	
	};
}