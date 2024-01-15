#pragma once
#include "jkEntity.h"
#include "jkComponent.h"
#include "jkScript.h"


namespace jk
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};


		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}
			return nullptr;
		}

		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};

			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					components.push_back(comp);
			}

			for (Script* script : mScripts)
			{
				comp = dynamic_cast<T*>(script);
				if (comp != nullptr)
					components.push_back(comp);
			}
			return components;
		}


		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}


		template <typename T>
		T* AddComponent(const Vector3& abc)
		{
			T* comp = new T(abc);

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);
			comp->Initialize();


			return comp;
		}



		template <typename T>
		T* AddComponent(const Vector3& abc, float set)
		{
			T* comp = new T(abc, set);

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);		
			comp->Initialize();


			return comp;
		}


		template <typename T>
		T* RemoveComponent(UINT COLID)
		{
			for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
			{
				T* component = dynamic_cast<T*>(*it);
				if (component != nullptr)
				{
					if(component->GetColliderID() == COLID)
					{	
						delete component;
						mComponents.erase(it);
						return component; // 삭제된 컴포넌트 반환 (선택사항)
					}
				}
			}
			return nullptr;
		}


		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;



	public:
		Transform* GetTransform() const
		{
			if (mComponents[(UINT)eComponentType::Transform])
				return static_cast<Transform*>(mComponents[(UINT)eComponentType::Transform]);

			return nullptr;
		}

		Vector3 GetPosition() const { return GetTransform()->GetPosition(); }
		float GetPositionX() const { return GetTransform()->GetPositionX(); }
		float GetPositionY() const { return GetTransform()->GetPositionY(); }
		float GetPositionZ() const { return GetTransform()->GetPositionZ(); }
		Vector2 GetPositionXY() const { return GetTransform()->GetPositionXY(); }

		Vector3 GetRotation() const { return GetTransform()->GetRotation(); }
		float GetRotationX() const { return GetTransform()->GetRotationX(); }
		float GetRotationY() const { return GetTransform()->GetRotationY(); }
		float GetRotationZ() const { return GetTransform()->GetRotationZ(); }
		Vector2 GetRotationXY() const { return GetTransform()->GetRotationXY(); }

		Vector3 GetScale() const { return GetTransform()->GetScale(); }
		float GetScaleX() const { return GetTransform()->GetScaleX(); }
		float GetScaleY() const { return GetTransform()->GetScaleY(); }
		float GetScaleZ() const { return GetTransform()->GetScaleZ(); }
		Vector2 GetScaleXY() const { return GetTransform()->GetScaleXY(); }

		void SetPosition(const Vector3& position) { GetTransform()->SetPosition(position); }
		void SetPositionX(const float posX) { GetTransform()->SetPositionX(posX); }
		void SetPositionY(const float posY) { GetTransform()->SetPositionY(posY); }
		void SetPositionZ(const float posZ) { GetTransform()->SetPositionZ(posZ); }
		void SetPositionXY(const Vector2& position) { GetTransform()->SetPositionXY(position); }

		void SetRotation(const Vector3& rotation) { GetTransform()->SetRotation(rotation); }
		void SetRotationX(const float rotX) { GetTransform()->SetRotationX(rotX); }
		void SetRotationY(const float rotY) { GetTransform()->SetRotationY(rotY); }
		void SetRotationZ(const float rotZ) { GetTransform()->SetRotationZ(rotZ); }
		void SetRotationXY(const Vector2& rotation) { GetTransform()->SetRotationXY(rotation); }

		void SetScale(const Vector3& scale) { GetTransform()->SetScale(scale); }
		void SetScaleX(const float scaleX) { GetTransform()->SetScaleX(scaleX); }
		void SetScaleY(const float scaleY) { GetTransform()->SetScaleY(scaleY); }
		void SetScaleZ(const float scaleZ) { GetTransform()->SetScaleZ(scaleZ); }
		void SetScaleXY(const Vector2& scale) { GetTransform()->SetScaleXY(scale); }

		void AddPosition(const Vector3& position) { GetTransform()->AddPosition(position); }
		void AddPositionX(const float posX) { GetTransform()->AddPositionX(posX); }
		void AddPositionY(const float posY) { GetTransform()->AddPositionY(posY); }
		void AddPositionZ(const float posZ) { GetTransform()->AddPositionZ(posZ); }
		void AddPositionXY(const Vector2& position) { GetTransform()->AddPositionXY(position); }

		void AddRotation(const Vector3& rotation) { GetTransform()->AddRotation(rotation); }
		void AddRotationX(const float rotX) { GetTransform()->AddRotationX(rotX); }
		void AddRotationY(const float rotY) { GetTransform()->AddRotationY(rotY); }
		void AddRotationZ(const float rotZ) { GetTransform()->AddRotationZ(rotZ); }

		void AddScale(const Vector3& scale) { GetTransform()->AddScale(scale); }
		void AddScaleX(const float scaleX) { GetTransform()->AddScaleX(scaleX); }
		void AddScaleY(const float scaleY) { GetTransform()->AddScaleY(scaleY); }
		void AddScaleZ(const float scaleZ) { GetTransform()->AddScaleZ(scaleZ); }



		Vector3 Forward() const { return GetTransform()->Foward(); }
		Vector3 Right() const { return GetTransform()->Right(); }
		Vector3 Up() const { return GetTransform()->Up(); }



		const math::Matrix& GetWorldMatrix() const { return GetTransform()->GetWorldMatrix(); }


		//Vector3 WorldForward() const { return GetTransform()->WorldForward(); }
		//Vector3 WorldRight() const { return GetTransform()->WorldRight(); }
		//Vector3 WorldUp() const { return GetTransform()->WorldUp(); }


		//Vector3 GetWorldPosition() const { return GetTransform()->GetWorldPosition(); }
		//Vector3 GetWorldRotation() const { return GetTransform()->GetWorldRotation(); }
		//Vector3 GetWorldScale() const { return GetTransform()->GetWorldScale(); }

		//float GetWorldPositionX() const { return GetTransform()->GetWorldPositionX(); }
		//float GetWorldPositionY() const { return GetTransform()->GetWorldPositionY(); }
		//float GetWorldPositionZ() const { return GetTransform()->GetWorldPositionZ(); }
		//Vector2 GetWorldPositionXY() const { return GetTransform()->GetWorldPositionXY(); }
		//float GetWorldRotationX() const { return GetTransform()->GetWorldRotationX(); }
		//float GetWorldRotationY() const { return GetTransform()->GetWorldRotationY(); }
		//float GetWorldRotationZ() const { return GetTransform()->GetWorldRotationZ(); }
		//float GetWorldScaleX() const { return GetTransform()->GetWorldScaleX(); }
		//float GetWorldScaleY() const { return GetTransform()->GetWorldScaleY(); }
		//float GetWorldScaleZ() const { return GetTransform()->GetWorldScaleZ(); }

		//Vector2 GetWorldCenterUp() const { return GetTransform()->GetWorldCenterUp(); }
		//Vector2 GetWorldCenterBottom() const { return GetTransform()->GetWorldCenterBottom(); }
		//Vector2 GetWorldLeftUp() const { return GetTransform()->GetWorldLeftUp(); }
		//Vector2 GetWorldLeftCenter() const { return GetTransform()->GetWorldLeftCenter(); }
		//Vector2 GetWorldLeftBottom() const { return GetTransform()->GetWorldLeftBottom(); }
		//Vector2 GetWorldRightUp() const { return GetTransform()->GetWorldRightUp(); }
		//Vector2 GetWorldRightCenter() const { return GetTransform()->GetWorldRightCenter(); }
		//Vector2 GetWorldRightBottom() const { return GetTransform()->GetWorldRightBottom(); }
	};



}
