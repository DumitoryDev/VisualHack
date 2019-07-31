#pragma once
#include "../pch.h"
#include "exception.h"

/*
 * Visual Studio Enterprise | 60
 * Visual Studio Professional | 62
 * Visual Studio Community | 78
 *
 */

enum class version
{
	VS2017Community = 1,
	VS2017Professional,
	VS2017Enterprise,
	VS2019Community,
	VS2019Professional,
	VS2019Enterprise,
	

};

class reg_helper
{
public:
		

	using destructor = std::function<void(void*)>;
	using u_ptr = std::unique_ptr<void, destructor>;

	reg_helper(const reg_helper& other) = delete;
	reg_helper(reg_helper&& other) noexcept = delete;
	reg_helper& operator=(const reg_helper& other) = delete;
	reg_helper& operator=(reg_helper&& other) noexcept = delete;

	reg_helper(version);
	~reg_helper(void) = default;

	std::vector<BYTE> get_data() const;
	void set_data(const std::vector<BYTE> & buff) const;
private:
	static std::map<version, std::wstring> paths_;
	destructor func_destructor_ = [](void* ptr)
	{
		::RegCloseKey(reinterpret_cast<HKEY>(ptr));
	};

	u_ptr h_key_ptr_{};
	version version_{};


};