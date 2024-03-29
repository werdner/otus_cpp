#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ip.h"
#include "utils.h"

int main()
{
    try
    {
        std::vector<IP::IpParams > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = IP_Utils::split(line, '\t');
            std::vector<std::string> ip_address = IP_Utils::split(v.at(0), '.');
            
            int ip_address_size = ip_address.size();
            std::uint8_t * params = new std::uint8_t[ip_address_size];

            for (int i = 0; i < ip_address_size; ++i)
                params[i] = IP_Utils::stringToUint8(ip_address[i]); // converse std::string to std::uint8_t
            ip_pool.emplace_back(params);
            delete [] params;
        }

        std::cout << std::endl;
        std::cout << "FILTER_1\n\n";

        int counter_params = 0;

        std::uint8_t * filter_1 = IP_Utils::process_params(counter_params, 1); // parse the passed arguments (1)
        std::vector<IP::IpParams> filtred_1 = IP::filter(ip_pool, IP::IpParams(filter_1));
        IP_Utils::print_list(filtred_1);
        delete [] filter_1;

        std::cout << std::endl;
        std::cout << "FILTER_46_70\n\n";

        std::uint8_t * filter_46_70 = IP_Utils::process_params(counter_params, 46, 70); // parse the passed arguments (46, 70)
        std::vector<IP::IpParams> filtred_46_70 = IP::filter(ip_pool, IP::IpParams(filter_46_70));
        IP_Utils::print_list(filtred_46_70);
        delete [] filter_46_70;

        std::cout << std::endl;
        std::cout << "FILTER_ANY_46\n\n";

        std::uint8_t * filter_any_46 = IP_Utils::process_params(counter_params, 46); // parse the passed arguments (46)
        std::vector<IP::IpParams> filtred_any_46 = IP::filter_any(ip_pool, IP::IpParams(filter_any_46));
        IP_Utils::print_list(filtred_any_46, true);
        delete [] filter_any_46;

        std::cout << std::endl;
        std::cout << "SORT\n\n";
        
        std::sort(begin(ip_pool), end(ip_pool), IP_Utils::compare);
        IP_Utils::print_list(ip_pool);
    }
    catch(const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
