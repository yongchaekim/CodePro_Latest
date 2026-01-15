#include <iostream>
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

int BinarySearch(int s, int e, int d) {
	while(s<=e) {
		int m=(s+e)/2;
		if(A[m] == d) return m;
		else if(A[m]>d) e=m-1;
		else s=m+1;
	}
	return -1;
}

int BinarySearchLower(int s, int e, int d) {
	int sol=-1;
	while(s<=e) {
		int m=(s+e)/2;
		if(A[m]==d) {
			sol = m;
			e=m-1;
		} 
		else if(A[m]>d) e=m-1;
		else s=m+1;
	}
	return sol;
}

int BinarySearchUpper(int s, int e, int d) {
	int sol=-1;
	while(s<=e) {
		int m=(s+e)/2;
		if(A[m]==d) {
			sol=m;
			s=s+1;
		}
		else if(A[m]>d) {
			e=m-1;
		} else {
			s=m+1;
		}
	}
}


void Solve() {

	
}

int main() {
	int ans = -1;
	InputData(); // 입력 받는 부분

	
	
	// 여기서부터 작성
	cout << ans << endl;// 출력하는 부분
	return 0;
}
