#include "ChannelCoding.h"
#include "../reed_solomon/ReedSolomon.h"
#include "../bit_scrambling/Cpp/BitScrambling.hpp"

#include <algorithm>
#include <cstddef>     // for Byte and std::to_integer
#include <cstdint>
#include <iostream>
#include <span>
#include <stdexcept>
#include <vector>

namespace sts1cobcsw
{

    void EncodeTelemetry(std::span<Byte, blockLength + overhead> data)
    {
        std::span<Byte, blockLength> subspan(data.begin() + overhead, data.end()); // Extract the message bytes.

        // std::span<data_t> castSpan{reinterpret_cast<data_t*>(subspan.data()), subspan.size()}; // span expects a non-void pointer.
        std::vector<data_t> v(subspan.size());
        for (int i = 0; i < subspan.size(); i++) {
            v[i] = std::to_integer<data_t>(subspan[i]);
        }

        encode_rs_ccsds(v.data(), v.data() + messageLength);
        bitsn::scramble_telemetry(v);

        // Move elements rightwards
        // std::copy_backward(data.begin(), data.end() - (nParitySymbols + overhead), data.end());

        // If convolutional code is used, the ASM shall be convolutionally encoded, too.
        std::memcpy(data.data(), preambleAndSyncMarker.data(), overhead);

        for (int i = 0; i < subspan.size(); i++) {
            subspan[i] = static_cast<Byte>(v[i]);
        }

        std::memcpy(data.data() + overhead, subspan.data(), blockLength);
    }

    void DecodeTelecommands(std::span<Byte, blockLength + overhead> data)
    {
        for (int i = 0; i < preambleAndSyncMarker.size(); i++) {
            if (data[i] != preambleAndSyncMarker[i]) {
                throw std::runtime_error("Error: Invalid preamble or ASM!");
            }
        }

        std::span<Byte> subspan(data.begin() + overhead, data.end());
        std::vector<data_t> v(subspan.size());
        for (int i = 0; i < subspan.size(); i++) {
            v[i] = std::to_integer<data_t>(subspan[i]);
        }

        bitsn::unscramble_telecommand(v);
        decode_rs_ccsds(v.data());

        for (int i = 0; i < v.size(); i++) {
            subspan[i] = static_cast<Byte>(v[i]);
        }

        // std::memcpy(subspan.begin(), subspan.end(), data.data() + overhead);
        std::memcpy(data.data() + overhead, subspan.data(), blockLength);
    }
}
