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


#include <iostream>
#include <deque>
#include <sstream>
#include <bitset>

#include "encodings.h"

namespace encodings {

namespace binary {

class bytestream {
 public:
  bytestream()
    : stream_(std::deque<uint8_t>())
  {}
  size_t num_bytes() const {return stream_.size();}
  bool has_bytes() const {return num_bytes() > 0;}
  void push(const uint32_t bits) {stream_.push_back(bits);}
  uint8_t pop() {
      auto value = stream_.front();
      stream_.pop_front();
      return value;
  }
 private:
  std::deque<uint8_t> stream_;
};

bytestream from_hex(std::string &hex_string) {
  auto stream = bytestream();
  for (size_t pos = 0; pos < hex_string.size(); pos += 4) {
    uint32_t quad = std::stoul(hex_string.substr(pos, 4), 0, 16);
    uint32_t bitmask = 0xFF000000;
    for (size_t it = 4; it; --it) {
      uint32_t masked_bits = (quad & bitmask) >> (it - 1) * 8;
      if (masked_bits != 0) {
	stream.push(masked_bits);
      }
      bitmask = bitmask >> 8;
    }
  }
  return stream;
}

void print_byte(uint8_t byte) {
  for (auto i = 0x80; i; i = i >> 1) {
    std::cout << (((byte & i) == i) ? "1" : "0");
  }
  std::cout << '\n';
}

void print_quad(uint32_t bits) {
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

uint8_t pop_octet(binary::bytestream &stream) {
  if (stream.num_bytes() == 0) {
    return 0;
  }
  return stream.pop();
}

uint32_t build_array(binary::bytestream &stream) {
  uint32_t array = pop_octet(stream) << 16;
  array = array | pop_octet(stream) << 8;
  array = array | pop_octet(stream);
  return array;
}

uint8_t to_byte(uint8_t byte) {
  if (byte == '+') {
    return 62;
  } else if (byte == '/') {
    return 63;
  } else if (byte < 58) {
    return byte + 4;
  } else if (byte < 90) {
    return byte - 65;
  }
  return byte - 71;    // fingers crossed it's lower a case letter...
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
  auto stream = binary::from_hex(hex_string);
  size_t offset = 0;
  while (stream.has_bytes()) {
    if (stream.num_bytes() - 3 > stream.num_bytes()) {
      offset =  2 - ((stream.num_bytes() - 1) % 3);
    }
    uint32_t array = build_array(stream);
    uint32_t bounds_mask = 0xFC0000;
    for (uint32_t quad = 4; quad > offset ; --quad) {
      uint8_t byte = (array & bounds_mask) >> (quad - 1) * 6;
      bounds_mask = bounds_mask >> 6;
      buffer.put(from_byte(byte));
    }
  }
  for (int i = 0; i < offset; i++) {
    buffer.put('=');
  }
  return buffer.str();
}

}  // base64


namespace hex {

std::string from_base64(std::string base64_string) {
  auto buffer = std::stringstream();
  uint32_t bitset = 0;
  for (auto ch : base64_string) {
    if (ch == '=') {
      if ((bitset & 0x8) == 0x8) {  // is odd byte
	bitset >>= 2;
      } else {
	while ((bitset & 1) ^ 1) {
	  bitset >>= 1;
	}
      }
      break;
    }
    if (bitset > 0) {
      bitset <<= 6;
    }
    bitset |= base64::to_byte(ch);
  }
  std::cout << base64_string << '\t';
  binary::print_quad(bitset);
  buffer << std::hex << bitset;
  return buffer.str();
}

}  // hex


}  // encodings
