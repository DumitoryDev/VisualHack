#pragma once
#include "../pch.h"
namespace mtl
{
	using map_func = std::map<std::string, std::function<void(void)>>;
	class engine
	{
	public:
		
		engine(const engine& other) = delete;
		engine(engine&& other) noexcept = delete;
		engine& operator=(const engine& other) = delete;
		engine& operator=(engine&& other) noexcept = delete;

		engine(void) = delete;
		~engine(void) = delete;

		static void show_version(void);
		static void show_now_date(void);
		static size_t show_menu(void);
		static map_func funcs;
	private:
		static void update_date(void);
		static std::string version_;
		
	};

	
}
