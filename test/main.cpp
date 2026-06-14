#include <iostream>
#include "../memory/creditor/creditor.hpp"

struct test
{
    int val = 10;
};

int main()
{
    memdebt::memory::creditor::Creditor<test> creditor;

    test value;
    value.val = 10;

    auto debtor = creditor.add(value);
    debtor->val = 0;

    return 0;
}