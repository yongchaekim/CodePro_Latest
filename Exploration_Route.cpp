#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct DATA { 
	int r, c; 
};

const int INF = 1e9;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
		cout.tie(nullptr);

    int R, C;
    cin >> R >> C;
	
		// Input graph as string
    vector<string> g(R);
    for (int i = 0; i < R; i++) cin >> g[i];

		// Make starting data and create vector of digit to store position
    DATA S{-1, -1};
    vector<DATA> digit(10, {-1, -1});
    int n = 0;
	
		// Process the data of the graph. 
		// If the chracter is 'S' then save the Starting data. 
		// If the character is between 1 to 9, change to digits and save the position of the digits
		// get max digit,
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            char ch = g[r][c];
            if (ch == 'S') S = {r, c};
            if ('1' <= ch && ch <= '9') {
                int d = ch - '0';
                digit[d] = {r, c};
                n = max(n, d);
            }
        }
    }

		// If the max digit is 0, then there is no need to compute so return answer as 0
    if (n == 0) { cout << 0 << "\n"; return 0; }

    // nodes: 0 = S, 1..n = digits
    vector<DATA> nodes(n + 1);
    nodes[0] = S;
    for (int i = 1; i <= n; i++) nodes[i] = digit[i];

    // D[i][j] = shortest distance from nodes[i] to nodes[j]
	  // Dijkstra's Algorithm
    vector<vector<int>> D(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i <= n; i++) {
        vector<vector<int>> dist(R, vector<int>(C, -1));
        queue<DATA> q;

        dist[nodes[i].r][nodes[i].c] = 0;
        q.push(nodes[i]);

        while (!q.empty()) {
            DATA cur = q.front(); q.pop();
            for (int k = 0; k < 4; k++) {
                int nr = cur.r + dr[k], nc = cur.c + dc[k];
								// Check boundary of the graph
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
								// Check walls
                if (g[nr][nc] == '*') continue;
                if (dist[nr][nc] != -1) continue;
                dist[nr][nc] = dist[cur.r][cur.c] + 1;
                q.push({nr, nc});
            }
        }

        for (int j = 0; j <= n; j++) {
            int d = dist[nodes[j].r][nodes[j].c];
            if (d != -1) D[i][j] = d;
        }
    }

    // dp[mask][last] = min distance starting at S, visiting digits in mask, ending at node 'last'
    int FULL = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n + 1, INF));
    dp[0][0] = 0;

    for (int mask = 0; mask <= FULL; mask++) {
        for (int last = 0; last <= n; last++) {
            if (dp[mask][last] == INF) continue;

            for (int nxt = 1; nxt <= n; nxt++) {
                int bit = 1 << (nxt - 1);
                if (mask & bit) continue;
                dp[mask | bit][nxt] = min(dp[mask | bit][nxt], dp[mask][last] + D[last][nxt]);
            }
        }
    }

    // Return to S at the end (required to get 18 for the sample)
    int ans = INF;
    for (int last = 1; last <= n; last++) {
        ans = min(ans, dp[FULL][last] + D[last][0]);
    }

    cout << ans << "\n";
    return 0;
}
