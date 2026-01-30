#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;


int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};
int N, M;

struct Node {
	int r,c,d;
};

vector<vector<int>> Map;
queue<Node> q;

void Input(void) {
int i, j;
	cin >> N >> M;
	Map.assign(N, vector<int>(M, 0));
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			cin >> Map[i][j];
			Map[i][j]++;
		}
	}
}


int DST(int r, int c) {
	if(Map[r][c] != 2) return 0;
	Map[r][c] = 3;
	int cnt = 0;
	for(int i = 0; i<4; i++) {
		cnt += DST(r+dr[i], c+dc[i]);
	}
	if(cnt < 4) {
		Map[r][c] = 3;
		q.push({r,c,0});
	}
	return 1;
}

void Restruct(void) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			if(Map[i][j] == 2) {
				DST(i, j);
				return;
			}
		}
	}
}


int BST(void) {
	
	Restruct();
	
	while(!q.empty()) {
		Node cur = q.front(); q.pop();
		for(int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if(Map[nr][nc] == 2) return cur.d;
			if(Map[nr][nc] != 1) continue;
			int dst = cur.d + 1;
			q.push({nr, nc, dst});
			Map[nr][nc] = 3;
		}
	}
	
return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Input();
	
	int ans = -1;	
	ans = BST();
	cout << ans << endl;

	return 0;
}
