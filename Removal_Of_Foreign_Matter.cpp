#include <iostream>
#include <algorithm>

using namespace std;

int N; // 이물질의 개수
int K; // 장비 최대 사용가능 횟수
int X[50000]; // 이물질의 위치

void InputData() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> X[i];
	}
}

bool compare(int a, int b) {
	return a < b;
}

void sorting() {

	sort(X, X+N, compare);
}

bool canCover(long long V) {
    long long reachLen = 2LL * V;   // one use covers [start, start + 2V] if placed greedily
    int used = 0;
    int i = 0;

    while (i < N) {
        used++;
        if (used > K) return false;

        long long start = X[i];
        long long end = start + reachLen;

        // skip all points covered by this interval
        while (i < N && X[i] <= end) i++;
    }
    return true;
}

long long Solve() {
	
	long long lo = 0, hi = 1000000000LL;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (canCover(mid)) hi = mid;
        else lo = mid + 1;
    }
	
	return lo;
}

int main() {
	long long ans = -1;
	InputData(); // 입력 받는 부분
	
	sorting();

	ans = Solve();
	
	// 여기서부터 작성
	cout << ans << endl;// 출력하는 부분
	return 0;
}
