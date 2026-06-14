#include <iostream>
#include "../memory/creditor/creditor.hpp"

int main()
{
    memdebt::memory::creditor::Creditor creditor;

    T value;
    value.val = 10;

    creditor.add(value);

    return 0;
}