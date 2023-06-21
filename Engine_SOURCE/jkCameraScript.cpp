#include "jkCameraScript.h"
#include "jkTransform.h"
#include "jkGameObject.h"
#include "jkTime.h"

namespace jk
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 1.0f * Time::DeltaTime();
		tr->SetPosition(pos);
	}
}