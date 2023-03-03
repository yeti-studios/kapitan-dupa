//
// Created by volt on 2023-02-25.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_STRINGMAP_HPP
#define KPTDUPA_STRINGMAP_HPP


struct StrHash {
	using is_transparent = void;
	[[nodiscard]] inline size_t operator()(const char *txt) const
	{
		return std::hash<std::string_view>{}(txt);
	}
	[[nodiscard]] inline size_t operator()(std::string_view txt) const
	{
		return std::hash<std::string_view>{}(txt);
	}
	[[nodiscard]] inline size_t operator()(const std::string &txt) const
	{
		return std::hash<std::string>{}(txt);
	}
};

template<typename T>
using StringMap = std::unordered_map<std::string, T, StrHash, std::equal_to<>>;



#endif //KPTDUPA_STRINGMAP_HPP
