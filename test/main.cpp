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
    debtor->val = 1000;

    std::cout
    << "Get referenced: "
    << (*debtor).val
    << std::endl;

    return 0;
}