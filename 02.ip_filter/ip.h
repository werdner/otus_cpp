#pragma once

#include <memory>
#include <cstdint>
#include <array>
#include <vector>

namespace IP {
    class IP_Filter
    {
        public:
            static constexpr int LIMIT = 4;
            IP_Filter();
            IP_Filter(const IP_Filter & ip_filter);
            IP_Filter(const std::array<std::uint8_t, LIMIT> & array_ptr, const std::uint8_t size);
            ~IP_Filter();
            void operator=(const IP_Filter & ip_filter);
            const std::shared_ptr<std::array<std::uint8_t, LIMIT> > & getParams() const { return params; }
            const std::array<std::uint8_t, LIMIT> * getRawParams() const { return params.get(); }
            int getSize() const { return size; }
        private:
            std::shared_ptr<std::array<std::uint8_t, LIMIT> > params;
            int size = 0;

    };

    using ip_arr = std::array<std::uint8_t, IP_Filter::LIMIT>;

    const std::vector<ip_arr> filter(const std::vector<ip_arr> input_vac, const IP_Filter & filter_params);
    const std::vector<ip_arr> filter_any(const std::vector<ip_arr> input_vac, const IP_Filter & filter_params);
}