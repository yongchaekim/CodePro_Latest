#include <iostream>
#include <vector>
#include <utility>   // pair
using namespace std;

int N;
long long T;
long long P[100000 + 10];
long long S[100000 + 10];
int group_first[100000 + 10]; // leaders
int G;

void InputData() {
    cin >> N >> T;
    for (int i = 0; i < N; i++) cin >> P[i] >> S[i];
}

int Solve() {
	
	vector<long long> X(N);
	for(int i=0; i<N; i++) {
		X[i] = P[i] + (S[i]*T);
	}
	
	//Create a Stack
	vector<pair<long long, int>> stk;
	
	for(int i=N-1; i>=0; i--) {
		if(stk.empty() || X[i] < stk.back().first) {
			stk.push_back({X[i], i+1});
		}
	}
	
	G = stk.size();
	for(int i=0; i<G; i++) {
		group_first[i] = stk[i].second;
	}
	return G;
	
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
		cout.tie(NULL);

    InputData();

    int ans = Solve();

    cout << ans << "\n";
    for (int i = 0; i < ans; i++) {
        cout << group_first[i] << (i + 1 == ans ? '\n' : ' ');
    }
    return 0;
}
