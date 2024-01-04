#include "Main_Camera.h"
#include "Include_Common.h"


namespace jk
{
	Main_Camera::Main_Camera()
	{
	
	}
	Main_Camera::~Main_Camera()
	{
	}
	void Main_Camera::Initialize()
	{
		GameObject::Initialize();
	}
	void Main_Camera::Update()
	{
		GameObject::Update();
	}
	void Main_Camera::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Main_Camera::Render()
	{
		GameObject::Render();
	}
}