#pragma once

#include <cstdint>
#include <iomanip>
#include <ostream>
#include <span>

template <size_t RowSize, bool ShowAscii>
struct CustomHexdump
{
    CustomHexdump(const std::span<const uint8_t> bytes)
        : mData(bytes.data()), mLength(bytes.size()) {}
    const uint8_t *mData;
    const size_t mLength;
};

template <size_t RowSize, bool ShowAscii>
std::ostream &operator<<(std::ostream &out,
                         const CustomHexdump<RowSize, ShowAscii> &dump)
{
    out.fill('0');

    for (size_t i = 0; i < dump.mLength; i += RowSize)
    {
        out << "0x" << std::setw(6) << std::hex << i << ": ";

        for (size_t j = 0; j < RowSize; ++j)
        {
            if (((RowSize % 2) == 0) && (j == (RowSize / 2)))
                out << " ";

            if (i + j < dump.mLength)
            {

                out << std::hex << std::setw(2)
                    << static_cast<const int>(dump.mData[i + j]) << " ";
            }
            else
                out << "   ";
        }

        out << " ";
        if (ShowAscii)
        {
            out << "|  ";

            for (size_t j = 0; j < RowSize; ++j)
            {
                if (!(i + j < dump.mLength))
                    continue;

                if (std::isprint(dump.mData[i + j]))
                    out << static_cast<const char>(dump.mData[i + j]);
                else
                    out << ".";
            }
        }

        out << std::endl;
    }

    return out;
}

using Hexdump = CustomHexdump<16, true>;
