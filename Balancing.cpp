#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
		cout.tie(NULL);

    int N;
    cin >> N;

    vector<long long> row(N, 0), col(N, 0);
    long long total = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long long x;
            cin >> x;
            row[i] += x;
            col[j] += x;
            total += x;
        }
    }

    long long S = 0;
    for (int i = 0; i < N; i++) S = max(S, row[i]);
    for (int j = 0; j < N; j++) S = max(S, col[j]);

    long long answer = N * S - total;   // minimal products to add
    cout << answer << "\n";
    return 0;
}
