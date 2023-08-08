#include "Attack_HitBox.h"

namespace jk
{
     Attack_HitBox::Attack_HitBox()
    {
         MeshRenderer* mr = AddComponent<MeshRenderer>();
         mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
         mr->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
    }

    Attack_HitBox::~Attack_HitBox()
    {
    }

    void Attack_HitBox::Initialize()
    {        
        _collider = AddComponent<Collider2D>();
        _collider->SetSize(Vector2(150.f, 150.f));
        _collider->SetPosition(Vector3(0.f, 0.f, -250.f));
        GameObject::Initialize();
    }

    void Attack_HitBox::Update()
    {
        GameObject::Update();
    }

    void Attack_HitBox::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Attack_HitBox::Render()
    {
        GameObject::Render();
    }

    void Attack_HitBox::OnCollisionEnter(Collider2D* other)
    {
    }

    void Attack_HitBox::OnCollisionStay(Collider2D* other)
    {
    }

    void Attack_HitBox::OnCollisionExit(Collider2D* other)
    {
    }

}
