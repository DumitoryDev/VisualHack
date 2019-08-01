#include "crypt.h"

void crypt::decrypt_data(void)
{

	DATA_BLOB data_out;
	DATA_BLOB data_verify;
	
	data_out.pbData = this->data_.data();
	data_out.cbData = static_cast<DWORD>(this->data_.size());

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
	this->data_ = { first,last };
	
	::LocalFree(data_verify.pbData);
			
}

void crypt::crypt_data(void)
{

	DATA_BLOB data_in;
	DATA_BLOB data_out;
	
	data_in.pbData = this->data_.data();
	data_in.cbData = static_cast<DWORD>(this->data_.size());
	
	
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

	this->data_ = { first, last };
	::LocalFree(data_out.pbData);
		
	
}


