#pragma once
#include "../pch.h"

namespace mtl
{
	class time
	{
	public:
		time(const time& other) = delete;
		time(time&& other) noexcept = delete;
		time& operator=(const time& other) = delete;
		time& operator=(time&& other) noexcept = delete;

		time(void) = delete;
		~time(void) = delete;

		static std::vector<size_t> get_date(void);
	};
}
