#pragma once

#include <memory>
#include "../creditor/type.hpp"

namespace memdebt::memory::debtor
{
    template<typename T>
    class Debtor 
    {
        private:
            std::weak_ptr<T> __borrow;
            T *__item;
            creditor::type<T>::iterator __it;

        public:
            Debtor()
            : __item(nullptr)
            {}

            Debtor(
                const std::weak_ptr<T> &borrow,
                T *item,
                const creditor::type<T>::iterator &it
            )
            : __borrow(borrow), __item(item), __it(it)
            {}

            T *get() const
            {
                return this->__item;
            }

            creditor::type<T>::const_iterator get_it_pos() const
            {
                return this->__it;
            }

            void clear()
            {
                this->__borrow.reset();
                this->__item = nullptr;
                this->__it = {};
            }

            bool check() const
            {
                return !(this->__borrow.expired());
            }

            T *operator->() const
            {
                return this->__item;
            }
    };
}