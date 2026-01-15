#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;
#define MAXN (100)
int N;
vector<string> g;
char bestowner=0;
int bestcount=-1;

int dr[] = {0, 1, 0, -1};
int dc[] = {-1, 0, 1, 0};

struct DATA {
	int r, c;
};

void InputData() {
	cin >> N;
	g.resize(N);
	for (int h = 0; h < N; h++) {
		cin >> g[h];
	}
}

void Solve() {
	
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	map<char,int> zones;
	
	for(int r=0; r<N; r++) {
		for(int c=0; c<N; c++) {
			
			if(visited[r][c]) continue;
			
			visited[r][c] = true;
			char owner = g[r][c];
			zones[owner]++;
			
			queue<DATA> q;
			q.push({r, c});
			
			while(!q.empty()) {
				DATA cur = q.front(); q.pop();
				for(int i=0; i<4; i++) {
					int nr = cur.r + dr[i];
					int nc = cur.c + dc[i];
					if(nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
					if(g[nr][nc] != owner) continue;
					if(visited[nr][nc]) continue;
					q.push({nr, nc});
					visited[nr][nc] = true;
				}
			}
		}
	}
		
		
	for (auto &iter : zones) {
    if (iter.second > bestcount || (iter.second == bestcount && iter.first > bestowner)) {
        bestowner = iter.first;
        bestcount = iter.second;
    }
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	InputData();// 입력받는 부분 Input
	Solve();
	// 여기서부터 작성 Write from here

	cout << bestowner << " " << bestcount << "\n";// 출력하는 부분 Output
	return 0;
}
