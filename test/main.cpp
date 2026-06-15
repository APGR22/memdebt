#include <iostream>
#include <memory>
#include "../memdebt.hpp"

struct test : public memdebt::memory::debtor::enable_debtor_from_this<test>
{
    int val = 10;

    ~test()
    {
        std::cout << "test is destroyed: " << this->val << std::endl;
    }
};

int main()
{
    memdebt::memory::creditor::Creditor<test> creditor;

    test value;
    value.val = 10;

    auto debtor = creditor.add(value);
    debtor->val = 0;

    auto this_debtor = debtor->debtor_from_this();

    std::cout
    << "Are debtor and this_debtor values same: "
    << (debtor.get() == this_debtor.get())
    << std::endl;

    memdebt::memory::debtor::Debtor<test> cp_debtor;
    cp_debtor = debtor;

    std::cout
    << "Are debtor and cp_debtor values same: "
    << (debtor.get() == cp_debtor.get())
    << std::endl;

    debtor.clear();

    std::cout
    << "Has the debtor reset: "
    << !debtor.check()
    << std::endl;

    return 0;
}