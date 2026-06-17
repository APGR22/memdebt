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
            memory_type<T> __src_memory;

        protected:
            inline uint64_t _get_end_index()
            {
                return this->__src_memory.size();
            }

            inline uint64_t _get_last_index()
            {
                return this->__src_memory.size() - 1;
            }

        public:
            debtor::Debtor<T> borrow(const T &value)
            {
                type<T> item = {this->_get_end_index(), value};
                auto item_ptr = std::make_shared<type<T>>(item);

                this->__src_memory.push_back(item_ptr);

                debtor::Debtor<T> debtor(item_ptr, item_ptr.get());

                if constexpr (
                    std::is_base_of_v<debtor::enable_debtor_from_this<T>, T>
                )
                {
                    item_ptr->data.__debtor_base = debtor;
                }

                return debtor;
            }

            bool release(uint64_t index)
            {
                auto &item_ptr = this->__src_memory[index];
                if (item_ptr->lock) return false;

                uint64_t last_index = this->_get_last_index();
                if (index != last_index)
                {
                    auto &last_item_ptr = this->__src_memory[last_index];

                    item_ptr.swap(last_item_ptr);

                    item_ptr->index = index;
                    last_item_ptr->index = last_index;
                }

                this->__src_memory.pop_back();

                return true;
            }

            void clear()
            {
                this->__src_memory.clear();
            }
    };
}