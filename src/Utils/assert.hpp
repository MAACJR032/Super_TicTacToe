#pragma once

#include <iostream>

void assert(bool condition, std::string_view s)
{
    if (!condition)
    {
        std::cerr << s << '\n';
        exit(1);
    }
}