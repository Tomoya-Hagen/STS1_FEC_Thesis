#include "test.h"
#include "ChannelCoding.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <format>
#include <iostream>
#include <numeric>
#include <random>
#include <span>
#include <stdlib.h>
#include <string>
#include <vector>

// void test_encode_decode_short()
// {
//     auto src = std::vector<std::uint8_t>();

//     std::cout << "input: ";
//     for (int i = 0; i < 223; i++)
//     {
//         // src.push_back(rand() % 50);
//         src.push_back(i);
//         std::cout << std::to_string(src[i]) << " ";
//     }
//     std::cout << "\n";

//     auto dst = std::vector<std::uint8_t>();
//     sts1cobcsw::Encode(src, dst);
//     int control_size = dst.size(); // the size of the total code word. used to test the string of the code word.
//     auto encoded = std::string();

//     for (int i = 0; i < dst.size(); i++)
//     {
//         auto x = dst[i];
//         auto byte = std::string();
//         int limit = 8;
//         while (limit > 0)
//         {
//             byte += (x & 1 ? '1' : '0');
//             x >>= 1;
//             limit--;
//         }

//         // last byte
//         if (i == dst.size() - 1)
//         {
//             int index = 0;
//             int j = 0;
//             while (j < byte.size())
//             { // find the first '1' to cut off the bits before it. E.g. 00000001 => index = 7
//                 if (byte[j] == '1')
//                 {
//                     index = j;
//                     break;
//                 }
//                 j++;
//             }
//             int lim = 8 - index;
//             while (lim > 0)
//             {
//                 encoded += byte[index--];
//                 lim--;
//             }
//         }

//         std::reverse(byte.begin(), byte.end());
//         encoded += byte;
//     }
//     std::cout << "\nencoded: " << encoded << "\n";

//     auto decoded = codec.DecodeToString(encoded);
//     decoded = decoded.substr(0, decoded.size() - 3); // Cut off 3 last bits since the src.size() will always be odd
//     auto buffer = std::vector<std::uint8_t>();

//     auto byte = 0;
//     for (int i = 0; i < decoded.size(); i++)
//     {
//         byte = (byte << 1) | (decoded[i] - '0');
//         if (i != 0 && i % 7 == 0)
//         {
//             assert(byte >= 0 && byte <= 0b11111111);
//             buffer.push_back(byte);
//             byte = 0;
//         }
//     }

//     if (byte != 0)
//     {
//         buffer.push_back(byte);
//     }

//     std::cout << "after cc decoding, size: " << buffer.size() << " code word: ";
//     for (auto x : buffer)
//     {
//         std::cout << std::to_string(x) << " ";
//     }
//     std::cout << "\n";

//     auto destination = std::vector<std::uint8_t>();
//     sts1cobcsw::Decode(buffer, destination);
//     std::cout << "src: " << src.size() << "\n";
//     std::cout << "destination: " << destination.size() << "\n";
//     assert(src.size() == destination.size());
//     for (auto x : destination)
//     {
//         std::cout << std::to_string(x) << " ";
//     }
//     for (int i = 0; i < src.size(); i++) {
//         assert(src[i] == destination[i]);
//     }
//     std::cout << "Test 'test_encode_decode_short' passed" << "\n";
// }

// void test_encode_decode_long()
// {
//     srand(static_cast<unsigned>(time(0)));
//     auto src = std::vector<std::uint8_t>();

//     for (int i = 0; i < 1000; i++)
//     {
//         src.push_back(rand() % 255);
//     }

//     std::vector<std::uint8_t> dst;
//     sts1cobcsw::Encode(src, dst);

//     auto encoded = std::string();

//     for (auto x : dst)
//     {
//         encoded += (x - '0');
//     }

//     auto decoded = encoded; // = codec.Decode(encoded);

//     std::vector<std::uint8_t> buffer;

//     for (char bit : decoded)
//     {
//         buffer.push_back(bit - '0');
//     }

//     auto destination = std::vector<std::uint8_t>();
//     sts1cobcsw::Decode(buffer, destination);

//     assert(src.size() == destination.size());
//     for (int i = 0; i < src.size(); i++)
//     {
//         assert(src[i] == destination[i]);
//     }
//     std::cout << "Test 'test_encode_decode_long' passed" << "\n";
// }

