#include <array>
#include <memory>
#include <vector>
#include <iostream>

#include "ip.h"

IP::IP_Filter::IP_Filter(const ip_arr & array_ptr, const std::uint8_t input_s) : size(input_s)
{
    params = std::make_shared<ip_arr>(array_ptr);
}

IP::IP_Filter::~IP_Filter()
{
    size = 0;
}

IP::IP_Filter::IP_Filter(const IP_Filter & ip_filter) : params(ip_filter.params), size(ip_filter.size) {}

void IP::IP_Filter::operator=(const IP_Filter & ip_filter)
{
    params = ip_filter.params;
    size = ip_filter.size;
}

const std::vector<IP::ip_arr> IP::filter(const std::vector<IP::ip_arr> input_vac, const IP_Filter & filter_params)
{
    std::vector<IP::ip_arr> filtred_vec;
    const IP::ip_arr * params = filter_params.getRawParams();

    int vec_size = input_vac.size();
    for (int i = 0; i < vec_size; ++i)
    {
        IP::IP_Filter input_ip_params(input_vac[i], 4);
        int input_ip_params_size = input_ip_params.getSize();
        int ip_params_size = filter_params.getSize();
        bool validation_passed = true;

        for (int k = 0; k < ip_params_size && k < input_ip_params_size; ++k)
        {
            const IP::ip_arr * rawParams = input_ip_params.getRawParams();
            if ((int)(*params)[k] != (int)(*rawParams)[k])
            {
                validation_passed = false;
                break;
            }
        }
            
        if (validation_passed)
            filtred_vec.emplace_back(input_vac[i]);
    }

    return filtred_vec;
}

const std::vector<IP::ip_arr> IP::filter_any(const std::vector<IP::ip_arr> input_vac, const IP_Filter & filter_params)
{
    std::vector<IP::ip_arr> filtred_vec;
    const IP::ip_arr * params = filter_params.getRawParams();

    int vec_size = input_vac.size();
    for (int i = 0; i < vec_size; ++i)
    {
        IP::IP_Filter input_ip_params(input_vac[i], 4);
        int input_ip_params_size = input_ip_params.getSize();
        int ip_params_size = filter_params.getSize();
        bool validation_passed = false;

        for (int k1 = 0, k2 = 0; k1 < input_ip_params_size && k2 < ip_params_size; ++k1)
        {
            const IP::ip_arr * rawParams = input_ip_params.getRawParams();
            if (validation_passed && (int)(*params)[k2] != (int)(*rawParams)[k1])
            {
                validation_passed = false;
                break;
            }

            if ((int)(*params)[k2] == (int)(*rawParams)[k1])
            {
                ++k2;
                validation_passed = true;
            }
        }
            
        if (validation_passed)
            filtred_vec.emplace_back(input_vac[i]);
    }

    return filtred_vec;
}