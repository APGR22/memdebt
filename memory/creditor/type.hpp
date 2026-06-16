#pragma once

#include <vector>
#include <memory>

namespace memdebt::memory::creditor
{
    template<typename T>
    struct type
    {
        uint64_t index;
        T data;
    };

    template<typename T>
    using memory_type = std::vector<std::shared_ptr<type<T>>>;
}