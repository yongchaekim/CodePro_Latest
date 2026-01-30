#include <stdio.h>
#include <stdlib.h>

int N;
int M;
int rear_sol;
int front_sol;

int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};
int Map[500][500];

struct Node {
	int row;
	int col;
	int dst;
};

struct Node Queue[100000000];

void Input(void) {
int i, j;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			scanf("%d", &Map[i][j]);
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
		struct Node element = {r, c, 0};
		Map[r][c] = 3;
		Queue[rear_sol] = element;
		rear_sol = (rear_sol+1);
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
	
	while(rear_sol != front_sol) {
		struct Node deq = Queue[front_sol];
		front_sol = (front_sol + 1) ;
		for(int i = 0; i < 4; i++) {
			int nr = deq.row + dr[i];
			int nc = deq.col + dc[i];
			if(Map[nr][nc] == 2) return deq.dst;
			if(Map[nr][nc] != 1) continue;
			int dst = deq.dst + 1;
			struct Node element = {nr, nc, dst};
			Queue[rear_sol] = element;
			rear_sol = (rear_sol+1) ;
			Map[nr][nc] = 3;
		}
	}
	
return -1;
}

int main() {
	Input();
	
	int answer = -1;	
	answer = BST();
	printf("%d", answer);

	return 0;
}
