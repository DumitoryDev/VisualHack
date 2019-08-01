#include"engine.h"
#include"reg_helper.h"
#include "time_info.h"
#include "crypt_visual_date.h"

namespace mtl
{
	mtl::map_func engine::funcs = {
		{"--update", engine::update_date},
		{"--date", engine::show_now_date},
		{"--version", engine::show_version}
	};

	std::string mtl::engine::version_ = "1.0.0.0";

	void mtl::engine::update_date(void)
	{

		const reg_helper helper(static_cast<version>(mtl::engine::show_menu()));
		const auto data_crypt = helper.get_data();

		mtl::crypt_visual_date crypt(data_crypt);
		crypt.decrypt_data();
		auto data_date = crypt.get_date();

		std::cout << "Old date - " << data_date[0].i << " " << data_date[1].i << " " << data_date[2].i << std::endl;
		auto date_data = mtl::time::get_date();

		data_date[0].i = static_cast<int>(date_data[0]); // year
		data_date[1].i = static_cast<int>(date_data[1]); // month
		data_date[2].i = static_cast<int>(date_data[2]); // day

		++data_date[1].i; // increment of the month

		std::cout << "New date - " << data_date[0].i << " " << data_date[1].i << " " << data_date[2].i << std::endl;

		crypt.change_date(data_date);
		crypt.crypt_data();

		helper.set_data(crypt.get_data());

		std::cout << "The operation was successful!" << std::endl;

	}

	void mtl::engine::show_version(void)
	{

		std::cout <<"Software version - " << engine::version_ << std::endl;

	}

	void engine::show_now_date(void)
	{
		const reg_helper helper(static_cast<version>(mtl::engine::show_menu()));

		mtl::crypt_visual_date crypt(helper.get_data());

		crypt.decrypt_data();
		auto date = crypt.get_date();

		std::cout << "License to " << date[0].i << " " << date[1].i << " " << date[2].i << std::endl;


	}

	size_t engine::show_menu(void)
	{

		std::cout << "Choose version Visual Studio:\n1 - Visual Studio 2017 Community\n2 - Visual Studio 2017 Professional\n3 - Visual Studio 2017 Enterprise\n4 - Visual Studio 2019 Community\n5 - Visual Studio 2019 Professional\n6 - Visual Studio 2019 Enterprise\n";
		size_t choice{};
		std::cin >> choice;
		if (choice > 6 || choice < 1)
		{
			throw std::runtime_error("Wrong input!(Choose version Visual Studio)");
		}

		return choice;

	}
}
