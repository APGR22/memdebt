#pragma once

#include <iostream>

// namespace memdebt::type
// {
    struct T
    {
        int val = 0;

        ~T()
        {
            std::cout << "T is destroyed: " << this->val << std::endl;
        }
    };
// }