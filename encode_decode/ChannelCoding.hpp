#pragma once

#include "../bit_scrambling/Cpp/BitScrambling.hpp"
#include "../reed_solomon/ReedSolomon.h"

#include <cstdint>
#include <span>
#include <vector>

namespace sts1cobcsw
{
    using Byte = std::byte;
    inline constexpr auto blockLength = 255;
    inline constexpr auto messageLength = 223;
    inline constexpr auto nParitySymbols = 32;
    inline constexpr auto overhead = 8 + 4; // preamble and ASM.
    static_assert(nParitySymbols == blockLength - messageLength);
    inline constexpr auto preambleAndSyncMarker = std::to_array<Byte>({std::byte{0x33}, std::byte{0x33}, std::byte{0x33}, std::byte{0x33},
    std::byte{0x33}, std::byte{0x33}, std::byte{0x33}, std::byte{0x33},
    std::byte{0b00011010}, std::byte{0b11001111}, std::byte{0b11111100}, std::byte{0b00011101}});
    void EncodeTelemetry(std::span<Byte, blockLength + overhead> data);
    void DecodeTelecommands(std::span<Byte, blockLength + overhead> data);
}
