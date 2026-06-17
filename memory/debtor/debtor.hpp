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
            bool __is_lock_access_by_this = false;

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

            Debtor(const Debtor &other)
            :
                __borrow(other.__borrow),
                __item(other.__item)
            {}

            Debtor(Debtor &&other)
            :
                __borrow(other.__borrow),
                __item(other.__item),
                __lock_valid_access(other.__lock_valid_access),
                __is_lock_access_by_this(other.__is_lock_access_by_this)
            {
                other.clear();
            }

            T *get() const
            {
                if (this->__item->lock && !this->__is_lock_access_by_this) return nullptr;

                return &(this->__item->data);
            }

            const T *get_read_only() const
            {
                return &(this->__item->data);
            }

            uint64_t get_index() const
            {
                return this->__item->index;
            }

            std::shared_ptr<T> copy() const
            {
                if (auto shared = this->__borrow.lock())
                {
                    return std::make_shared<T>(shared->data);
                }

                return {};
            }

            bool lock_valid()
            {
                if (this->__lock_valid_access = this->__borrow.lock())
                {
                    return true;
                }

                return false;
            }

            bool lock_access()
            {
                if (this->__borrow.expired()) return false;
                if (this->__item->lock && !this->__is_lock_access_by_this) return false;

                this->__item->lock = true;
                this->__is_lock_access_by_this = true;

                return true;
            }

            void unlock_valid()
            {
                this->__lock_valid_access.reset();
            }

            bool unlock_access()
            {
                if (this->__borrow.expired()) return false;
                if (this->__item->lock && !this->__is_lock_access_by_this) return false;

                this->__item->lock = false;
                this->__is_lock_access_by_this = false;

                return true;
            }

            void clear()
            {
                this->unlock_access();
                this->__borrow.reset();
                this->__item = nullptr;
                this->__lock_valid_access.reset();
            }

            bool check() const
            {
                return !(this->__borrow.expired());
            }

            bool is_locked_access() const
            {
                if (this->__borrow.expired()) return false;

                return this->__item->lock;
            }

            bool is_locked_access_by_this() const
            {
                return this->__is_lock_access_by_this;
            }

            Debtor &operator=(const Debtor &other)
            {
                if (this != &other)
                {
                    this->clear();

                    this->__borrow = other.__borrow;
                    this->__item = other.__item;
                }

                return *this;
            }

            Debtor &operator=(Debtor &&other)
            {
                if (this != &other)
                {
                    this->clear();

                    this->__borrow = other.__borrow;
                    this->__item = other.__item;
                    this->__lock_valid_access = other.__lock_valid_access;
                    this->__is_lock_access_by_this = other.__is_lock_access_by_this;

                    other.clear();
                }

                return *this;
            }

            T *operator->() const
            {
                if (this->__item->lock && !this->__is_lock_access_by_this) return nullptr;

                return &(this->__item->data);
            }

            T &operator*() const
            {
                if (this->__item->lock && !this->__is_lock_access_by_this) return nullptr;

                return this->__item->data;
            }

            ~Debtor()
            {
                this->clear();
            }
    };
}