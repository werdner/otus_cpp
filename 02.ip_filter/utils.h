#pragma once

#include <string>
#include <cstdint>

#include "ip.h"

namespace IP_Utils {
    std::uint8_t stringToUint8(const std::string& str);
    std::vector<std::string> split(const std::string &str, char d);

    void print_list(const std::vector<IP::IpParams> & filtredVec, bool reverse = false);
    bool compare(const IP::IpParams & first, const IP::IpParams & last);


    std::uint8_t * process_params(int & counter) {
        std::uint8_t * params = new std::uint8_t[counter];
        return params;
    }

    template<typename T, typename ...Args>
    std::uint8_t * process_params(int & counter, T first, Args... args)
    {
        std::uint8_t * params = process_params(++counter, args...);
        params[--counter] = first;
        return params;
    }
}