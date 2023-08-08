#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "miner/block.h"

using namespace ::testing;

class TestFixture_Block : public Test {
protected:
};

TEST_F(TestFixture_Block, TestHexStrToBinary) {
    miner::BlockHeader::hexStrToBinary("0123456789ABCDEF");

    auto binary = miner::BlockHeader::hexStrToBinary("0000000400000002");
    ASSERT_EQ(binary.size(), 2);
    ASSERT_EQ(binary[0], 2);
    ASSERT_EQ(binary[1], 4);

    binary = miner::BlockHeader::hexStrToBinary("D3421A423F980");
    ASSERT_EQ(binary.size(), 2);
    ASSERT_EQ(binary[0], 2753821056);
    ASSERT_EQ(binary[1], 865313);
}