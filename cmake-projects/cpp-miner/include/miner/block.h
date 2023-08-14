#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <ranges>
#include <span>
#include <string>
#include <vector>

namespace miner {

class BlockHeader {
public:

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC CONSTANTS
    ///////////////////////////////////////////////////////////////////////////

    static constexpr size_t sHeaderSize = 20;
    static constexpr size_t sThresholdSize = 8;
    static constexpr size_t sNibblesPerWord = 8;
    static constexpr size_t sBitsPerByte = 8;
    static constexpr size_t sBitsPerNibble = 4;

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC TYPES
    ///////////////////////////////////////////////////////////////////////////

    using Threshold = std::array<uint32_t, sThresholdSize>;

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC FUNCTIONS
    ///////////////////////////////////////////////////////////////////////////

    BlockHeader(const std::string &version, const std::string &prevhash, const std::string &merkleRoot, 
        const std::string &time, const std::string &nbits) {

        bool ok = (version.size() == 8) && (prevhash.size() == 64) && (merkleRoot.size() == 64) && 
            (time.size() == 8) && (nbits.size() == 8);
 
        if (ok) {
            std::ranges::copy(hexStrToBinary(version), mBlockHeader);
            std::ranges::copy(hexStrToBinary(prevhash), mBlockHeader + 1);
            std::ranges::copy(hexStrToBinary(merkleRoot), mBlockHeader + 9);
            std::ranges::copy(hexStrToBinary(time), mBlockHeader + 17);
            std::ranges::copy(hexStrToBinary(nbits), mBlockHeader + 18);
        }
    }

    uint32_t version(void) const {
        return mBlockHeader[0];
    }

    uint32_t nbits(void) const {
        return mBlockHeader[18];
    }

    uint32_t nonce(void) const {
        return mBlockHeader[19];
    }

    void setNonce(uint32_t nonce) {
        mBlockHeader[19] = nonce;
    }

    std::span<uint32_t> data(void) {
        return std::span<uint32_t>(mBlockHeader, sHeaderSize);
    }

    /// Converts the nbits word in the header to the threshold that the hash of the block must be below to be 
    /// considered a valid hash. See examples on https://developer.bitcoin.org/reference/block_chain.html
    /// TODO: There are some case where nbits and the threshold are negative that I must account for.
    static Threshold nbitsToThreshold(uint32_t nbits) {

        Threshold threshold;
        std::ranges::fill(threshold, 0);

        uint32_t exponent = nbits >> 24;
        uint32_t signifcand = nbits & 0xFFFFFF;

        for (size_t i = 0; i < 3; ++i) {
            if (exponent + i < 3) {
                continue;
            }
            uint32_t byte = (signifcand >> i*8) & 0xFF;
            auto r = std::div(exponent - 3 + i, 4);
            threshold[r.quot] |= byte << 8*r.rem;
        }
        return threshold;
    }

    /// Converts a hex string to a binary representation. We use little endian representation. The first bytes
    /// is the least significant byte of the first word.
    static std::vector<uint32_t> hexStrToBinary(const std::string &hex) {

        static const std::map<char, uint32_t> lookup = {
            {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, 
            {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
        };

        std::vector<uint32_t> binary;
        for (auto elem : hex | std::views::chunk(sNibblesPerWord)) {
            uint32_t value = 0;
            uint32_t shift = 0;
            bool upperNibble = true;
            for (auto e : elem) {
                value += lookup.at(toupper(e)) << shift + (upperNibble ? 4 : 0);
                shift += upperNibble ? 0 : sBitsPerByte;
                upperNibble = !upperNibble;
            }
            binary.push_back(value); 
        } 
        return binary;
    }

private:

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC FIELDS
    ///////////////////////////////////////////////////////////////////////////

    uint32_t mBlockHeader[sHeaderSize]; 

};

}
