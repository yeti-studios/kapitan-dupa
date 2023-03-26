//
// Created by volt on 2023-02-25.
//
#include <kptdup_pch.hpp>

#ifndef KPTDUPA_EXCEPTION_HPP
#define KPTDUPA_EXCEPTION_HPP


struct Exception: public std::runtime_error {
	using std::runtime_error::runtime_error;

	template<typename... Args>
	explicit Exception(const char* fmt, Args... args)
		: Exception(al::Format(fmt, args...))
	{

	}
};

#define KPTDUP_DEF_EXCEPTION(ex_name, parent_name) \
	struct ex_name: public parent_name {              \
        using parent_name::parent_name;            \
	};

KPTDUP_DEF_EXCEPTION(EngineException, Exception)
KPTDUP_DEF_EXCEPTION(NotImplementedException, Exception)

#endif //KPTDUPA_EXCEPTION_HPP
