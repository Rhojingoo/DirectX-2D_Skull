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
                if (mMatrix[row] == (1 << column))
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
            if (leftObj->GetState()
                != GameObject::eState::Active)
                continue;

            for (GameObject* rightObj : rights)
            {
                Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
                if (rightCol == nullptr)
                    continue;
                if (leftObj == rightObj)
                    continue;
                if (rightObj->GetState()
                    != GameObject::eState::Active)
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

        if (Intersect(left, right))
        {
            // 충돌
            if (iter->second == false)
            {
                //최초 충돌
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);
            }
            else
            {
                // 충돌 중
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else
        {
            // 충돌 X
            if (iter->second == true)
            {
                // 충돌하고 있다가 나갈떄
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);
            }
        }
    }

    bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
    {

        //사각형 충돌 정보 만들기   
        Vector3 leftPos = left->GetPosition();
        Vector3 rightPos = right->GetPosition();
        Vector2 leftSize = left->GetSize();
        Vector2 rightSize = right->GetSize();

        //원형 충돌 정보 만들기      
        float leftradius = 0;
        float rightradius = 0;
        {
            if (leftSize.x > leftSize.y)
                leftradius = leftSize.x / 2;
            else
                leftradius = leftSize.y / 2;

            if (rightSize.x > rightSize.y)
                rightradius = rightSize.x / 2;
            else
                rightradius = rightSize.y / 2;
        }


        // OBB 정보 만들기 중
        Vector3 Distance = leftPos - rightPos;
        Vector3 Left_Width = left->GetOwner()->GetComponent<Transform>()->Right();
        Vector3 Left_height = left->GetOwner()->GetComponent<Transform>()->Up();
        Vector3 RIGHT_Width = right->GetOwner()->GetComponent<Transform>()->Right();
        Vector3 RIGHT_height = right->GetOwner()->GetComponent<Transform>()->Up();

        Vector3 Left_Scale = left->GetOwner()->GetComponent<Transform>()->GetScale();
        Vector3 Right_Scale = right->GetOwner()->GetComponent<Transform>()->GetScale();

        Vector3 Normal_L_W = Left_Width / Left_Scale.x;
        Vector3 Normal_L_H = Left_Width / Left_Scale.y;
        Vector3 Normal_R_W = RIGHT_Width / Right_Scale.x;
        Vector3 Normal_R_H = RIGHT_Width / Right_Scale.y;

        std::vector<Vector3> Normal = {};
        Normal.push_back(Left_Width);
        Normal.push_back(Left_height);
        Normal.push_back(Normal_R_W);
        Normal.push_back(Normal_R_H);


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
       #pragma region 1안
        //for (int i = 0; i < 3; ++i)
        //{
        //   Vector3 axis = obb1.axes[i];

        //   // 첫 번째 OBB의 프로젝션 구간 계산
        //   float min1 = INFINITY, max1 = -INFINITY;
        //   for (int j = 0; j < 8; ++j)
        //   {
        //      Vector3 vertex = obb1.center + obb1.extents.x * (j & 1 ? -axis : axis)
        //         + obb1.extents.y * ((j >> 1) & 1 ? -obb1.axes[(i + 1) % 3] : obb1.axes[(i + 1) % 3])
        //         + obb1.extents.z * ((j >> 2) & 1 ? -obb1.axes[(i + 2) % 3] : obb1.axes[(i + 2) % 3]);
        //      float projection = vertex.x * axis.x + vertex.y * axis.y + vertex.z * axis.z;
        //      min1 = fmin(min1, projection);
        //      max1 = fmax(max1, projection);
        //   }

        //   // 두 번째 OBB의 프로젝션 구간 계산
        //   float min2 = INFINITY, max2 = -INFINITY;
        //   for (int j = 0; j < 8; ++j)
        //   {
        //      Vector3 vertex = obb2.center + obb2.extents.x * (j & 1 ? -axis : axis)
        //         + obb2.extents.y * ((j >> 1) & 1 ? -obb2.axes[(i + 1) % 3] : obb2.axes[(i + 1) % 3])
        //         + obb2.extents.z * ((j >> 2) & 1 ? -obb2.axes[(i + 2) % 3] : obb2.axes[(i + 2) % 3]);
        //      float projection = vertex.x * axis.x + vertex.y * axis.y + vertex.z * axis.z;
        //      min2 = fmin(min2, projection);
        //      max2 = fmax(max2, projection);
        //   }

        //   // 프로젝션 구간이 겹치지 않으면 충돌하지 않음
        //   if (max1 < min2 || max2 < min1)
        //   {
        //      return false;
        //   }
        //}
        #pragma endregion 
        
        #pragma region 2안
        //★★★★★★★★구현중(미흡함)★★★★★★★
        //for (int i = 0; i < 4; i++)
        //{
        //   float _Distance = abs((Normal[i].Dot(Distance)));

        //   if (_Distance < abs(Normal[i].Dot(Left_Width))
        //      + abs(Normal[i].Dot(Left_height))
        //      + abs(Normal[i].Dot(RIGHT_Width))
        //      + abs(Normal[i].Dot(RIGHT_height)))
        //   {   
        //      int a = 0;
        //      return false;
        //   }
        //}
        #pragma endregion 

        return false;
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