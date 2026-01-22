#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
		cout.tie(nullptr);

    int S, E1, E2;
    cin >> S >> E1 >> E2;

    const int MAXN = 9999;

    // 1) divisor count for every number up to 9999
    vector<int> divCnt(MAXN + 1, 0);
    for (int i = 1; i <= MAXN; i++) {
        for (int j = i; j <= MAXN; j += i) {
            divCnt[j]++;
        }
    }

    // 2) BFS
    vector<int> dist(MAXN + 1, -1);
    queue<int> q;
    dist[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == E1 && dist[E2] != -1) break;
        if (cur == E2 && dist[E1] != -1) break;

        int d0 = cur / 1000;           // thousands
        int d1 = (cur / 100) % 10;     // hundreds
        int d2 = (cur / 10) % 10;      // tens
        int d3 = cur % 10;             // ones

        // Try changing each digit (exactly one digit differs)
        for (int pos = 0; pos < 4; pos++) {
            for (int nd = 0; nd <= 9; nd++) {
                int nxt = cur;

                if (pos == 0) { // thousands
                    if (nd == d0) continue;
                    if (nd == 0) continue;         // must stay 4-digit
                    nxt = cur + (nd - d0) * 1000;
                } else if (pos == 1) { // hundreds
                    if (nd == d1) continue;
                    nxt = cur + (nd - d1) * 100;
                } else if (pos == 2) { // tens
                    if (nd == d2) continue;
                    nxt = cur + (nd - d2) * 10;
                } else { // ones
                    if (nd == d3) continue;
                    nxt = cur + (nd - d3);
                }

                // Rule 2 (based on your example): divisor count difference <= 1
                if (abs(divCnt[cur] - divCnt[nxt]) > 1) continue;

                if (dist[nxt] == -1) {
                    dist[nxt] = dist[cur] + 1;
                    q.push(nxt);
                }
            }
        }
    }

    cout << dist[E1] << "\n";
    cout << dist[E2] << "\n";
    return 0;
}
