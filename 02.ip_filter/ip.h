
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace IP {

    class IpParams {
        private:
            std::uint8_t * params;
            std::uint8_t size;
        public:
            enum {Limit = 4};
            IpParams(): params(nullptr), size(0) {}
            IpParams(const std::uint8_t * ip_params);
            IpParams(IpParams const &);
            ~IpParams() {
                delete [] params;
                size = 0;
            }
            void operator=(IpParams const &);
            std::uint8_t getSize() const { return size; }
            std::uint8_t * getParams() const { return params; }
    };

    std::vector<IpParams> filter(const std::vector<IpParams> & vec, const IpParams & params);
    std::vector<IpParams> filter_any(const std::vector<IpParams> & vec, const IpParams & params);
}