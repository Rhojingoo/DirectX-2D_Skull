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
        // �� �浹ü�� ID bool���� Ȯ��
        ColliderID id = {};
        id.left = left->GetColliderID();
        id.right = right->GetColliderID();

        // �浹������ �����´�
        std::map<UINT64, bool>::iterator iter
            = mCollisionMap.find(id.id);

        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(id.id, false));
            iter = mCollisionMap.find(id.id);
        }

        if (Intersect(left, right))
        {
            // �浹
            if (iter->second == false)
            {
                //���� �浹
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);
            }
            else
            {
                // �浹 ��
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else
        {
            // �浹 X
            if (iter->second == true)
            {
                // �浹�ϰ� �ִٰ� ������
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);
            }
        }
    }

    bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
    {

        //�簢�� �浹 ���� �����   
        Vector3 leftPos = left->GetPosition();
        Vector3 rightPos = right->GetPosition();
        Vector2 leftSize = left->GetSize();
        Vector2 rightSize = right->GetSize();

        //���� �浹 ���� �����      
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


        // OBB ���� ����� ��
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


        //�簢���浹
        //if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
        //   && fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
        //{
        //   int a = 0;
        //   return true;
        //}

        // �����浹
        //float radiusSum = leftradius + rightradius;      
        //float distance = Vector3::Distance(leftPos, rightPos);
        //if (distance < leftradius + rightradius)
        //{
        //   int a = 0;
        //   return true;
        //}


        // OBB �浹
       #pragma region 1��
        //for (int i = 0; i < 3; ++i)
        //{
        //   Vector3 axis = obb1.axes[i];

        //   // ù ��° OBB�� �������� ���� ���
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

        //   // �� ��° OBB�� �������� ���� ���
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

        //   // �������� ������ ��ġ�� ������ �浹���� ����
        //   if (max1 < min2 || max2 < min1)
        //   {
        //      return false;
        //   }
        //}
        #pragma endregion 
        
        #pragma region 2��
        //�ڡڡڡڡڡڡڡڱ�����(������)�ڡڡڡڡڡڡ�
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