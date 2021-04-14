#pragma once
#include <vector>
#include <limits>
#include <unordered_set>

namespace ut {
    using CardStack = std::vector<int>;
    using Table = std::vector<CardStack>;
}

template<>
struct std::hash<ut::Table> {
std::size_t operator()(const ut::Table& v) const {
    int num = 0;

    for (const ut::CardStack& array : v) {
        for (int current_num : array) {
            num += current_num;
        }
    }

    return std::hash<int>()(num<<2);
}
};
