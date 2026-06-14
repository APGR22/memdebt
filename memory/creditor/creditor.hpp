#pragma once

#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>

namespace memdebt::memory::creditor
{
    struct T
    {
        int val = 0;

        ~T()
        {
            std::cout << "T is destroyed: " << this->val << std::endl;
        }
    };

    class Creditor
    {
        private:
            std::unordered_map<
                T *,
                std::unique_ptr<T>
            > __src_memory;

        public:
            void add(const T &value)
            {
                auto item = std::make_unique<T>(value);
                item->val = 0;
                this->__src_memory.insert_or_assign(
                    item.get(),
                    std::move(item)
                );
            }

            ~Creditor()
            {
                std::cout << "Creditor is destroyed" << std::endl;
            }
    };
}