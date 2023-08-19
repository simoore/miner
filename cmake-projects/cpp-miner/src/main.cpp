#include <iostream>
#include <string>

#include "miner/block.h"
#include "miner/miner.h"

int main() {

    miner::BlockHeader header = miner::BlockHeader::genesisBlock();

    auto nonce = miner::Miner::mine(2080000000UL, header);
    
    header.setNonce(nonce);
    auto hashValue = miner::Sha256::hash(miner::Sha256::hash(header.data()));

    std::cout << "Block solved ! Nonce: " << nonce << std::endl;
    miner::Sha256::printHash(hashValue);
    
    return 0;
}
