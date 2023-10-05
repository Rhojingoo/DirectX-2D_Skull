#include "Sound.h"

namespace jk
{
	Sound::Sound()
	{
	}
	Sound::~Sound()
	{
	}
	void Sound::Initialize()
	{
		GameObject::Initialize();
	}
	void Sound::Update()
	{
		GameObject::Update();
	}
	void Sound::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Sound::Render()
	{
		GameObject::Render();
	}
	void Sound::OnCollisionEnter(Collider2D* other)
	{
	}
	void Sound::OnCollisionStay(Collider2D* other)
	{
	}
	void Sound::OnCollisionExit(Collider2D* other)
	{
	}
}