#include "reg_helper.h"




std::map<version, std::wstring> reg_helper::paths_ = {

	{ version::VS2017Community,L"Licenses\\5C505A59-E312-4B89-9508-E162F8150517\\08878"},
	{ version::VS2017Professional,L"Licenses\\5C505A59-E312-4B89-9508-E162F8150517\\08862"},
	{ version::VS2017Enterprise,L"Licenses\\5C505A59-E312-4B89-9508-E162F8150517\\08860"},

	{ version::VS2019Community,L"Licenses\\41717607-F34E-432C-A138-A3CFD7E25CDA\\09278"},
	{ version::VS2019Professional,L"Licenses\\41717607-F34E-432C-A138-A3CFD7E25CDA\\09262"},
	{ version::VS2019Enterprise,L"Licenses\\41717607-F34E-432C-A138-A3CFD7E25CDA\\09260"},

};



reg_helper::reg_helper(const version ver):version_(ver)
{

	HKEY h;
	if (::RegOpenKeyEx(HKEY_CLASSES_ROOT,
		reg_helper::paths_.at(this->version_).c_str(),
		0, 
		KEY_WRITE | KEY_READ, 
		&h) != ERROR_SUCCESS)
	{
		throw error::c_win_api_exception(L"Error RegOpenKeyEx!", ::GetLastError());
	}

	this->h_key_ptr_ = std::unique_ptr<void, destructor>(h, this->func_destructor_);
}

std::vector<BYTE> reg_helper::get_data() const
{

	std::vector<BYTE> buff(4096);
	DWORD size = buff.size();

	if (::RegQueryValueEx(reinterpret_cast<HKEY>(this->h_key_ptr_.get()), 
		L"", 
		 nullptr, 
		nullptr,
		buff.data(), 
		&size) != ERROR_SUCCESS)
	{
		throw error::c_win_api_exception(L"Error RegQueryValueEx!", ::GetLastError());
	}
	
	buff.resize(size);
	return buff;
	
}

void reg_helper::set_data(const std::vector<BYTE> & buff) const
{
	
	if (::RegSetValueEx(reinterpret_cast<HKEY>(this->h_key_ptr_.get()), 
		L"",
		0, 
		REG_BINARY, 
		buff.data(),
		buff.size()) != ERROR_SUCCESS)
	{
		throw error::c_win_api_exception(L"Error RegOpenKeyEx!", ::GetLastError());
	}
	   	 
}
