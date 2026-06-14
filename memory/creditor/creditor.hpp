#pragma once

#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>
#include "../../helper/hex.hpp"
#include "../../dependencies/uuidv7/uuidv7.hpp"

#include "../../type/test.hpp"

namespace memdebt::memory::creditor
{
    class Creditor
    {
        private:
            std::unordered_map<
                std::string,
                std::unique_ptr<T>
            > __src_memory;

        public:
            void add(const T &value)
            {
                auto item = std::make_unique<T>(value);
                item->val = 0;

                auto key = uuidv7();
                std::string key_str = memdebt::helper::hex(key);

                this->__src_memory.insert({key_str, std::move(item)});
            }

            ~Creditor()
            {
                std::cout << "Creditor is destroyed" << std::endl;
            }
    };
}