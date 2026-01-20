#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   // llabs
using namespace std;

const long long INF = (1LL << 60);

struct Pos {
    long long x, y;
};

long long manhattan(const Pos& a, const Pos& b) {
    return llabs(a.x - b.x) + llabs(a.y - b.y);
}

int countBits(int mask) {
    int cnt = 0;
    while (mask > 0) {
        cnt += (mask & 1);
        mask >>= 1;
    }
    return cnt;
}

/*
TSP-bitmask style DP for ONE base:
cost[mask] = minimum fuel to start at 'base', visit exactly the points in 'mask', return to 'base'
where moving cost = ManhattanDistance * (1 + currentLoad)
currentLoad = number of already visited points in mask
*/
vector<long long> buildCostForBase(const Pos& base, const vector<Pos>& points) {
    int N = (int)points.size();
    int ALL = (1 << N);

    // dp[mask][last] = minimum fuel to start at base, visit 'mask', end at point 'last'
    vector<vector<long long>> dp(ALL, vector<long long>(N, INF));
    vector<long long> cost(ALL, INF);

    // Like TSP initialization: start -> i
    // load = 0, so multiplier = 1
    for (int i = 0; i < N; i++) {
        dp[1 << i][i] = manhattan(base, points[i]) * 1LL;
    }

    // Like classic TSP bitmask DP transitions
    for (int mask = 0; mask < ALL; mask++) {
        int load = countBits(mask);

        for (int last = 0; last < N; last++) {
            if ((mask & (1 << last)) == 0) continue;   // last must be in mask
            long long cur = dp[mask][last];
            if (cur >= INF) continue;

            for (int next = 0; next < N; next++) {
                if (mask & (1 << next)) continue;      // not visited yet
                int nextMask = mask | (1 << next);

                // Key difference vs classic TSP: edge cost depends on 'load'
                long long moveCost = manhattan(points[last], points[next]) * (1LL + load);

                dp[nextMask][next] = min(dp[nextMask][next], cur + moveCost);
            }
        }
    }

    // Return to base (like "return to start" in TSP)
    cost[0] = 0; // choose no points
    for (int mask = 1; mask < ALL; mask++) {
        int load = countBits(mask);

        long long best = INF;
        for (int last = 0; last < N; last++) {
            if ((mask & (1 << last)) == 0) continue;

            long long returnCost = manhattan(points[last], base) * (1LL + load);
            best = min(best, dp[mask][last] + returnCost);
        }
        cost[mask] = best;
    }

    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    Pos base0, base1;
    cin >> base0.x >> base0.y;
    cin >> base1.x >> base1.y;

    vector<Pos> p(N);
    for (int i = 0; i < N; i++) cin >> p[i].x >> p[i].y;

    int ALL_MASK = (1 << N) - 1;

    // Build subset-cost table for each base (same idea as running TSP DP twice)
    vector<long long> cost0 = buildCostForBase(base0, p);
    vector<long long> cost1 = buildCostForBase(base1, p);

    // Split points between base0 and base1
    long long ans = INF;
    for (int mask = 0; mask <= ALL_MASK; mask++) {
        ans = min(ans, cost0[mask] + cost1[ALL_MASK ^ mask]);
    }

    cout << ans << "\n";
    return 0;
}