// void test_encode_decode_insert_error_success()
// {
//     auto src = std::vector<std::uint8_t>();

//     srand(static_cast<unsigned>(time(0)));
//     for (int i = 0; i < 500; i++)
//     {
//         src.push_back(rand() % 255);
//     }

//     std::vector<std::uint8_t> dst;
//     sts1cobcsw::Encode(src, dst);

//     auto encoded = std::string();

//     for (auto x : dst)
//     {
//         encoded += (x - '0');
//     }

//     int errors = 8;
//     assert(errors < encoded.size());
//     int pos = encoded.size() / 2;
//     for (int i = 0; i < errors; i++)
//     {
//         if (encoded[pos + i] == '0')
//         {
//             encoded[pos + i] = '1';
//         }
//         else
//         {
//             encoded[pos + i] = '0';
//         }
//     }
//     auto decoded = encoded; //  = codec.Decode(encoded);

//     auto buffer = std::vector<std::uint8_t>();

//     for (char bit : decoded)
//     {
//         buffer.push_back(bit - '0');
//     }

//     auto destination = std::vector<std::uint8_t>();
//     sts1cobcsw::Decode(buffer, destination);

//     assert(src.size() == destination.size());
//     for (int i = 0; i < src.size(); i++)
//     {
//         assert(src[i] == destination[i]);
//     }
//     std::cout << "Test 'test_encode_decode_insert_error_success' passed" << "\n";
// }

// void test_encode_decode_insert_error_fail()
// {
// }

// void test_preamble_and_sync_marker()
// {
//     auto buffer = std::vector<std::uint8_t>();
//     buffer.resize(255);
//     std::fill(buffer.begin(), buffer.end(), 1);
//     sts1cobcsw::AppendPreambleAndSyncMarker(buffer);
//     assert(buffer.size() == 263);
//     auto sync_marker = std::array<uint16_t, 4>{0b00011010, 0b11001111, 0b11111100, 0b00011101};
//     for (int i = 0; i < buffer.size(); i++)
//     {
//         auto x = buffer[i];
//         if (i < 4)
//         {
//             assert(x == 0x33);
//         }
//         if (i >= 4 && i < 8)
//         {
//             assert(x == sync_marker[i - 4]);
//         }
//         std::cout << std::to_string(x) << " ";
//     }
//     std::cout << "\n";
//     std::cout << "Test 'test_preamble_and_sync_marker' passed" << "\n";
// }

// void test_basis_conversion()
// {
//     srand(static_cast<unsigned>(time(0)));
//     auto random_factor = (rand() % 10) + 1;
//     assert(random_factor >= 0 && random_factor <= 10);
//     auto size = random_factor * 255;
//     std::cout << "data length: " << std::to_string(size) << " (factor: " << std::to_string(random_factor) << ")\n";
//     auto buffer = std::vector<uint8_t>();
//     buffer.resize(size);
//     for (int i = 0; i < size; i++)
//     {
//         buffer[i] = rand() % 255;
//     }
//     // std::iota(buffer.begin(), buffer.begin() + 255, 0); // the symbols periodically repeat themselves in interval 0-255.

//     auto lab_rat_buffer = std::vector<uint8_t>();
//     lab_rat_buffer.resize(size);
//     std::copy(buffer.begin(), buffer.end(), lab_rat_buffer.begin());
//     sts1cobcsw::ConvertBases(lab_rat_buffer.data(), true, lab_rat_buffer.size());

//     auto counter = 0;
//     for (uint8_t c : lab_rat_buffer)
//     {
//         if (counter % 15 == 0)
//         {
//             std::cout << "\n";
//         }
//         counter++;
//         std::cout << std::to_string(c) << " ";
//     }

//     sts1cobcsw::ConvertBases(lab_rat_buffer.data(), false, lab_rat_buffer.size());

//     for (int i = 0; i < buffer.size(); i++)
//     {
//         assert(buffer[i] == lab_rat_buffer[i]);
//     }

//     std::cout << "\nbasis conversion test successful!" << "\n";
// }

