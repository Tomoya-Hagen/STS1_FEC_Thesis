#include "rs.hpp"
<<<<<<< HEAD
#include "../encode_decode/encode_decode.h"

#include <bitset>
=======

>>>>>>> fix_rs
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
<<<<<<< HEAD
#include <vector>
#include <stdlib.h>

void test_ccsds_short_message() {
  
  // 205 204 203 202 4 5 6 7 8 9 247 11 12 13 14 15 16 17 18 19 20 17 22 23 24 25 26 27 28 29 30 31 65 33 34 35 36 37 38 39 40 41 42 217
  //  44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 
  //  88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 
  //  125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 
  //  159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 
  //  193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 
  // notice the intervals of the errors and where the last error was inserted. at the multiple of 11 and stops at position (11 * 4 - 1)? with value 217
  RS::ReedSolomon<223, 32> rs;
  uint8_t data[223] = {};
  // std::cout << "size is: " << sizeof(data) << "\n";
=======

void test_ccsds_short_message() {
  RS::ReedSolomon<223, 32> rs;
  uint8_t data[223] = {};
  std::cout << "size is: " << sizeof(data) << "\n";
>>>>>>> fix_rs
  for (int i = 0; i < sizeof(data); i++) {
    // data[i] = rand() % 255;
    data[i] = i;
  }

<<<<<<< HEAD
  std::cout << "\n";

  uint8_t buffer[255] = {};

  sts1cobcsw::ConvertBases(data, true, 223);

  rs.Encode(data, buffer);

  sts1cobcsw::ConvertBases(buffer, false, 255);

  std::cout << "encoded: ";
  for (int x : buffer) {
    std::cout << std::to_string(x) << " ";
  }
  std::cout << "\n";

  for (int i = 0; i < 1; i++) {
    buffer[i] = 205 - i;
=======
  uint8_t buffer[255] = {};

  rs.Encode(data, buffer);

  int random = 500;
  for (int i = 0; i < 32; i++) {
    data[(i + random) % 255] = 0;
>>>>>>> fix_rs
  }

  uint8_t decoded[223] = {};

<<<<<<< HEAD
  sts1cobcsw::ConvertBases(buffer, true, 255);

  rs.Decode(buffer, decoded);

  sts1cobcsw::ConvertBases(decoded, false, 223);

  sts1cobcsw::ConvertBases(data, false, 223);

  for (int i = 0; i < sizeof(decoded); i++) {
    std::cout << std::to_string(decoded[i]) << " ";
    // assert(data[i] == decoded[i]);
  }
  std::cout << "\n" << (rs.had_errors() ? "Had errors" : "No errors") << "\n" << (rs.error_correction_successful() ? "Errors corrected" : "Not corrected") << "\n";
  // std::cout << "\n" << "Test successful!"
            // << "\n";
=======
  rs.Decode(buffer, decoded);

  for (int i = 0; i < sizeof(decoded); i++) {
    assert(data[i] == decoded[i]);
  }
  std::cout << "Test successful!"
            << "\n";
>>>>>>> fix_rs
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
<<<<<<< HEAD
    std::cout << std::bitset<8>{static_cast<unsigned long long>(a)};
=======
    std::cout << std::showbase << std::hex << a;
>>>>>>> fix_rs
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
<<<<<<< HEAD
    std::cout << std::bitset<8>{static_cast<unsigned long long>(a)};
=======
    std::cout << std::showbase << std::hex << a;
>>>>>>> fix_rs
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

<<<<<<< HEAD
double sqrt(double x) {
  if (x < 2) {
    return x;
  }

  double left = 0;
  double right = x / 2;
  double e = 0.00001;
  double y = 0;
  double mid, sqrt;

  while (left <= right) {
    mid = (left + (right - left)) / 2;
    sqrt = mid * mid;
    if (std::abs(x - sqrt) < e) {
      return mid;
    } else if (x > sqrt) {
      y = mid;
      left = mid;
    } else if (x < sqrt) {
      right = mid;
    }
  }

  return y;
}
void markVisited(std::vector<std::vector<int>>& grid, int x, int y) {
  if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] != 1) {
    return;
  }
  grid[x][y] = 0;
  markVisited(grid, x - 1, y);
  markVisited(grid, x + 1, y);
  markVisited(grid, x, y - 1);
  markVisited(grid, x, y + 1);
}

int numberOfIsland(std::vector<std::vector<int>> grid) {
  int n = grid.size();
  int m = grid[0].size();
  int count = 0;

  for (std::vector<int> row : grid) {
    assert(row.size() == m);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 1) {
        markVisited(grid, i , j);
        count++;
      }
    }
  }

  return count;
}

int gcd(int x, int y) {
  int z;

  while (y != 0) {
    z = y;
    y = x % y;
    x = z;
  }
  return x;

}

std::vector<int> twoSum(std::vector<int>& n, int t) {
  std::vector<int> p;

  std::sort(n.begin(), n.end());
  
  for (int i = 0; i < n.size() - 1; i++) {
    for (int j = i + 1; j < n.size(); j++) {
      if (n[i] + n[j] == t) {
        p.push_back(n[i]);
        p.push_back(n[j]);
      }
    }
  }
  return p;
}

void moveZeros(std::vector<int>& nums) {
  int pos = 0;

  for (int x : nums) {
    if (x != 0) {
      nums[pos++] = x;
    }
  }

  for (; pos < nums.size(); pos++) {
    nums[pos] = 0;
  }
}

void bubbleSort(std::vector<int>& nums) {
  bool swapped;
  for (int i = 0; i < nums.size(); i++) {
    swapped = false;
    for (int j = 0; j < nums.size() - i - 1; j++) {
      if (nums[j] > nums[j + 1]) {
        nums[j] ^= nums[j + 1];
        nums[j + 1] ^= nums[j];
        nums[j] ^= nums[j + 1];
        swapped = true;
      }
    }
    if (swapped == false) {
      return;
    }
  }
}


int main() {
  test_ccsds_short_message();
  double maxDouble = std::numeric_limits<double>::max();
  double minDouble = std::numeric_limits<double>::min();
  // create_gf();

=======
int main() {
  // test_ccsds_short_message();
  create_gf();
>>>>>>> fix_rs
  return 0;
}
