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

    creditor.release(debtor_4.get_index());

    return 0;
}