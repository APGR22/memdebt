#include <iostream>
#include <memory>
#include "../memdebt.hpp"

struct test : public memdebt::memory::debtor::enable_debtor_from_this<test>
{
    int val = 0;

    ~test()
    {
        std::cout << "test is destroyed: " << this->val << std::endl;
    }
};

int main()
{
    memdebt::memory::creditor::Creditor<test> creditor;

    test value;

    auto debtor_1 = creditor.borrow(value);
    debtor_1->val = 1000;

    std::cout
    << "index: "
    << debtor_1.get_index()
    << " | value: "
    << debtor_1->val
    << '\n';

    auto debtor_2 = creditor.borrow(value);
    debtor_2->val = 2000;

    std::cout
    << "index: "
    << debtor_2.get_index()
    << " | value: "
    << debtor_2->val
    << '\n';

    auto debtor_3 = creditor.borrow(value);
    debtor_3->val = 3000;

    std::cout
    << "index: "
    << debtor_3.get_index()
    << " | value: "
    << debtor_3->val
    << '\n';

    creditor.release(debtor_1.get_index());

    std::cout
    << "index: "
    << debtor_3.get_index()
    << " | value: "
    << debtor_3->val
    << '\n';

    auto debtor_4 = creditor.borrow(value);
    debtor_4->val = 4000;

    std::cout
    << "index: "
    << debtor_4.get_index()
    << " | value: "
    << debtor_4->val
    << '\n';

    auto cp_debtor_4 = debtor_4;
    cp_debtor_4.lock_access();

    debtor_4.lock_access();

    creditor.release(debtor_4.get_index());

    if (debtor_4.check())
    {
        std::cout
        << "debtor_4 is saved"
        << " | index: "
        << debtor_4.get_index()
        << " | is null: "
        << (debtor_4.get() == nullptr)
        << " | is read_only null: "
        << (debtor_4.get_read_only() == nullptr)
        << " | locked: "
        << debtor_4.is_locked_access()
        << " | locked by this: "
        << debtor_4.is_locked_access_by_this()
        << '\n';

        debtor_4.unlock_access();
    }

    auto cp_debtor_4_item = debtor_4.copy();
    cp_debtor_4_item->val = 4444;

    return 0;
}