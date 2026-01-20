#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   // abs
using namespace std;

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

/*
Nodes:
  0 = base
  1..N = pickup points (points[0] is node 1, ...)

mask bits represent visited pickup nodes:
  bit (node-1) corresponds to pickup node (1..N)
*/
vector<int> buildCostForBase(const Pos& base, const vector<Pos>& points) {
    int N = (int)points.size();
    int FULL = (1 << N) - 1;

    // Distance matrix D[0..N][0..N]
    vector<vector<int>> D(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++) {
        D[0][i] = D[i][0] = distance(base, points[i - 1]);
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            D[i][j] = distance(points[i - 1], points[j - 1]);
        }
    }

    // dp[mask][last] = min cost to start at 0, visit 'mask', end at node 'last' (0..N)
    vector<vector<int>> dp(1 << N, vector<int>(N + 1, INF));
    dp[0][0] = 0;

    for (int mask = 0; mask <= FULL; mask++) {
        int load = countBits(mask); // parcels already picked

        for (int last = 0; last <= N; last++) {
            if (dp[mask][last] == INF) continue;

            for (int nxt = 1; nxt <= N; nxt++) {
                int bit = 1 << (nxt - 1);
                if (mask & bit) continue;

                int moveCost = D[last][nxt] * (1 + load);
                dp[mask | bit][nxt] = min(dp[mask | bit][nxt],
                                          dp[mask][last] + moveCost);
            }
        }
    }

    // Build cost[mask] using the same "return to S (node 0)" structure
    vector<int> cost(1 << N, INF);
    cost[0] = 0;

    for (int mask = 1; mask <= FULL; mask++) {
        int load = countBits(mask);

        // Same structure as:
        // ans = min(ans, dp[mask][last] + D[last][0])
        // but with multiplier for return:
        int ans = INF;
        for (int last = 1; last <= N; last++) {
            int bit = 1 << (last - 1);
            if ((mask & bit) == 0) continue;

            ans = min(ans, dp[mask][last] + D[last][0] * (1 + load));
        }
        cost[mask] = ans;
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

    int FULL = (1 << N) - 1;

    vector<int> cost0 = buildCostForBase(base0, p);
    vector<int> cost1 = buildCostForBase(base1, p);

    int best = INF;
    for (int mask = 0; mask <= FULL; mask++) {
        best = min(best, cost0[mask] + cost1[FULL ^ mask]);
    }

    cout << best << "\n";
    return 0;
}
