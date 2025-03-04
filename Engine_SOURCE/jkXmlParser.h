#pragma once

#include "..\\External\\CMarkUp\\Include\\Markup.h"
//#include "..\\External\\CMarkUp\\Include\\Markup.cpp"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\CMarkUp\\lib\\CMarkUp_debug.lib")
#else
#pragma comment(lib, "..\\External\\CMarkUp\\lib\\CMarkUp.lib")
#endif

#include "jkEngine.h"

namespace jk
{
	class XmlParser
	{
	public:
		XmlParser();
		~XmlParser();

		bool LoadFile(const std::string& name) { return LoadFile(StringToWideString(name));	}
		bool LoadFile(const std::wstring& name);
		bool FindElem(const std::string& elementName) { return FindElem(StringToWideString(elementName)); }
		bool FindElem(const std::wstring& elementName);

		bool IntoElem() { return mXml->IntoElem(); }
		bool OutOfElem() { return mXml->OutOfElem(); }
		void ResetPos() { mXml->ResetPos(); }

		bool HasAttribute(const std::string& attributeName) { return HasAttribute(StringToWideString(attributeName)); }
		bool HasAttribute(const std::wstring& attributeName);

		std::wstring GetWstringAttribute(const std::wstring& attributeWSTRName) { return mXml->GetAttrib(attributeWSTRName.c_str()); }
		float GetFloatAttribute(const std::string& attibuteFloatName) { return GetFloatAttribute(StringToWideString(attibuteFloatName)); }
		int GetIntAttribute(const std::string& attibuteIntName) { return GetIntAttribute(StringToWideString(attibuteIntName)); }
		float GetFloatAttribute(const std::wstring& attibuteFloatName);
		int GetIntAttribute(const std::wstring& attibuteIntName);

	private:
		//CMarkup* mXml = new CMarkup;
		CMarkup* mXml;
		//std::shared_ptr<CMarkup> mXml;
	};
}
