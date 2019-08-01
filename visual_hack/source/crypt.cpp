#include "crypt.h"

std::vector<BYTE> crypt::decrypt_data(std::vector<BYTE> buff)
{

	DATA_BLOB data_out;
	DATA_BLOB data_verify;
	
	data_out.pbData = buff.data();
	data_out.cbData = static_cast<DWORD>(buff.size());

	if (!::CryptUnprotectData(
		&data_out,
		nullptr,
		nullptr,                 // Optional entropy
		nullptr,                 // Reserved
		nullptr,      
		0,
		&data_verify))
	{
		throw error::c_win_api_exception(L"Error CryptUnprotectData!", ::GetLastError());
	}

	
	const auto first = data_verify.pbData;
	const auto last = data_verify.pbData + data_verify.cbData;
	std::vector<BYTE> buff_result{ first,last };
		
	::LocalFree(data_verify.pbData);
		
	return buff_result;
}

std::vector<crypt::num> crypt::get_nums(const std::vector<BYTE>  & data)
{
	
	std::vector<crypt::num> buff(3);
	
	int i = 16; // bias

	for (auto &  element : buff)
		element = { *(data.cend() - i--), *(data.cend() - i--) };
		

	return buff;

}

void crypt::change_num(std::vector<BYTE>& buff, const std::vector<crypt::num>& nums)
{
	const auto offset = 16;
	
	for (auto i = 0, j = offset; i < 3; ++i)
	{
		*(buff.end() - j--) = nums[i].byte[0];
		*(buff.end() - j--) = nums[i].byte[1];
	}
		
}

std::vector<BYTE> crypt::crypt_data(std::vector<BYTE> buff)
{

	DATA_BLOB data_in;
	DATA_BLOB data_out;
	
	data_in.pbData = buff.data();
	data_in.cbData = static_cast<DWORD>(buff.size());
	
	
	if (!::CryptProtectData(
		&data_in,
		nullptr, // A description string. 
		nullptr,                               // Optional entropy
		nullptr,                               // Reserved.
		nullptr,                      // Pass a PromptStruct.
		0,
		&data_out))
	{
		throw error::c_win_api_exception(L"Error CryptProtectData!", ::GetLastError());
	}

	const auto first = data_out.pbData;
	const auto last = data_out.pbData + data_out.cbData;

	std::vector<BYTE> buff_res{ first, last };
	::LocalFree(data_out.pbData);

	return buff_res;
	
}


