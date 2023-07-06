#pragma once
#include "jkResource.h"
#include "jkImage.h"

namespace jk
{
	class Resources
	{
	public:
		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			//리소스맵에서 데이터를 탐색한다 데이터가 있다면 해당데이터를 반환하고
			//데이터가 없다면 end를 반환해준다.
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = mResources.find(key);

			//찾고자 하는 데이터가 존재한다면
			//해당타입으로 형변환하여 반환
			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			//데이터 없다면 널을 반환
			return nullptr;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			std::shared_ptr<T> resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// 해당 리소스가 없다면
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

//#pragma region Title_Resource
//		template <typename T>
//		static T* Find_Tile(const std::wstring& key)
//		{
//			//리소스맵에서 데이터를 탐색한다 데이터가 있다면 해당데이터를 반환하고
//			//데이터가 없다면 end를 반환해준다.
//			std::map<std::wstring, Resource*>::iterator iter = _Resources.find(key);
//
//			//찾고자 하는 데이터가 존재한다면
//			//해당타입으로 형변환하여 반환
//			if (iter != _Resources.end())
//			{
//				return dynamic_cast<T*>(iter->second);
//			}
//
//			//데이터 없다면 널을 반환
//			return nullptr;
//		}
//
//		template <typename T>
//		static T* Load_Tile(HDC hdc, const std::wstring& key, const std::wstring& path)
//		{
//			// 키값으로 탐색
//			T* resource = Resources::Find<T>(key);
//			if (resource != nullptr)
//			{
//				return resource;
//			}
//
//			// 해당 리소스가 없다면
//			resource = new T();
//			if (FAILED(resource->Load(path)))
//			{
//				assert(false);
//				return nullptr;
//			}
//
//			resource->SetKey(key);
//			resource->SetPath(path);
//			_Resources.insert(std::make_pair(key, resource));
//
//			return dynamic_cast<T*>(resource);
//		}
//#pragma endregion



	private:
		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;
		//static std::map<std::wstring, Resource*> _Resources;
	};
}

