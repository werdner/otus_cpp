#include <vector>
#include <limits>

#include "ip.h"
#include <string>
#include <iostream>

namespace IP_Utils {
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

    std::uint8_t stringToUint8(const std::string& str)
    {
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
}