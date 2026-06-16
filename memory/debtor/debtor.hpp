#pragma once

#include <memory>
#include "../creditor/type.hpp"

namespace memdebt::memory::debtor
{
    template<typename T>
    class Debtor 
    {
        private:
            std::weak_ptr<creditor::type<T>> __borrow;
            creditor::type<T> *__item;

            std::shared_ptr<creditor::type<T>> __lock_valid_access;

        public:
            Debtor()
            : __item(nullptr)
            {}

            Debtor(
                const std::weak_ptr<creditor::type<T>> &borrow,
                creditor::type<T> *item
            )
            : __borrow(borrow), __item(item)
            {}

            T *get() const
            {
                return &(this->__item->data);
            }

            uint64_t get_index() const
            {
                return this->__item->index;
            }

            bool lock_valid()
            {
                if (this->__lock_valid_access = this->__borrow.lock())
                {
                    return true;
                }

                return false;
            }

            void unlock_valid()
            {
                this->__lock_valid_access.reset();
            }

            void clear()
            {
                this->__borrow.reset();
                this->__item = nullptr;
            }

            bool check() const
            {
                return !(this->__borrow.expired());
            }

            T *operator->() const
            {
                return &(this->__item->data);
            }

            T &operator*() const
            {
                return this->__item->data;
            }
    };
}