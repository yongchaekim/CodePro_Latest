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
char bestowner='B';
int bestcount, bestcells;

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

int rankOwner(char ch) {
    if (ch == 'R') return 3;
    if (ch == 'G') return 2;
    return 1; // 'B'
}

void Solve() {
	
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	map<char,int> zones;
	map<char,int> cells;
	
	for(int r=0; r<N; r++) {
		for(int c=0; c<N; c++) {
			
			if(visited[r][c]) continue;
			
			visited[r][c] = true;
			char owner = g[r][c];
			zones[owner]++;
			cells[owner]++;
			
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
					cells[owner]++;
				}
			}
		}
	}
	
		
	for (auto &iter : zones) {
    char ch = iter.first;
    int z = iter.second;
    int c = cells[ch]; // cells must be computed already

    if (z > bestcount || (z == bestcount && c > bestcells) || (z == bestcount && c == bestcells && rankOwner(ch) > rankOwner(bestowner))) {
        bestowner = ch;
        bestcount = z;
			  bestcells = c; 
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
