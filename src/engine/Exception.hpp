//
// Created by volt on 2023-02-25.
//

#ifndef KPTDUPA_EXCEPTION_HPP
#define KPTDUPA_EXCEPTION_HPP

#include <stdexcept>
#include <format>

struct Exception: public std::runtime_error {
	using std::runtime_error::runtime_error;

	template<typename... Args>
	explicit Exception(const std::string_view fmt, Args... args)
		: Exception(std::vformat(fmt, std::make_format_args(args...)))
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
