#include "rs.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <string>

void test_ccsds_short_message() {
  RS::ReedSolomon<223, 32> rs;
  uint8_t data[223] = {};
  std::cout << "size is: " << sizeof(data) << "\n";
  for (int i = 0; i < sizeof(data); i++) {
    // data[i] = rand() % 255;
    data[i] = i;
  }

  uint8_t buffer[255] = {};

  rs.Encode(data, buffer);

  int random = 500;
  for (int i = 0; i < 32; i++) {
    data[(i + random) % 255] = 0;
  }

  uint8_t decoded[223] = {};

  rs.Decode(buffer, decoded);

  for (int i = 0; i < sizeof(decoded); i++) {
    assert(data[i] == decoded[i]);
  }
  std::cout << "Test successful!"
            << "\n";
}

void create_gf() {
  uint8_t exp[255] = {};
  uint8_t log[256] = {};
  uint16_t gen = 0x187;
  uint16_t x = 1;
  for (int i = 0; i < 255; i++) {
      exp[i] = x;
      log[x] = i;
      x <<= 1;
      if (x >= 0x100) {
          x ^= gen;
      }
  }

  for (int i = 0; i < 255; i++) {
    int a = exp[i];
    std::cout << std::showbase << std::hex << a;
    if (i != 0 && i % 15 == 0) {
      std::cout << ",\n";
    } else if (i == 254) {
      std::cout << "\n";
    } else {
      std::cout << ", ";
    }
  }
  for (int i = 0; i < 256; i++) {
    int a = log[i];
    std::cout << std::showbase << std::hex << a;
    if (i != 0 && i % 16 == 0) {
      std::cout << ",\n";
    } else if (i == 255) {
      std::cout << "\n";
    } else {
      std::cout << ", ";
    }
  }

  for (int i = 1; i < 255; i++) {
    std::cout << std::to_string(log[exp[i]]) << " and "
              << std::to_string(exp[log[i]]) << "\n";
    assert(log[exp[i]] == exp[log[i]]);
  }

  std::cout << "Test passed, the tables have been correctly generated!"
            << "\n";
}

int main() {
  // test_ccsds_short_message();
  create_gf();
  return 0;
}
