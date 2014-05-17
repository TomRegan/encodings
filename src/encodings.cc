//   Copyright 2014 Tom Regan
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.


#include "encodings.h"


namespace encodings {


namespace binary {


void print_byte(uint8_t byte) {
  for (auto i = 0x80; i; i = i >> 1) {
    std::cout << (((byte & i) == i) ? "1" : "0");
  }
  std::cout << '\n';
}

void print_double(uint32_t bits) {
  for (uint32_t i = 0x80000000; i; i = i >> 1) {
    if (i == 0x80 || i == 0x8000 || i == 0x800000) {
      std::cout << ' ';
    }
    std::cout << (((bits & i) == i) ? "1" : "0");
  }
  std::cout << '\n';
}


}  // binary


namespace base64 {


uint8_t to_byte(uint8_t byte) {
  if (byte == '+') {
    return 62;
  } else if (byte == '/') {
    return 63;
  } else if (byte < 58) {
    return byte + 4;
  } else if (byte < 91) {
    return byte - 65;
  }
  return byte - 71;
}

uint8_t from_byte(uint8_t byte) {
  if (byte < 26) {
    return byte + 65;  // ascii A
  } else if (byte < 52) {
    return byte + 71;  // ascii a
  } else if (byte < 62) {
    return byte - 4;   // ascii 0
  } else if (byte == 62) {
    return '+';
 }
  return '/';
}

std::string from_hex(std::string hex_string) {
  auto buffer = std::stringstream();
  while (!hex_string.empty()) {
    uint32_t bitset = std::stoul(hex_string.substr(0, 6), 0, 16);
    hex_string.erase(0, 6);
    while (!(bitset & 0x00ff0000)) {
      bitset <<= 8;
    }
    uint8_t bytemask = 0x3f;
    if (bitset & 0x00fc0000) {
      buffer << from_byte((bitset >> 18) & bytemask);
    }
    if (bitset & 0x0003f000) {
      buffer << from_byte((bitset >> 12) & bytemask) ;
    }
    if (bitset & 0x00000fc0) {
      buffer << from_byte((bitset >> 6) & bytemask);
    }
    if (bitset & 0x0000003f) {
      buffer << from_byte(bitset & bytemask);
    }
    while (buffer.str().size() % 4) {
      buffer << '=';
    }
  }
  return buffer.str();
}


}  // base64


namespace hex {


std::string from_base64(std::string base64_string) {
  auto buffer = std::stringstream();
  while (base64_string.size()) {
    std::string dword = base64_string.substr(0, 4);
    base64_string.erase(0, 4);
    uint32_t bitset = base64::to_byte(dword[0]);
    bitset <<=6;
    bitset |= base64::to_byte(dword[1]);
    bitset <<= 6;
    bitset |= base64::to_byte(dword[2]);
    bitset <<=6;
    bitset |= base64::to_byte(dword[3]);
    if (dword[2] == '=' && dword[3] == '=') {
      bitset >>= 16;
    }
    else if (dword[3]  == '=') {
      bitset >>= 8;
    }
    buffer << std::hex << bitset;
  }
  return buffer.str();
}


}  // hex


}  // encodings
