// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: distcoord.capnp

#include "distcoord.capnp.h"

namespace capnp {
namespace schemas {
static const ::capnp::_::AlignedData<26> b_fce2365756d7b39d = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
    157, 179, 215,  86,  87,  54, 226, 252,
     16,   0,   0,   0,   2,   0,   0,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0, 242,   0,   0,   0,
     33,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     29,   0,   0,   0,  55,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     72, 101,  97, 114, 116,  66, 101,  97,
    116,  84, 121, 112, 101,   0,   0,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
      8,   0,   0,   0,   1,   0,   2,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     17,   0,   0,   0,  42,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      1,   0,   0,   0,   0,   0,   0,   0,
      9,   0,   0,   0,  42,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    112, 105, 110, 103,   0,   0,   0,   0,
    112, 111, 110, 103,   0,   0,   0,   0, }
};
::capnp::word const* const bp_fce2365756d7b39d = b_fce2365756d7b39d.words;
#if !CAPNP_LITE
static const uint16_t m_fce2365756d7b39d[] = {0, 1};
const ::capnp::_::RawSchema s_fce2365756d7b39d = {
  0xfce2365756d7b39d, b_fce2365756d7b39d.words, 26, nullptr, m_fce2365756d7b39d,
  0, 2, nullptr, nullptr, nullptr, { &s_fce2365756d7b39d, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
CAPNP_DEFINE_ENUM(HeartBeatType_fce2365756d7b39d, fce2365756d7b39d);
static const ::capnp::_::AlignedData<51> b_c7426d39bcaf282b = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
     43,  40, 175, 188,  57, 109,  66, 199,
     16,   0,   0,   0,   1,   0,   1,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      1,   0,   7,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0, 250,   0,   0,   0,
     33,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     29,   0,   0,   0, 119,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     71, 114, 111, 117, 112,  72, 101,  97,
    114, 116,  66, 101,  97, 116,   0,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
      8,   0,   0,   0,   3,   0,   4,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     41,   0,   0,   0, 114,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     40,   0,   0,   0,   3,   0,   1,   0,
     52,   0,   0,   0,   2,   0,   1,   0,
      1,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   1,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     49,   0,   0,   0, 146,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     52,   0,   0,   0,   3,   0,   1,   0,
     64,   0,   0,   0,   2,   0,   1,   0,
    104, 101,  97, 114, 116,  66, 101,  97,
    116,  84, 121, 112, 101,   0,   0,   0,
     15,   0,   0,   0,   0,   0,   0,   0,
    157, 179, 215,  86,  87,  54, 226, 252,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     15,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    115, 111, 117, 114,  99, 101,  67, 111,
    109, 112, 111, 110, 101, 110, 116,  73,
    100,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0, }
};
::capnp::word const* const bp_c7426d39bcaf282b = b_c7426d39bcaf282b.words;
#if !CAPNP_LITE
static const ::capnp::_::RawSchema* const d_c7426d39bcaf282b[] = {
  &s_fce2365756d7b39d,
};
static const uint16_t m_c7426d39bcaf282b[] = {0, 1};
static const uint16_t i_c7426d39bcaf282b[] = {0, 1};
const ::capnp::_::RawSchema s_c7426d39bcaf282b = {
  0xc7426d39bcaf282b, b_c7426d39bcaf282b.words, 51, d_c7426d39bcaf282b, m_c7426d39bcaf282b,
  1, 2, i_c7426d39bcaf282b, nullptr, nullptr, { &s_c7426d39bcaf282b, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
static const ::capnp::_::AlignedData<35> b_d8629c14bc7a91fa = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
    250, 145, 122, 188,  20, 156,  98, 216,
     16,   0,   0,   0,   1,   0,   0,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      1,   0,   7,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0,   2,   1,   0,   0,
     33,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     29,   0,   0,   0,  63,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     76, 101,  97, 100, 101, 114,  72, 101,
     97, 114, 116,  66, 101,  97, 116,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
      4,   0,   0,   0,   3,   0,   4,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     13,   0,   0,   0, 146,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   3,   0,   1,   0,
     28,   0,   0,   0,   2,   0,   1,   0,
    115, 111, 117, 114,  99, 101,  67, 111,
    109, 112, 111, 110, 101, 110, 116,  73,
    100,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0, }
};
::capnp::word const* const bp_d8629c14bc7a91fa = b_d8629c14bc7a91fa.words;
#if !CAPNP_LITE
static const uint16_t m_d8629c14bc7a91fa[] = {0};
static const uint16_t i_d8629c14bc7a91fa[] = {0};
const ::capnp::_::RawSchema s_d8629c14bc7a91fa = {
  0xd8629c14bc7a91fa, b_d8629c14bc7a91fa.words, 35, nullptr, m_d8629c14bc7a91fa,
  0, 1, i_d8629c14bc7a91fa, nullptr, nullptr, { &s_d8629c14bc7a91fa, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
static const ::capnp::_::AlignedData<36> b_8d54747aa35f644c = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
     76, 100,  95, 163, 122, 116,  84, 141,
     16,   0,   0,   0,   1,   0,   0,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      1,   0,   7,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0,  18,   1,   0,   0,
     37,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     33,   0,   0,   0,  63,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     82, 101, 113, 117, 101, 115, 116,  70,
    111, 114,  86, 111, 116, 101,  82, 101,
    113,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
      4,   0,   0,   0,   3,   0,   4,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     13,   0,   0,   0, 146,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   3,   0,   1,   0,
     28,   0,   0,   0,   2,   0,   1,   0,
    115, 111, 117, 114,  99, 101,  67, 111,
    109, 112, 111, 110, 101, 110, 116,  73,
    100,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0, }
};
::capnp::word const* const bp_8d54747aa35f644c = b_8d54747aa35f644c.words;
#if !CAPNP_LITE
static const uint16_t m_8d54747aa35f644c[] = {0};
static const uint16_t i_8d54747aa35f644c[] = {0};
const ::capnp::_::RawSchema s_8d54747aa35f644c = {
  0x8d54747aa35f644c, b_8d54747aa35f644c.words, 36, nullptr, m_8d54747aa35f644c,
  0, 1, i_8d54747aa35f644c, nullptr, nullptr, { &s_8d54747aa35f644c, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
static const ::capnp::_::AlignedData<52> b_f94e1231cc4b13d6 = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
    214,  19,  75, 204,  49,  18,  78, 249,
     16,   0,   0,   0,   1,   0,   0,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      2,   0,   7,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0,  18,   1,   0,   0,
     37,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     33,   0,   0,   0, 119,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     82, 101, 113, 117, 101, 115, 116,  70,
    111, 114,  86, 111, 116, 101,  82, 101,
    112,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
      8,   0,   0,   0,   3,   0,   4,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     41,   0,   0,   0, 146,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     44,   0,   0,   0,   3,   0,   1,   0,
     56,   0,   0,   0,   2,   0,   1,   0,
      1,   0,   0,   0,   1,   0,   0,   0,
      0,   0,   1,   0,   1,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     53,   0,   0,   0,  82,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     52,   0,   0,   0,   3,   0,   1,   0,
     64,   0,   0,   0,   2,   0,   1,   0,
    115, 111, 117, 114,  99, 101,  67, 111,
    109, 112, 111, 110, 101, 110, 116,  73,
    100,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    118, 111, 116, 101,  70, 111, 114,  73,
    100,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     12,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0, }
};
::capnp::word const* const bp_f94e1231cc4b13d6 = b_f94e1231cc4b13d6.words;
#if !CAPNP_LITE
static const uint16_t m_f94e1231cc4b13d6[] = {0, 1};
static const uint16_t i_f94e1231cc4b13d6[] = {0, 1};
const ::capnp::_::RawSchema s_f94e1231cc4b13d6 = {
  0xf94e1231cc4b13d6, b_f94e1231cc4b13d6.words, 52, nullptr, m_f94e1231cc4b13d6,
  0, 2, i_f94e1231cc4b13d6, nullptr, nullptr, { &s_f94e1231cc4b13d6, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
static const ::capnp::_::AlignedData<68> b_f33d21662bc326c4 = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
    196,  38, 195,  43, 102,  33,  61, 243,
     16,   0,   0,   0,   1,   0,   0,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      3,   0,   7,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0, 250,   0,   0,   0,
     33,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     29,   0,   0,   0, 175,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     76, 101,  97, 100, 101, 114,  69, 108,
    101,  99, 116, 105, 111, 110,   0,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
     12,   0,   0,   0,   3,   0,   4,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     69,   0,   0,   0, 130,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     68,   0,   0,   0,   3,   0,   1,   0,
     80,   0,   0,   0,   2,   0,   1,   0,
      1,   0,   0,   0,   1,   0,   0,   0,
      0,   0,   1,   0,   1,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     77,   0,   0,   0, 146,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     80,   0,   0,   0,   3,   0,   1,   0,
     92,   0,   0,   0,   2,   0,   1,   0,
      2,   0,   0,   0,   2,   0,   0,   0,
      0,   0,   1,   0,   2,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     89,   0,   0,   0, 146,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     92,   0,   0,   0,   3,   0,   1,   0,
    104,   0,   0,   0,   2,   0,   1,   0,
    108, 101,  97, 100, 101, 114,  72, 101,
     97, 114, 116,  66, 101,  97, 116,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
    250, 145, 122, 188,  20, 156,  98, 216,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    114, 101, 113, 117, 101, 115, 116,  70,
    111, 114,  86, 111, 116, 101,  82, 101,
    113,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
     76, 100,  95, 163, 122, 116,  84, 141,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    114, 101, 113, 117, 101, 115, 116,  70,
    111, 114,  86, 111, 116, 101,  82, 101,
    112,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
    214,  19,  75, 204,  49,  18,  78, 249,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0, }
};
::capnp::word const* const bp_f33d21662bc326c4 = b_f33d21662bc326c4.words;
#if !CAPNP_LITE
static const ::capnp::_::RawSchema* const d_f33d21662bc326c4[] = {
  &s_8d54747aa35f644c,
  &s_d8629c14bc7a91fa,
  &s_f94e1231cc4b13d6,
};
static const uint16_t m_f33d21662bc326c4[] = {0, 2, 1};
static const uint16_t i_f33d21662bc326c4[] = {0, 1, 2};
const ::capnp::_::RawSchema s_f33d21662bc326c4 = {
  0xf33d21662bc326c4, b_f33d21662bc326c4.words, 68, d_f33d21662bc326c4, m_f33d21662bc326c4,
  3, 3, i_f33d21662bc326c4, nullptr, nullptr, { &s_f33d21662bc326c4, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
static const ::capnp::_::AlignedData<50> b_8a25ecc657bf2ed3 = {
  {   0,   0,   0,   0,   5,   0,   6,   0,
    211,  46, 191,  87, 198, 236,  37, 138,
     16,   0,   0,   0,   1,   0,   1,   0,
     69,  25, 169,  50, 210, 204, 180, 165,
      1,   0,   7,   0,   0,   0,   2,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     21,   0,   0,   0, 250,   0,   0,   0,
     33,   0,   0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     29,   0,   0,   0, 119,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 105, 115, 116,  99, 111, 111, 114,
    100,  46,  99,  97, 112, 110, 112,  58,
     71, 114, 111, 117, 112,  73, 110, 116,
    101, 114, 110,  97, 108, 115,   0,   0,
      0,   0,   0,   0,   1,   0,   1,   0,
      8,   0,   0,   0,   3,   0,   4,   0,
      0,   0, 255, 255,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     41,   0,   0,   0, 122,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     40,   0,   0,   0,   3,   0,   1,   0,
     52,   0,   0,   0,   2,   0,   1,   0,
      1,   0, 254, 255,   0,   0,   0,   0,
      0,   0,   1,   0,   1,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     49,   0,   0,   0, 122,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     48,   0,   0,   0,   3,   0,   1,   0,
     60,   0,   0,   0,   2,   0,   1,   0,
    103, 114, 111, 117, 112,  72, 101,  97,
    114, 116,  66, 101,  97, 116,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
     43,  40, 175, 188,  57, 109,  66, 199,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    108, 101,  97, 100, 101, 114,  69, 108,
    101,  99, 116, 105, 111, 110,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
    196,  38, 195,  43, 102,  33,  61, 243,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     16,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0, }
};
::capnp::word const* const bp_8a25ecc657bf2ed3 = b_8a25ecc657bf2ed3.words;
#if !CAPNP_LITE
static const ::capnp::_::RawSchema* const d_8a25ecc657bf2ed3[] = {
  &s_c7426d39bcaf282b,
  &s_f33d21662bc326c4,
};
static const uint16_t m_8a25ecc657bf2ed3[] = {0, 1};
static const uint16_t i_8a25ecc657bf2ed3[] = {0, 1};
const ::capnp::_::RawSchema s_8a25ecc657bf2ed3 = {
  0x8a25ecc657bf2ed3, b_8a25ecc657bf2ed3.words, 50, d_8a25ecc657bf2ed3, m_8a25ecc657bf2ed3,
  2, 2, i_8a25ecc657bf2ed3, nullptr, nullptr, { &s_8a25ecc657bf2ed3, nullptr, nullptr, 0, 0, nullptr }
};
#endif  // !CAPNP_LITE
}  // namespace schemas
}  // namespace capnp

