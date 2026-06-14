#pragma once

#include <string>
#include "../bank/bank.hpp"

namespace memdebt::memory::debtor
{
    template<typename T>
    class Debtor 
    {
        private:
            bank::Bank<T> __bank;
            std::string __key;

        public:
            Debtor(const bank::Bank<T> &bank, const std::string &key)
            : __bank(bank), __key(key)
            {}

            T &get() const
            {
                return *(this->__bank.get(this->__key));
            }

            const std::string &key() const
            {
                return this->__key;
            }

            bool check() const
            {
                return this->__bank.get(this->__key);
            }

            T *operator->() const
            {
                return this->__bank.get(this->__key);
            }
    };
}