#include "jkCollisionManager.h"
#include "jkGameObject.h"
#include "jkScene.h"
#include "jkSceneManager.h"
#include "jkLayer.h"
#include "jkCollider2D.h"

namespace jk
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

    void CollisionManager::Update()
    {
        for (UINT column = 0; column < (UINT)eLayerType::End; column++)
        {
            for (UINT row = 0; row < (UINT)eLayerType::End; row++)
            {
                if (mMatrix[column][row] == true)
                {
                    LayerCollision((eLayerType)column, (eLayerType)row);
                }
            }
        }
    }

    void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
    {
        Scene* activeScene = SceneManager::GetActiveScene();

        const std::vector<GameObject*>& lefts
            = activeScene->GetLayer(left).GetGameObjects();
        const std::vector<GameObject*>& rights
            = activeScene->GetLayer(right).GetGameObjects();

        for (GameObject* leftObj : lefts)
        {
            Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
            if (leftCol == nullptr)
                continue;
            //if (leftObj->GetState()
            //    != GameObject::eState::Active)
            //    continue;

            if (leftObj->GetState()
                == GameObject::eState::Dead)
                continue;


            for (GameObject* rightObj : rights)
            {
                Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
                if (rightCol == nullptr)
                    continue;
                if (leftObj == rightObj)
                    continue;
                //if (rightObj->GetState()
                //    != GameObject::eState::Active)
                //    continue;

                if (rightObj->GetState()
                    == GameObject::eState::Dead)
                    continue;

                ColliderCollision(leftCol, rightCol);
            }
        }
    }

    void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
    {
        // 두 충돌체의 ID bool값을 확인
        ColliderID id = {};
        id.left = left->GetColliderID();
        id.right = right->GetColliderID();

        // 충돌정보를 가져온다
        std::map<UINT64, bool>::iterator iter
            = mCollisionMap.find(id.id);

        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(id.id, false));
            iter = mCollisionMap.find(id.id);
        }

        if (left->GetOwner()->GetState() == GameObject::eState::Paused
            || right->GetOwner()->GetState() == GameObject::eState::Paused)
        {
            left->OnCollisionExit(right);
            right->OnCollisionExit(left);

            iter->second = false;

            return;
        }


        if (Intersect(left, right))
        {

            // 충돌
            if (iter->second == false)
            {
                //최초 충돌
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);      
                iter->second = true;
         
            }
            else
            {
                // 충돌 중
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
                left->SetColorcheck(-1);
                right->SetColorcheck(-1);

                if (iter->second == true)
                    return;
            }
            iter->second = true;

        }
        else
        {
            // 충돌 X
            if (iter->second == true)
            {
                // 충돌하고 있다가 나갈떄
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);
                left->SetColorcheck(1);
                right->SetColorcheck(1);

                iter->second = false;
            }
        }
    }

    bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
    {

        //사각형 충돌 정보 만들기   
        //Vector3 leftPos = left->GetPosition();
        //Vector3 rightPos = right->GetPosition();
        //Vector2 leftSize = left->GetSize();
        //Vector2 rightSize = right->GetSize();

        ////원형 충돌 정보 만들기      
        //float leftradius = 0;
        //float rightradius = 0;
        //{
        //    if (leftSize.x > leftSize.y)
        //        leftradius = leftSize.x / 2;
        //    else
        //        leftradius = leftSize.y / 2;

        //    if (rightSize.x > rightSize.y)
        //        rightradius = rightSize.x / 2;
        //    else
        //        rightradius = rightSize.y / 2;
        //}

        //사각형충돌
        //if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
        //   && fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
        //{
        //   int a = 0;
        //   return true;
        //}

        // 원형충돌
        //float radiusSum = leftradius + rightradius;      
        //float distance = Vector3::Distance(leftPos, rightPos);
        //if (distance < leftradius + rightradius)
        //{
        //   int a = 0;
        //   return true;
        //}


        // OBB 충돌
        // Rect vs Rect 
        // 0 --- 1
        // |     |
        // 3 --- 2
        Vector3 arrLocalPos[4] =
        {
           Vector3{-0.5f, 0.5f, 0.0f}
           ,Vector3{0.5f, 0.5f, 0.0f}
           ,Vector3{0.5f, -0.5f, 0.0f}
           ,Vector3{-0.5f, -0.5f, 0.0f}
        };

        Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
        Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

        Matrix leftMatrix = leftTr->GetMatrix();
        Matrix rightMatrix = rightTr->GetMatrix();

        Vector3 Axis[4] = {};

        Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
        Matrix finalLeft = Matrix::CreateScale(leftScale);
        finalLeft *= leftMatrix;

        Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
        Matrix finalRight = Matrix::CreateScale(rightScale);
        finalRight *= rightMatrix;

        Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
        Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
        Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
        Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

        Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
        Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
        Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
        Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

        for (size_t i = 0; i < 4; i++)
            Axis[i].z = 0.0f;

        Vector3 vc = left->GetPosition() - right->GetPosition();
        vc.z = 0.0f;

        Vector3 centerDir = vc;
        for (size_t i = 0; i < 4; i++)
        {
            Vector3 vA = Axis[i];

            float projDistance = 0.0f;
            for (size_t j = 0; j < 4; j++)
            {
                projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
            }

            if (projDistance < fabsf(centerDir.Dot(vA)))
                return false;
        }

        return true;
    }

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}