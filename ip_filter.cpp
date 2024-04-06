#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d); // auto ?
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

template <typename Container> bool lexicographical_compare(const Container &a, const Container &b)
{
	if (a.size() != b.size()) {
		throw std::runtime_error("a.size() != b.size()");
	}
	for (typename Container::size_type i = 0; i < a.size(); ++i) {
		if (a[i] == b[i]) {
			continue;
		} else {
			try {
				return std::stoi(a[i]) > stoi(b[i]);
			} catch (const std::exception &e) {
				return a[i] > b[i];
			}
		}
	}
	return false;
}

template <typename ContainerIterator>
void sort_by_lexicographical_comapre(ContainerIterator begin, ContainerIterator end)
{
	std::sort(begin, end, lexicographical_compare<typename ContainerIterator::value_type>);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
	try {
		auto print_vector = [](const std::vector<std::vector<std::string>> &ip_pool) {
			for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
				for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
					if (ip_part != ip->cbegin()) {
						std::cout << ".";
					}
					std::cout << *ip_part;
				}
				std::cout << std::endl;
			}
		};

		std::vector<std::vector<std::string>> ip_pool;

		for (std::string line; std::getline(std::cin, line);) {
			auto v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		sort_by_lexicographical_comapre(ip_pool.begin(), ip_pool.end());
		print_vector(ip_pool);

		std::vector<std::vector<std::string>> ip_pool_filtered;
		ip_pool_filtered.reserve(ip_pool.size());

		std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool_filtered),
					 [](std::vector<std::string> &ip) {
						 if (ip.size() < 1)
							 return false;
						 else
							 return ip[0] == "1";
					 });
		print_vector(ip_pool_filtered);

		ip_pool_filtered.clear();
		std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool_filtered),
					 [](std::vector<std::string> &ip) {
						 if (ip.size() < 2)
							 return false;
						 else
							 return ip[0] == "46" && ip[1] == "70";
					 });
		print_vector(ip_pool_filtered);

		ip_pool_filtered.clear();
		std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool_filtered),
					 [](std::vector<std::string> &ip) {
						 for (auto &i : ip)
							 if (i == "46")
								 return true;
						 return false;
					 });
		print_vector(ip_pool_filtered);

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
