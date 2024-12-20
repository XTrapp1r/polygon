#include <string>
#include <unordered_map>
#include <tuple>
#include <functional>
struct TupleHash {
    template <typename T1, typename T2, typename T3>
    std::size_t operator()(const std::tuple<T1, T2, T3>& t) const {
        std::size_t h1 = std::hash<T1>()(std::get<0>(t));
        std::size_t h2 = std::hash<T2>()(std::get<1>(t));
        std::size_t h3 = std::hash<T3>()(std::get<2>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class Solution {
public:
    int countDigitOne(int n) {
        std::string s = std::to_string(n);
        int m = s.size();
        std::unordered_map<std::tuple<int, int, bool>, int, TupleHash> memo;
        auto dp = [&](auto& self, int pos, int count, bool is_limit) -> int {
            if (pos == m) {
                return count;
            }
            auto key = std::make_tuple(pos, count, is_limit);
            if (memo.find(key) != memo.end()) {
                return memo[key];
            }
            int limit = is_limit ? (s[pos] - '0') : 9;
            int total = 0;
            for (int digit = 0; digit <= limit; ++digit) {
                total += self(self, pos + 1, count + (digit == 1 ? 1 : 0), is_limit && (digit == limit));
            }
            memo[key] = total;
            return total;
        };
        return dp(dp, 0, 0, true);
    }
};
