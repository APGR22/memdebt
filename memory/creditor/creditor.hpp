#pragma once

#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>
#include "../bank/bank.hpp"
#include "../debtor/debtor.hpp"
#include "../../helper/hex.hpp"
#include "../../dependencies/uuidv7/uuidv7.hpp"

namespace memdebt::memory::creditor
{
    template<typename T>
    class Creditor
    {
        private:
            bank::Bank<T>::type __src_memory;

        public:
            debtor::Debtor<T> add(const T &value)
            {
                auto item = std::make_unique<T>(value);

                auto key = uuidv7();
                std::string key_str = memdebt::helper::hex(key);

                this->__src_memory.insert({key_str, std::move(item)});

                bank::Bank<T> bank(this->__src_memory);
                return debtor::Debtor<T>(bank, key_str);
            }

            void sub(const std::string &key)
            {
                this->__src_memory.erase(key);
            }
    };
}