// =======================================================================================

namespace riaps {
namespace distrcoord {

// GroupHeartBeat
#ifndef _MSC_VER
constexpr uint16_t GroupHeartBeat::_capnpPrivate::dataWordSize;
constexpr uint16_t GroupHeartBeat::_capnpPrivate::pointerCount;
#endif
#if !CAPNP_LITE
constexpr ::capnp::Kind GroupHeartBeat::_capnpPrivate::kind;
constexpr ::capnp::_::RawSchema const* GroupHeartBeat::_capnpPrivate::schema;
constexpr ::capnp::_::RawBrandedSchema const* GroupHeartBeat::_capnpPrivate::brand;
#endif  // !CAPNP_LITE

// LeaderHeartBeat
#ifndef _MSC_VER
constexpr uint16_t LeaderHeartBeat::_capnpPrivate::dataWordSize;
constexpr uint16_t LeaderHeartBeat::_capnpPrivate::pointerCount;
#endif
#if !CAPNP_LITE
constexpr ::capnp::Kind LeaderHeartBeat::_capnpPrivate::kind;
constexpr ::capnp::_::RawSchema const* LeaderHeartBeat::_capnpPrivate::schema;
constexpr ::capnp::_::RawBrandedSchema const* LeaderHeartBeat::_capnpPrivate::brand;
#endif  // !CAPNP_LITE

// RequestForVoteReq
#ifndef _MSC_VER
constexpr uint16_t RequestForVoteReq::_capnpPrivate::dataWordSize;
constexpr uint16_t RequestForVoteReq::_capnpPrivate::pointerCount;
#endif
#if !CAPNP_LITE
constexpr ::capnp::Kind RequestForVoteReq::_capnpPrivate::kind;
constexpr ::capnp::_::RawSchema const* RequestForVoteReq::_capnpPrivate::schema;
constexpr ::capnp::_::RawBrandedSchema const* RequestForVoteReq::_capnpPrivate::brand;
#endif  // !CAPNP_LITE

// RequestForVoteRep
#ifndef _MSC_VER
constexpr uint16_t RequestForVoteRep::_capnpPrivate::dataWordSize;
constexpr uint16_t RequestForVoteRep::_capnpPrivate::pointerCount;
#endif
#if !CAPNP_LITE
constexpr ::capnp::Kind RequestForVoteRep::_capnpPrivate::kind;
constexpr ::capnp::_::RawSchema const* RequestForVoteRep::_capnpPrivate::schema;
constexpr ::capnp::_::RawBrandedSchema const* RequestForVoteRep::_capnpPrivate::brand;
#endif  // !CAPNP_LITE

// LeaderElection
#ifndef _MSC_VER
constexpr uint16_t LeaderElection::_capnpPrivate::dataWordSize;
constexpr uint16_t LeaderElection::_capnpPrivate::pointerCount;
#endif
#if !CAPNP_LITE
constexpr ::capnp::Kind LeaderElection::_capnpPrivate::kind;
constexpr ::capnp::_::RawSchema const* LeaderElection::_capnpPrivate::schema;
constexpr ::capnp::_::RawBrandedSchema const* LeaderElection::_capnpPrivate::brand;
#endif  // !CAPNP_LITE

// GroupInternals
#ifndef _MSC_VER
constexpr uint16_t GroupInternals::_capnpPrivate::dataWordSize;
constexpr uint16_t GroupInternals::_capnpPrivate::pointerCount;
#endif
#if !CAPNP_LITE
constexpr ::capnp::Kind GroupInternals::_capnpPrivate::kind;
constexpr ::capnp::_::RawSchema const* GroupInternals::_capnpPrivate::schema;
constexpr ::capnp::_::RawBrandedSchema const* GroupInternals::_capnpPrivate::brand;
#endif  // !CAPNP_LITE


}  // namespace
}  // namespace

