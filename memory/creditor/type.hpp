#pragma once

#include <list>
#include <memory>

// #include "../../type/test.hpp"

namespace memdebt::memory::creditor
{
    template<typename T>
    using type = std::list<std::shared_ptr<T>>;
}