#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

static const int INF = 1000000000;

int R, C, N;
vector<string> g; // resize after reading R,C

struct DATA {
    int r;
    int c;
};

vector<DATA> digit(10, DATA{-1, -1});

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

void Input_Data(void) {
    cin >> R >> C;
    g.resize(R);
    for (int i = 0; i < R; i++) cin >> g[i];
}

int Solve() {
    // find start + digits
    DATA S{-1, -1};
    N = 0;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            char ch = g[r][c];
            if (ch == 'S') S = {r, c};
            if ('1' <= ch && ch <= '9') {
                int d = ch - '0';
                digit[d] = {r, c};
                N = max(N, d);
            }
        }
    }

    if (S.r == -1) return -1;     // no start
    if (N == 0) return 0;         // no targets
	
		// build nodes: 0 = S, 1..N = digits
    vector<DATA> nodes(N + 1);
    nodes[0] = S;
    for (int i = 1; i <= N; i++) {
        if (digit[i].r == -1) return -1; // missing required digit
        nodes[i] = digit[i];
    }
	
		
		// pairwise distances by BFS from each node transforming D in the distance by distance graph
	  /*
		  S 1 2 3 4 5 6 7 8 9
		S 
		1
		2
		3
		4
		5
		6
		7
		8
		9
		*/
    vector<vector<int>> D(N + 1, vector<int>(N + 1, INF));

    for (int i = 0; i <= N; i++) {
        vector<vector<int>> dist(R, vector<int>(C, -1));
        queue<DATA> q;

        dist[nodes[i].r][nodes[i].c] = 0;
        q.push(nodes[i]);

        while (!q.empty()) {
            DATA cur = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nr = cur.r + dr[k];
                int nc = cur.c + dc[k];

                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (g[nr][nc] == '*') continue;
                if (dist[nr][nc] != -1) continue;

                dist[nr][nc] = dist[cur.r][cur.c] + 1;
                q.push({nr, nc});
            }
        }

        for (int j = 0; j <= N; j++) {
            int d = dist[nodes[j].r][nodes[j].c];
            if (d != -1) D[i][j] = d;
        }
    }
	
		// Use Bitwise Traveling Sales Problem to find the shortest Path. Dynamic Programming !!!

	
	int FULL = (1 << N) - 1;
    vector<vector<int>> dp(1 << N, vector<int>(N + 1, INF));
    dp[0][0] = 0;

    for (int mask = 0; mask <= FULL; mask++) {
        for (int last = 0; last <= N; last++) {
            if (dp[mask][last] == INF) continue;

            for (int nxt = 1; nxt <= N; nxt++) {
                int bit = 1 << (nxt - 1);
                if (mask & bit) continue;
                dp[mask | bit][nxt] = min(dp[mask | bit][nxt], dp[mask][last] + D[last][nxt]);
            }
        }
    }

    // Return to S at the end (required to get 18 for the sample)
    int ans = INF;
    for (int last = 1; last <= N; last++) {
        ans = min(ans, dp[FULL][last] + D[last][0]);
    }
	
		/*
		If problem does not need to return to S at the end
		int ans = INF;
		for (int last = 1; last <= N; last++) {
			ans = min(an, dp[FULL][last]);
		}
		*/
		

   return ans;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Input_Data();
    int sol = Solve();
    cout << sol << '\n';
    return 0;
}
