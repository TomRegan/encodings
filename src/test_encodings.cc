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


#include "gtest/gtest.h"
#include "encodings.h"

using encodings::base64::from_hex;
using encodings::hex::from_base64;

class EncodingsTest : public ::testing::Test {

};

TEST_F(EncodingsTest, ShouldBase64EncodeHex_0041) {
  ASSERT_EQ("QQ==", from_hex("41"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_0049) {
  ASSERT_EQ("SQ==", from_hex("49"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_7375) {
  ASSERT_EQ("c3U=", from_hex("7375"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_4927) {
  ASSERT_EQ("SSc=", from_hex("4927"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_2b2d) {
  ASSERT_EQ("Ky1h", from_hex("2b2d61"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_546f) {
  ASSERT_EQ("VG9t", from_hex("546f6d"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_fade) {
  ASSERT_EQ("+t4=", from_hex("fade"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_ffff) {
  ASSERT_EQ("//8=", from_hex("ffff"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_0065) {
  ASSERT_EQ("ZQ==", from_hex("65"));
}

TEST_F(EncodingsTest, ShouldBase64EncodeHex_7468) {
  ASSERT_EQ("dGhyZWUgYmxpbmQgbWljZQ==",
	from_hex("746872656520626c696e64206d696365"));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_QQ__) {
  ASSERT_EQ("41", from_base64("QQ=="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_SQ__) {
  ASSERT_EQ("49", from_base64("SQ=="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_c3u_) {
  ASSERT_EQ("7375", from_base64("c3U="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_SSc_) {
  ASSERT_EQ("4927", from_base64("SSc="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_Ky1h) {
  ASSERT_EQ("2b2d61", from_base64("Ky1h"));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_VG9t) {
  ASSERT_EQ("546f6d", from_base64("VG9t"));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64___8_) {
  ASSERT_EQ("ffff", from_base64("//8="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64__t4_) {
  ASSERT_EQ("fade", from_base64("+t4="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_ZQ__) {
  ASSERT_EQ("65", from_base64("ZQ=="));
}

TEST_F(EncodingsTest, ShouldHexEncodeBase64_dGhy) {
  ASSERT_EQ("746872656520626c696e64206d696365",
	from_base64("dGhyZWUgYmxpbmQgbWljZQ=="));
}
