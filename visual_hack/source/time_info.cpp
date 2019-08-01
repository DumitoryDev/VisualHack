#include  "time_info.h"

namespace mtl
{
	std::vector<size_t> time::get_date()
	{
		std::vector<size_t> data_time(3);
		auto t = std::time(nullptr);
		std::tm timestamp{};
		localtime_s(&timestamp, &t);
		auto format = "%Y "; //const char* format = " -  [%T - %d:%m - %Y]";
		std::stringstream ss{};
		ss << std::put_time(&timestamp, format);
		format = "%m ";
		ss << std::put_time(&timestamp, format);
		format = "%d ";
		ss << std::put_time(&timestamp, format);


		for (auto& i : data_time)
		{
			int data{};
			ss >> data;
			i = data;
		}

		return data_time;
	}
}
