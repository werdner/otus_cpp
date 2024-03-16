#include "ip.h"

namespace IP {
    IpParams::IpParams(const std::uint8_t * ip_params) {
            int num_args = 0;
            while(ip_params[num_args])
                ++num_args;
            if (num_args > Limit)
                num_args = Limit;
            if (num_args > 0)
                params = new std::uint8_t[num_args];
            for (int i = 0; i < num_args; ++i)
                params[i] = ip_params[i];
            size = num_args;  
    }

    IpParams::IpParams(IpParams const & ip): IpParams(ip.params) {}

    void IpParams::operator=(IpParams const & ip)
    {
        int num_args = 0;
        while(ip.params[num_args])
            ++num_args;

        if (num_args > Limit)
            num_args = Limit;
        if (num_args > 0)
            params = new std::uint8_t[num_args];
        for (int i = 0; i < num_args; ++i)
            params[i] = ip.params[i];
        size = num_args; 
    }

    std::vector<IpParams> filter(const std::vector<IpParams> & vec, const IpParams & params)
    {
        std::vector<IpParams> filtredVec;
        std::uint8_t * ip_params = params.getParams();
        
        int vec_size = vec.size();
        for (int i = 0; i < vec_size; ++i)
        {
            std::uint8_t * input_ip_params = vec[i].getParams();
            int input_ip_params_size = vec[i].getSize();
            int ip_params_size = params.getSize();
            bool validation_passed = true;

            for (int k = 0; k < ip_params_size && k < input_ip_params_size; ++k)
            {
                if (ip_params[k] != input_ip_params[k])
                {
                    validation_passed = false;
                    break;
                }
            }
            
            if (validation_passed)
                filtredVec.emplace_back(vec[i]);
        }

        return filtredVec;
    }

    std::vector<IpParams> filter_any(const std::vector<IpParams> & vec, const IpParams & params)
    {
        std::vector<IpParams> filtredVec;
        std::uint8_t * ip_params = params.getParams();

        int vec_size = vec.size();
        for (int i = 0; i < vec_size; ++i)
        {
            std::uint8_t * input_ip_params = vec[i].getParams();
            int input_ip_params_size = vec[i].getSize();
            int ip_params_size = params.getSize();
            bool validation_passed = false;

            for (int k1 = 0, k2 = 0; k1 < input_ip_params_size && k2 < ip_params_size; ++k1)
            {
                if (validation_passed && ip_params[k2] != input_ip_params[k1])
                {
                    validation_passed = false;
                    break;
                }

                if (ip_params[k2] == input_ip_params[k1])
                {
                    ++k2;
                    validation_passed = true;
                }
            }
            
            if (validation_passed)
                filtredVec.emplace_back(vec[i]);
        }

        return filtredVec;
    }
}