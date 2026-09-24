#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

const int INF = 1e8; // Sentinel for unreachable amounts

int main() {
    std::vector<int> coins = {1, 2, 5}; // Coin denominations
    int amount = 11;
    int n = coins.size();

    // dp[i][w]: using first i coins to form amount w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, INF));

    // Base case: 0 coins needed to make amount 0
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    // Build table
    for (int i = 1; i <= n; ++i) {
        int coinVal = coins[i - 1];
        for (int w = 1; w <= amount; ++w) {
            // Exclude coin i
            dp[i][w] = dp[i - 1][w];

            // Include coin i (if it fits)
            if (w >= coinVal && dp[i][w - coinVal] != INF) {
                dp[i][w] = std::min(dp[i][w], 1 + dp[i][w - coinVal]);
            }
        }
    }

    // Print DP Table
    std::cout << "=== Minimum Coins DP Table ===\n";
    std::cout << " Coin\\Amt";
    for (int w = 0; w <= amount; ++w) std::cout << std::setw(5) << w;
    std::cout << "\n" << std::string(10 + (amount + 1) * 5, '-') << "\n";

    for (int i = 0; i <= n; ++i) {
        if (i == 0) std::cout << std::setw(8) << "None" << " |";
        else        std::cout << std::setw(6) << coins[i - 1] << " |";

        for (int w = 0; w <= amount; ++w) {
            if (dp[i][w] >= INF) std::cout << std::setw(5) << "INF";
            else                 std::cout << std::setw(5) << dp[i][w];
        }
        std::cout << "\n";
    }

    std::cout << "\nMinimum coins for amount " << amount << ": " 
              << (dp[n][amount] >= INF ? -1 : dp[n][amount]) << "\n";

    return 0;
}
