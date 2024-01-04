#pragma once

namespace jk
{
	class jkFont
	{
	public:
		jkFont();
		virtual ~jkFont();
				

		static void Initialize();
		static void Update();
		static void Render();

		// Getter (text_ ���� ���� �������� �Լ�)
		const wchar_t* getText() const
		{
			return text_;
		}

		// Setter (text_ ���� ���� �����ϴ� �Լ�)
		static void setText(const wchar_t* text, float Horizontal, float Vertical, float size, bool set)
		{
			wcscpy_s(text_, 50, text);  // 50: �ִ� ������ ���� ��, �� ���� buffer ũ��� ��ġ�ؾ� �մϴ�.

			Horizontal_Position = Horizontal;
			Vertical_Position = Vertical;
			Font_size = size;
			_Texton = set;
		}

		static void setText2(const wchar_t* text, float Horizontal, float Vertical, float size, bool set)
		{
			wcscpy_s(text_2, 50, text);  // 50: �ִ� ������ ���� ��, �� ���� buffer ũ��� ��ġ�ؾ� �մϴ�.

			Horizontal_Position2 = Horizontal;
			Vertical_Position2 = Vertical;
			Font_size2 = size;
			_Texton2 = set;
		}

		static void textoff() { _Texton = false, _Texton2= false; }


	private:
		static wchar_t text_[50];
		static float Horizontal_Position;
		static float Vertical_Position;
		static float Font_size;
		static bool _Texton;

		static wchar_t text_2[50];
		static float Horizontal_Position2;
		static float Vertical_Position2;
		static float Font_size2;
		static bool _Texton2;

	};
}