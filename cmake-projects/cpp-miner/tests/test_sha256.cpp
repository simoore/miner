#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "miner/sha256.h"

using namespace ::testing;

class TestFixture_Sha256 : public Test {
protected:
};

TEST_F(TestFixture_Sha256, TestCHFunc) {
    uint32_t x = 0x6;
    uint32_t y = 0x3;
    uint32_t z = 0x8;
    uint32_t expected = 0xA;
    uint32_t actual = miner::Sha256::ch(x, y, z);
    ASSERT_EQ(actual, expected);
}

TEST_F(TestFixture_Sha256, TestEmptyHash) {

    miner::Sha256::Block input = {
        0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    };
    
    miner::Sha256::HashValue expected = {
        0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924, 0x27ae41e4, 0x649b934c, 0xa495991b, 0x7852b855
    };

    auto actual = miner::Sha256::hashBlock(miner::Sha256::sInitialHash, input);

    ASSERT_EQ(actual, expected);
}

TEST_F(TestFixture_Sha256, TestHashBlock1) {

    miner::Sha256::Block input = {
        0x61626380, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000018
    };
    
    miner::Sha256::HashValue expected = {
        0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad
    };

    auto actual = miner::Sha256::hashBlock(miner::Sha256::sInitialHash, input);

    ASSERT_EQ(actual, expected);
}

TEST_F(TestFixture_Sha256, TestHashBlock2) {

    miner::Sha256::Block input = {
        0x61626364, 0x62636465, 0x63646566, 0x64656667, 0x65666768, 0x66676869, 0x6768696a, 0x68696a6b,
        0x696a6b6c, 0x6a6b6c6d, 0x6b6c6d6e, 0x6c6d6e6f, 0x6d6e6f70, 0x6e6f7071, 0x80000000, 0x00000000
    };
    
    miner::Sha256::HashValue expected = {
        0x85e655d6, 0x417a1795, 0x3363376a, 0x624cde5c, 0x76e09589, 0xcac5f811, 0xcc4b32c1, 0xf20e533a
    };

    auto actual = miner::Sha256::hashBlock(miner::Sha256::sInitialHash, input);

    ASSERT_EQ(actual, expected);
}

TEST_F(TestFixture_Sha256, TestHashBlock3) {

    miner::Sha256::HashValue initial = {
        0x85e655d6, 0x417a1795, 0x3363376a, 0x624cde5c, 0x76e09589, 0xcac5f811, 0xcc4b32c1, 0xf20e533a
    };

    miner::Sha256::Block input = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000001c0
    };
    
    miner::Sha256::HashValue expected = {
        0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1
    };

    auto actual = miner::Sha256::hashBlock(initial, input);

    ASSERT_EQ(actual, expected);
}

TEST_F(TestFixture_Sha256, TestLength2Words) {
    auto [w1, w2] = miner::Sha256::length2Words(448);
    ASSERT_EQ(w1, 0);
    ASSERT_EQ(w2, 0x1c0);
}

TEST_F(TestFixture_Sha256, TestCalcT1) {
    uint32_t e = 0x9243f8af; 
    uint32_t f = 0x839a0fc9; 
    uint32_t g = 0xee1c97a8; 
    uint32_t h = 0x443ed29e;
    uint32_t k = 0x9bdc06a7;
    uint32_t w = 0x80000000;
    uint32_t actual = miner::Sha256::calcT1(e, f, g, h, k, w);
    ASSERT_EQ(actual, 0xd87ff922);
    ASSERT_EQ(actual + 0xb8e2b4cb, 0x9162aded);
}

TEST_F(TestFixture_Sha256, TestVector1) {

    std::vector<uint32_t> input = {
        0x61626364, 0x62636465, 0x63646566, 0x64656667, 0x65666768, 0x66676869, 0x6768696a, 0x68696a6b,
        0x696a6b6c, 0x6a6b6c6d, 0x6b6c6d6e, 0x6c6d6e6f, 0x6d6e6f70, 0x6e6f7071
    };

    miner::Sha256::HashValue expected = {
        0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1
    };

    auto actual = miner::Sha256::hash(std::span<const uint32_t>(input.data(), input.size()));

    ASSERT_EQ(actual, expected);
}
