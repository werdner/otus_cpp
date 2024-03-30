#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <cstdint>
#include <algorithm>

#include "utils.h"
#include "ip.h"

int main()
{
    try
    {
        std::vector<IP::ip_arr> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = IP_Utils::split(line, '\t');
            std::vector<std::string> ip_address = IP_Utils::split(v.at(0), '.');
            std::array<std::uint8_t, IP::IP_Filter::LIMIT> array;
            for (int i = 0; i < 4; ++i)
            {
                array[i] = IP_Utils::stringToUint8(ip_address[i]);
            }

            ip_pool.push_back(array);
        }


        std::cout << std::endl;
        std::cout << "FILTER_1\n\n";

        const IP::IP_Filter filter_params_1 = IP::IP_Filter(IP::ip_arr{1}, 1);
        const std::vector<IP::ip_arr> filter_1 = IP::filter(ip_pool, filter_params_1);

        IP_Utils::print_ip<IP::IP_Filter::LIMIT>(filter_1);

        std::cout << std::endl;
        std::cout << "FILTER_46_70\n\n";

        const IP::IP_Filter filter_params_46_70 = IP::IP_Filter(IP::ip_arr{46, 70}, 2);
        const std::vector<IP::ip_arr> filter_46_70 = IP::filter(ip_pool, filter_params_46_70);

        IP_Utils::print_ip<IP::IP_Filter::LIMIT>(filter_46_70);

        std::cout << std::endl;
        std::cout << "FILTER_ANY_46\n\n";

        const IP::IP_Filter filter_params_any_46 = IP::IP_Filter(IP::ip_arr{46}, 1);
        const std::vector<IP::ip_arr> filter_any_46 = IP::filter_any(ip_pool, filter_params_any_46);

        IP_Utils::print_ip<IP::IP_Filter::LIMIT>(filter_any_46);

        std::cout << std::endl;
        std::cout << "LEXICOGRAPHICAL ORDER\n\n";

        std::sort(begin(ip_pool), end(ip_pool), [](const IP::ip_arr & arr1, const IP::ip_arr & arr2){ return arr1 > arr2; });
        IP_Utils::print_ip<IP::IP_Filter::LIMIT>(ip_pool);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
