#pragma once

#include <list>
#include <memory>
#include <utility>
#include <iostream>
#include "creditor_fwd.hpp"
#include "type.hpp"
#include "../debtor/debtor.hpp"
#include "../debtor/enable_debtor_from_this.hpp"

namespace memdebt::memory::creditor
{
    template<typename T>
    class Creditor
    {
        private:
            type<T> __src_memory;

        public:
            debtor::Debtor<T> add(const T &value)
            {
                auto item = std::make_shared<T>(value);

                this->__src_memory.push_back(item);

                auto it = this->__src_memory.end();
                it--;

                debtor::Debtor<T> debtor(item, item.get(), it);

                if constexpr (
                    std::is_base_of_v<debtor::enable_debtor_from_this<T>, T>
                )
                {
                    item->__debtor_base = debtor;
                }

                return debtor;
            }

            void sub(const type<T>::const_iterator &it)
            {
                this->__src_memory.erase(it);
            }
    };
}