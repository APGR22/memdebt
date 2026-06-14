#pragma once

#include <string>
#include <array>
#include <format>
#include <cstdint>

namespace memdebt::helper
{
    inline std::string hex(const std::array<uint8_t, 16> &array)
    {
        std::string result;

        for (uint8_t val : array)
        {
            result += std::format("{:02x}", val);
        }

        return result;
    }
}