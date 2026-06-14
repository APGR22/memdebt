#include <iostream>
#include "../memory/creditor/creditor.hpp"

struct test
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

    creditor.sub(debtor.key());

    std::cout << "Is the memory still there: " << debtor.check() << std::endl;

    return 0;
}