void test_one_block() {
    auto src = std::vector<std::byte>();
    src.resize(sts1cobcsw::blockLength + sts1cobcsw::overhead);

    std::cout << "input: ";
    for (int i = sts1cobcsw::overhead; i < sts1cobcsw::messageLength + sts1cobcsw::overhead; i++)
    {
        // src.push_back(rand() % 50);
        src.push_back(static_cast<std::byte>(i));
        std::cout << std::to_string(i) << " ";
    }
    std::cout << "\nEncoded: ";

    std::span<std::byte, sts1cobcsw::blockLength + sts1cobcsw::overhead> span{src};

    sts1cobcsw::EncodeTelemetry(span);

    std::memcpy(src.data(), span.data(), span.size());

    for (std::byte x : src) {
        std::cout << std::to_string(static_cast<std::uint8_t>(x)) << " ";
    }
    std::cout << "\nDecoded: ";

    std::span<std::byte, sts1cobcsw::blockLength + sts1cobcsw::overhead> span2{src};

    sts1cobcsw::DecodeTelecommands(span2);

    for (std::byte x : src) {
        std::cout << std::to_string(static_cast<std::uint8_t>(x)) << " ";
    }
    std::cout << "\n";

}

void test_simple() {
    std::vector<sts1cobcsw::Byte> data(sts1cobcsw::blockLength + sts1cobcsw::overhead);
    std::vector<sts1cobcsw::Byte> buffer(sts1cobcsw::blockLength + sts1cobcsw::overhead);
    std::mt19937 rng(10); // fixed seed for repeatability
    std::uniform_int_distribution<int> dist(0, 255);

    for (size_t i = 0; i < sts1cobcsw::messageLength; ++i) {
        data[sts1cobcsw::overhead + i] = static_cast<sts1cobcsw::Byte>(dist(rng));
        buffer[sts1cobcsw::overhead + i] = data[sts1cobcsw::overhead + i];
    }

    auto original = std::vector<sts1cobcsw::Byte>(data.begin() + sts1cobcsw::overhead, data.end());

    sts1cobcsw::Encode(std::span<sts1cobcsw::Byte, sts1cobcsw::blockLength + sts1cobcsw::overhead>(data.data(), data.size()));

    data[sts1cobcsw::overhead + 10] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 11] ^= static_cast<sts1cobcsw::Byte>(0xF1);
    data[sts1cobcsw::overhead + 12] ^= static_cast<sts1cobcsw::Byte>(0x1F);
    data[sts1cobcsw::overhead + 13] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 14] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 15] ^= static_cast<sts1cobcsw::Byte>(0xF1);
    data[sts1cobcsw::overhead + 16] ^= static_cast<sts1cobcsw::Byte>(0x1F);
    data[sts1cobcsw::overhead + 17] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 18] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 20] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 21] ^= static_cast<sts1cobcsw::Byte>(0xF1);
    data[sts1cobcsw::overhead + 22] ^= static_cast<sts1cobcsw::Byte>(0x1F);
    data[sts1cobcsw::overhead + 23] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    data[sts1cobcsw::overhead + 24] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    // data[sts1cobcsw::overhead + 25] ^= static_cast<sts1cobcsw::Byte>(0xF1);
    data[sts1cobcsw::overhead + 26] ^= static_cast<sts1cobcsw::Byte>(0x1F);
    data[sts1cobcsw::overhead + 27] ^= static_cast<sts1cobcsw::Byte>(0xFF);
    // data[sts1cobcsw::overhead + 28] ^= static_cast<sts1cobcsw::Byte>(0xFF);

    sts1cobcsw::Decode(std::span<sts1cobcsw::Byte, sts1cobcsw::blockLength + sts1cobcsw::overhead>(data.data(), data.size()));

    for (int i = sts1cobcsw::overhead; i < sts1cobcsw::messageLength + sts1cobcsw::overhead; i++) {
        assert(buffer[i] == data[i]);
    }
    std::cout << "\nSimple Test successful!\n";
}


int main()
{
    // test_encode_decode_short();
    // test_encode_decode_long();
    // test_encode_decode_insert_error_success();
    // test_encode_decode_insert_error_fail();
    // test_preamble_and_sync_marker();
    // test_basis_conversion();
    // test_one_block();
    test_simple();
    return 0;
}