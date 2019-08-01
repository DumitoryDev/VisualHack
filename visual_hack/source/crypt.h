#pragma once
#include "../pch.h"
#include "../source/exception.h"
class crypt
{
public:
	~crypt(void) = default;
	crypt(const crypt& other) = delete;
	crypt(crypt&& other) noexcept = delete;
	crypt& operator=(const crypt& other) = delete;
	crypt& operator=(crypt&& other) noexcept = delete;

	explicit crypt(std::vector<BYTE> data) :data_(std::move(data)) {


	}

	explicit crypt(const std::string& data) :data_{ data.cbegin(),data.cend() }
	{

	}



	void decrypt_data(void);
	void crypt_data(void);
	const auto & get_data(void) const noexcept 
	{
		return this->data_;
	}

protected:
	std::vector<BYTE> data_{};

};

