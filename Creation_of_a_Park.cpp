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

char ans;//구매자 이름 Buyer's name
int areacnt;//구매자 영역 개수 Number of buyer's area
int cellcnt;

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
	
	// Bigger Z wins
	// If tie Bigger, C wins
	// If tie Bigger Rank Owner R > G > B
		
	for (auto &iter : zones) {
    char ch = iter.first;
    int z = iter.second;
    int c = cells[ch]; // cells must be computed already

    if (z > areacnt || (z == areacnt && c > cellcnt) || (z == areacnt && c == cellcnt && rankOwner(ch) > rankOwner(ans))) {
        ans = ch;
        areacnt = z;
			  cellcnt = c; 
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

	cout << ans << " " << areacnt << "\n";// 출력하는 부분 Output
	return 0;
}


