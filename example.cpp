#include "Hexdump.hpp"

#include <iostream>

int main()
{
    unsigned char data[150];
    unsigned char c = 0;
    for (auto &val : data)
    {
        val = c++;
    }

    std::cout << Hexdump(data) << std::endl;
    std::cout << CustomHexdump<8, true>(data) << std::endl;
    std::cout << CustomHexdump<32, false>(data) << std::endl;
}
