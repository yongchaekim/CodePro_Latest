#include <iostream>
using namespace std;

int N; // 풍경화의 크기
int a[10 + 10][10 + 10]; // 풍경화
int X1, X2, X3; // 숨은 그림을 의미하는 3개의 숫자

int di[8] = { -1,-1,0,1,1,1,0,-1 };
int dj[8] = { 0,1,1,1,0,-1,-1,-1 };

void InputData(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> a[i][j];
		}
	}
	cin >> X1 >> X2 >> X3;
}

int Solve(void) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (a[i][j] != X1) continue;
			for (int k = 0; k < 8; k++) {
				int ni = i + di[k];
				int nj = j + dj[k];
				if (ni < 0 || ni >= N) continue;
				if (nj < 0 || nj >= N) continue;
				if (a[ni][nj] != X2) continue;
				count++;
			}
		}
	}
	return count;
}

int main(void) {
	int ans = -1;
	InputData(); // 입력

	// 코드 작성
	ans = Solve();


	cout << ans; // 출력
	return 0;
}
