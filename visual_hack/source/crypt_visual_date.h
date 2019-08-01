#pragma once

#include "../pch.h"
#include "crypt.h"
namespace mtl
{
	class crypt_visual_date: public crypt
	{
		
	public:
		union num
		{
			BYTE byte[2];
			int i;
		};

		using crypt::crypt;

		[[nodiscard]] std::vector<crypt_visual_date::num> get_date(void) const;
		void change_date(const std::vector<crypt_visual_date::num>& date);
	};
}
