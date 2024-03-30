#pragma once

#include <vector>
#include <string>

namespace IP_Utils {
    std::vector<std::string> split(const std::string &str, char d);
    std::uint8_t stringToUint8(const std::string& str);

    template<size_t N>
    void print_ip(const std::vector<std::array<std::uint8_t, N> > & ip_pool)
    {
        for (const auto & ip_address : ip_pool)
        {
            for (auto ip_part = ip_address.cbegin(); ip_part != ip_address.cend(); ++ip_part)
            {
                if (ip_part != ip_address.cbegin())
                {
                    std::cout << ".";
                }
                std::cout << (int)*ip_part;
            }
            std::cout << std::endl;
        }
    }
}