#pragma once

#include "Configuration.hpp"

#include <array>
#include <cstddef>
#include <span>

namespace sts1cobcsw
{
    inline constexpr auto preambleAndSyncMarker = std::to_array<Byte>({std::byte{0x33}, std::byte{0x33}, std::byte{0x33}, std::byte{0x33},
    std::byte{0x33}, std::byte{0x33}, std::byte{0x33}, std::byte{0x33},
    std::byte{0b00011010}, std::byte{0b11001111}, std::byte{0b11111100}, std::byte{0b00011101}});
    auto Encode(std::span<Byte, blockLength> data) -> void;
    auto Decode(std::span<Byte, blockLength> data) -> void;
}
