#pragma once
#include "../pch.h"
#include "../source/exception.h"
class crypt
{
public:

	union num
	{
		BYTE byte[2];
		int i;
	};

	crypt(const crypt& other) = delete;
	crypt(crypt&& other) noexcept = delete;
	crypt& operator=(const crypt& other) = delete;
	crypt& operator=(crypt&& other) noexcept = delete;

	crypt(void) = delete;
	~crypt(void) = delete;

	static std::vector<BYTE> decrypt_data(std::vector<BYTE> buff);
	static std::vector<num> get_nums(const std::vector<BYTE>& data);
	static void change_num(std::vector<BYTE>& buff, const std::vector<crypt::num>& nums);
	static std::vector<BYTE> crypt_data(std::vector<BYTE> buff);
	
private:

};

