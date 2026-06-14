#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace memdebt::memory::bank
{
    template<typename T>
    class Bank
    {
        public:
            using type = std::unordered_map<
                        std::string,
                        std::unique_ptr<T>
                    >;

        private:
            type &__access;

        public:
            Bank(type &access)
            : __access(access)
            {}

            T *get(const std::string &key) const
            {
                if (!this->__access.contains(key)) return nullptr;

                return this->__access.at(key).get();
            }
    };
}