#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL<<60);
const int MAXN = 8;

struct POS { long long x, y; };

int N;
POS basePos[2];
POS p[MAXN];

int distM(const POS& a, const POS& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Build cost table for one office b (0 or 1):
// cost[mask] = min fuel to start at base[b], visit exactly mask, return to base[b]
void buildCost(int b, long long cost[]) {
    int ALL = (1 << N) - 1;

    static long long dp[1<<MAXN][MAXN]; // dp[mask][last]
    for (int mask = 0; mask <= ALL; mask++) {
        cost[mask] = INF;
        for (int last = 0; last < N; last++) dp[mask][last] = INF;
    }

    // First pickup: load = 0, multiplier = 1
    for (int i = 0; i < N; i++) {
        dp[1<<i][i] = distM(basePos[b], p[i]);
    }

    // Expand masks
    for (int mask = 1; mask <= ALL; mask++) {
        int load = __builtin_popcount((unsigned)mask); // parcels already picked up
        for (int last = 0; last < N; last++) {
            if (!(mask & (1<<last))) continue;
            long long cur = dp[mask][last];
            if (cur >= INF) continue;

            for (int nxt = 0; nxt < N; nxt++) {
                if (mask & (1<<nxt)) continue;
                int nmask = mask | (1<<nxt);

                // move cost uses current load
                long long add = distM(p[last], p[nxt]) * (1LL + load);
                dp[nmask][nxt] = min(dp[nmask][nxt], cur + add);
            }
        }
    }

    // Return to base: load = popcount(mask)
    cost[0] = 0; // no pickups: stay at base
    for (int mask = 1; mask <= ALL; mask++) {
        int load = __builtin_popcount((unsigned)mask);
        for (int last = 0; last < N; last++) {
            if (!(mask & (1<<last))) continue;
            long long back = distM(p[last], basePos[b]) * (1LL + load);
            cost[mask] = min(cost[mask], dp[mask][last] + back);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    cin >> basePos[0].x >> basePos[0].y;
    cin >> basePos[1].x >> basePos[1].y;
    for (int i = 0; i < N; i++) cin >> p[i].x >> p[i].y;

    int ALL = (1 << N) - 1;

    static long long cost0[1<<MAXN], cost1[1<<MAXN];
    buildCost(0, cost0);
    buildCost(1, cost1);

    long long ans = INF;
    for (int mask = 0; mask <= ALL; mask++) {
        ans = min(ans, cost0[mask] + cost1[ALL ^ mask]);
    }

    cout << ans << "\n";
    return 0;
}
