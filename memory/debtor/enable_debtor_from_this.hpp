#pragma once

#include "debtor.hpp"
#include "../creditor/creditor_fwd.hpp"

namespace memdebt::memory::debtor
{
    template<typename T>
    class enable_debtor_from_this
    {
        private:
            Debtor<T> __debtor_base;

            friend class creditor::Creditor<T>;

        public:
            enable_debtor_from_this() {}

            const Debtor<T> &debtor_from_this() const
            {
                return this->__debtor_base;
            }
    };
}