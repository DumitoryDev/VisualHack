#include "crypt_visual_date.h"
namespace mtl
{
	std::vector<crypt_visual_date::num> crypt_visual_date::get_date(void) const
	{

		std::vector<crypt_visual_date::num> buff(3);

		size_t offset = 16;

		for (auto& element : buff)
			element = { *(this->data_.cend() - offset--), *(this->data_.cend() - offset--) };
		
		return buff;

	}

	void crypt_visual_date::change_date(const std::vector<crypt_visual_date::num>& date)
	{

		const auto offset = 16;
		
		for (auto i = 0, j = offset; i < 3; ++i)
		{
			*(this->data_.end() - j--) = date[i].byte[0];
			*(this->data_.end() - j--) = date[i].byte[1];
		}

	}
}
