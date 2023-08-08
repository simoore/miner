#include <cctype>
#include <cstdint>
#include <map>
#include <ranges>
#include <string>
#include <vector>

namespace miner {

class BlockHeader {
public:

    static constexpr int sNibblesPerWord = 8;
    static constexpr int sBitsPerNibble = 4;

    /// Converts a hex string to a binary representation.
    /// For example miner::BlockHeader::hexStrToBinary("D3421A423F980") gives [2753821056, 865313]
    static std::vector<uint32_t> hexStrToBinary(const std::string &hex) {

        static const std::map<char, uint32_t> lookup = {
            {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, 
            {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
        };

        std::vector<uint32_t> binary;
        for (auto elem : hex | std::views::reverse | std::views::chunk(sNibblesPerWord)) {
            uint32_t value = 0;
            uint32_t shift = 0;
            for (auto e : elem) {
                value += lookup.at(toupper(e)) << shift;
                shift += sBitsPerNibble;
            }
            binary.push_back(value); 
        } 
        return binary;
    }
};

}
