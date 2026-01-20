#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A large number bigger than any possible answer (assuming no overflow)
const int INF = 1000000000; // 1e9

struct Pos {
    int x, y;
};

int distance(const Pos& a, const Pos& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int countBits(int mask) {
    int cnt = 0;
    while (mask > 0) {
        cnt += (mask & 1);
        mask >>= 1;
    }
    return cnt;
}

vector<int> buildCostForBase(const Pos& base, const vector<Pos>& points) {
    int N = (int)points.size();
    int ALL = (1 << N);

    vector<vector<int>> dp(ALL, vector<int>(N, INF));
    vector<int> cost(ALL, INF);

    // First pickup: load = 0 => multiplier = 1
    for (int i = 0; i < N; i++) {
        dp[1 << i][i] = distance(base, points[i]);
    }

    // TSP-bitmask style transitions
    for (int mask = 0; mask < ALL; mask++) {
        int load = countBits(mask);

        for (int last = 0; last < N; last++) {
            if ((mask & (1 << last)) == 0) continue;
            int cur = dp[mask][last];
            if (cur >= INF) continue;

            for (int next = 0; next < N; next++) {
                if (mask & (1 << next)) continue;

                int nextMask = mask | (1 << next);
                int moveCost = distance(points[last], points[next]) * (1 + load);

                dp[nextMask][next] = min(dp[nextMask][next], cur + moveCost);
            }
        }
    }

    // Return to base
    cost[0] = 0;
    for (int mask = 1; mask < ALL; mask++) {
        int load = countBits(mask);

        int best = INF;
        for (int last = 0; last < N; last++) {
            if ((mask & (1 << last)) == 0) continue;

            int returnCost = distance(points[last], base) * (1 + load);
            best = min(best, dp[mask][last] + returnCost);
        }
        cost[mask] = best;
    }

    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    Pos base0, base1;
    cin >> base0.x >> base0.y;
    cin >> base1.x >> base1.y;

    vector<Pos> p(N);
    for (int i = 0; i < N; i++) cin >> p[i].x >> p[i].y;

    int ALL_MASK = (1 << N) - 1;

    vector<int> cost0 = buildCostForBase(base0, p);
    vector<int> cost1 = buildCostForBase(base1, p);

    int ans = INF;
    for (int mask = 0; mask <= ALL_MASK; mask++) {
        ans = min(ans, cost0[mask] + cost1[ALL_MASK ^ mask]);
    }

    cout << ans << "\n";
    return 0;
}
