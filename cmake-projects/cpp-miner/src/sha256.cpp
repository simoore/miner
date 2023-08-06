#include <algorithm>
#include "miner/sha256.h"

namespace miner {

Sha256::HashValue Sha256::hashBlock(const HashValue &lastHash, const Block &block) {

    uint32_t a = lastHash[0];
    uint32_t b = lastHash[1];
    uint32_t c = lastHash[2];
    uint32_t d = lastHash[3];
    uint32_t e = lastHash[4];
    uint32_t f = lastHash[5];
    uint32_t g = lastHash[6];
    uint32_t h = lastHash[7];

    BigBlock w;
    for (uint32_t j = 0; j < w.size(); j++) {

        if (j < sBlockSize) {
            w[j] = block[j];
        } else {
            w[j] = smallSig1(w[j-2]) + w[j-7] + smallSig0(w[j-15]) + w[j-16];
        }

        uint32_t T1 = calcT1(e, f, g, h, sK[j], w[j]);
        uint32_t T2 = bigSig0(a) + maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    HashValue res = {
        a + lastHash[0], 
        b + lastHash[1], 
        c + lastHash[2], 
        d + lastHash[3],
        e + lastHash[4], 
        f + lastHash[5], 
        g + lastHash[6], 
        h + lastHash[7]
    };
    return res;
} 

Sha256::HashValue Sha256::hash(const uint32_t *data, int nWords) {

    const uint32_t rounds = nWords / sBlockSize;
    const uint32_t nWordsInFinalBlock = nWords % sBlockSize;
    
    Block block;
    HashValue hash = sInitialHash;
    
    for (uint32_t i = 0; i < rounds; i++) {
        std::copy_n(data + i*sBlockSize, sBlockSize, block.begin());
        hash = hashBlock(hash, block);
    }

    // last block(s)
    const bool extraBlock = nWordsInFinalBlock == 14 || nWordsInFinalBlock == 15 || nWordsInFinalBlock == 16;
    const uint64_t l = 32 * nWords;

    std::copy_n(data + rounds*sBlockSize, nWordsInFinalBlock, block.begin());
    std::fill(block.begin() + nWordsInFinalBlock, block.end(), uint32_t(0));
    if (nWordsInFinalBlock != 16) {
        block[nWordsInFinalBlock] = sFirstPadWord;
    }
    if (!extraBlock) {
        std::tie(block[14], block[15]) = length2Words(l);
    }
    hash = hashBlock(hash, block);

    if (extraBlock) {
        std::fill(block.begin(), block.end(), uint32_t(0));
        if (nWordsInFinalBlock == 16) {
            block[0] = sFirstPadWord;
        }
        std::tie(block[14], block[15]) = length2Words(l);
        hash = hashBlock(hash, block);
    }
    return hash;
}

} // namespace miner