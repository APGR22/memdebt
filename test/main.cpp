#include <iostream>
#include <memory>
#include <utility>
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

    auto debtor_2 = std::move(debtor_1);

    if (!debtor_1.check())
    {
        std::cout << "Debtor 1 has destroyed because it has moved" << '\n';
    }

    if (debtor_2.check())
    {
        std::cout << "Debtor 2 is valid because moved from Debtor 1" << '\n';
    }

    auto debtor_3 = creditor.borrow(value);
    debtor_3->val = 2000;

    auto debtor_4 = debtor_3;

    if (debtor_3.check())
    {
        std::cout << "Debtor 3 is still valid because it just copied" << '\n';
    }

    if (debtor_4.check())
    {
        std::cout << "Debtor 4 is valid because copied from Debtor 3" << '\n';
    }

    memdebt::memory::debtor::Debtor<test> debtor_5;
    if (!debtor_5.check())
    {
        std::cout << "Debtor 5 is null because it's not from Creditor" << '\n';
    }

    debtor_5 = std::move(debtor_4);

    if (debtor_3.check())
    {
        std::cout << "Debtor 3 is still valid because there's nothing to do with it" << '\n';
    }

    if (!debtor_4.check())
    {
        std::cout << "Debtor 4 has destroyed because it has moved" << '\n';
    }

    if (debtor_5.check())
    {
        std::cout << "Debtor 5 is valid because moved from Debtor 4" << '\n';
    }

    return 0;
}