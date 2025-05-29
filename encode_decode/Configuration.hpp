#include <cstddef>

namespace sts1cobcsw {
    using Byte = std::byte;
    inline constexpr auto blockLength = 255;
    inline constexpr auto messageLength = 223;
    inline constexpr auto nParitySymbols = 32;
    static_assert(nParitySymbols == blockLength - messageLength);
}