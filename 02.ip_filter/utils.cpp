#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <limits>
#include "ip.h"

namespace IP_Utils {
    std::uint8_t stringToUint8(const std::string& str) {
        try {
            int value = std::stoi(str);
            
            if (value < 0 || value > std::numeric_limits<std::uint8_t>::max()) {
                throw std::out_of_range("Value out of range for std::uint8_t");
            }

            return static_cast<std::uint8_t>(value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
            throw;
        }
    }

    void print_list(const std::vector<IP::IpParams> & filtred_vec, bool reverse = false)
    {
        std::vector<IP::IpParams>::const_iterator start = filtred_vec.cbegin();
        std::vector<IP::IpParams>::const_iterator end = filtred_vec.cend();
        
        while (start != end)
        {
            std::vector<IP::IpParams>::const_iterator iterator = reverse ? end : start;
            std::uint8_t * params = iterator->getParams();
            int size = iterator->getSize();

            for (int i = 0; i < size; ++i)
            {
                std::uint8_t trail = (i + 1 == size) ? '\n' : '.';
                std::cout << (int)params[i] << trail;
            }

            reverse ? --end : ++start;
        }
    }

    bool compare(const IP::IpParams & first, const IP::IpParams & last)
    {
        std::uint8_t * f_params = first.getParams();
        std::uint8_t * l_params = last.getParams();

        int f_size = first.getSize();
        int l_size = last.getSize();

        if (f_size != l_size)
            return f_size > l_size;

        for (int i = 0; i < f_size; ++i)
        {
            if (f_params[i] == l_params[i])
                continue;
            return f_params[i] > l_params[i];
        }

        return false;
    }

    std::vector<std::string> split(const std::string &str, char d)
    {
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while(stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }
}