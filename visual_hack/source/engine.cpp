#include"engine.h"
#include"reg_helper.h"
#include "crypt.h"
#include "time.h"
namespace mtl
{
	mtl::map_func engine::funcs = { 
		{"--update", engine::update_date},
		{"--version", engine::get_verison}
	};

	std::string mtl::engine::version_ = "1.0.0.0";
	
	void mtl::engine::update_date(void)
	{
		std::cout << "Choose version Visual Studio:\n1 - Visual Studio 2017 Community\n2 - Visual Studio 2017 Professional\n3 - Visual Studio 2017 Enterprise\n4 - Visual Studio 2019 Community\n5 - Visual Studio 2019 Professional\n6 - Visual Studio 2019 Enterprise\n";
		size_t choice{};
		std::cin >> choice;
		if (choice > 6 || choice < 1)
		{
			throw std::runtime_error("Wrong input!(Choose version Visual Studio)");
		}

		const reg_helper helper(static_cast<version>(choice));
		const auto data_crypt = helper.get_data();
	    auto data_no_crypt = crypt::decrypt_data(data_crypt);
		auto data_nums = crypt::get_nums(data_no_crypt);
		std::cout << "Old date - " << data_nums[0].i << " " << data_nums[1].i << " " << data_nums[2].i << std::endl;
		auto date_data = mtl::time::get_date();

		data_nums[0].i = static_cast<int>(date_data[0]);
		data_nums[1].i = static_cast<int>(date_data[1]);
		data_nums[2].i = static_cast<int>(date_data[2]);

		data_nums[1].i++; // increment of the month

		std::cout << "New date - " << data_nums[0].i << " " << data_nums[1].i << " " << data_nums[2].i << std::endl;

		crypt::change_num(data_no_crypt, data_nums);
		auto data_new_crypt = crypt::crypt_data(data_no_crypt);
		helper.set_data(data_new_crypt);

		std::cout << "The operation was successful!" << std::endl;

	}

	void mtl::engine::get_verison(void)
	{

		std::cout << engine::version_ << std::endl;

	}

}
