#include "jkFont.h"
#include "jkFontWrapper.h"

namespace jk
{
	wchar_t jkFont::text_[50] = L"Default Text";
	float jkFont::Horizontal_Position = 0.f;
	float jkFont::Vertical_Position = 0.f;
	float jkFont::Font_size = 0.f;	
	bool jkFont::_Texton = false;

	wchar_t jkFont::text_2[50] = L"Default Text";
	float jkFont::Horizontal_Position2 = 0.f;
	float jkFont::Vertical_Position2 = 0.f;
	float jkFont::Font_size2 = 0.f;
	bool jkFont::_Texton2 = false;
	

	jkFont::jkFont()
	{
		wcscpy_s(text_, L"Default Text");
	}
	jkFont::~jkFont()
	{
	}

	void jkFont::Initialize()
	{
	}

	void jkFont::Update()
	{
	}

	void jkFont::Render()
	{
		if (_Texton == true)
		{
			//FontWrapper* av = new FontWrapper;
			/*av->*/FontWrapper::DrawFont(text_, Horizontal_Position, -Vertical_Position, Font_size, FONT_RGBA(255, 255, 255, 255));
		}
		if (_Texton2 == true)
		{
			//FontWrapper* av2 = new FontWrapper;
			/*av2->*/FontWrapper::DrawFont(text_2, Horizontal_Position2, -Vertical_Position2, Font_size2, FONT_RGBA(255, 255, 255, 255));
		}
	}


}
