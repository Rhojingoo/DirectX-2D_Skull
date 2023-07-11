#pragma once
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <type_traits>

#define arraysize(a) (sizeof(a)/sizeof(a[0]))


// Enable enum flags:
// https://www.justsoftwaresolutions.co.uk/cplusplus/using-enum-classes-as-bitfields.html

template<typename E>
struct enable_bitmask_operators
{
	static constexpr bool enable = false;
};

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator|(E lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	return static_cast<E>
		(
			static_cast<underlying>(lhs) | static_cast<underlying>(rhs)
			);
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator|=(E& lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	lhs = static_cast<E>
		(
			static_cast<underlying>(lhs) | static_cast<underlying>(rhs)
			);

	return lhs;
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator&(E lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	return static_cast<E>
		(
			static_cast<underlying>(lhs) & static_cast<underlying>(rhs)
			);
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator&=(E& lhs, E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	lhs = static_cast<E>
		(
			static_cast<underlying>(lhs) & static_cast<underlying>(rhs)
			);

	return lhs;
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator~(E rhs)
{
	typedef typename std::underlying_type<E>::type underlying;
	rhs = static_cast<E>
		(
			~static_cast<underlying>(rhs)
			);

	return rhs;
}

template<typename E>
constexpr bool has_flag(E lhs, E rhs)
{
	return (lhs & rhs) == rhs;
}



static std::wstring StringToWideString(const std::string& str)
{
	int numChars = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (numChars == 0)
	{
		return L"";
	}

	std::wstring wideStr(numChars, 0);

	if (!MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], numChars))
	{
		return L"";
	}

	return wideStr;
}

static std::string WideStringToString(const std::wstring& str)
{
	int numChars = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	if (numChars == 0)
	{
		return "";
	}

	std::string narrowStr(numChars, 0);

	if (!WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, &narrowStr[0], numChars, NULL, NULL))
	{
		return "";
	}

	return narrowStr;
}