#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN ((int)2e5)

int N, M;
int ID[MAXN + 10];
int freq[16] = {0};

void InputData() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> ID[i];
}

int bestSimilarInWindow() {
	int best = 0;
        for (int t = 0; t <= 15; t++) {
            int cnt = freq[t];
            if (t - 1 >= 0) cnt += freq[t - 1];
            if (t + 1 <= 15) cnt += freq[t + 1];
            best = max(best, cnt);
        }
        return best;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    InputData();

    // first window [0..M-1]
    for (int i = 0; i < M; i++) freq[ID[i]]++;
    int ans = bestSimilarInWindow();

    // slide window
    for (int start = 1; start <= N - M; start++) {
        int out = ID[start - 1];
        int in  = ID[start + M - 1];

        freq[out]--;
        freq[in]++;

        ans = max(ans, bestSimilarInWindow());
    }

    cout << ans << "\n";
    return 0;
}
