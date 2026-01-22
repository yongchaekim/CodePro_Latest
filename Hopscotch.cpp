#include <iostream>
using namespace std;

int H; 
int W;
int A[100 + 10][100 + 10];
int N;
int R[100 + 10];
int C[100 + 10];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void InputData(void) {
    cin >> H >> W;
    for (int i=0; i<H; i++) {
        for (int j=0; j<W; j++) {
            cin >> A[i][j];
        }
    }
    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> R[i] >> C[i];
    }
}

void Touch(int r, int c) {
    int V;
    if (A[r][c] == 0) V = 1;
    else V = 0;
    A[r][c] = V;

    for(int k = 0; k < 4; k++) {
        int nr = r;
        int nc = c;
        int flag = 0;

        for (;;) {
            nr = nr + dr[k];
            nc = nc + dc[k];
            if (nr < 0 || nr >= H || nc < 0 || nc >= W) break;
            if (A[nr][nc] == V) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            nr = r;
            nc = c;
            for (;;) {
                nr = nr + dr[k];
                nc = nc + dc[k];
                if (A[nr][nc] == V) {
                    break;
                }
                A[nr][nc] = V;
            }
        }
    }
}

/*
    int dr[8] = {-1,  1,  0,  0, -1, -1,  1,  1};
int dc[8] = { 0,  0, -1,  1, -1,  1, -1,  1};

void Touch(int r, int c) {
    int V = (A[r][c] == 0) ? 1 : 0;
    A[r][c] = V;

    for (int k = 0; k < 8; k++) {
        int nr = r, nc = c;
        bool foundV = false;
        bool bombBetween = false;

        // Scan until we find first V or go out of bounds
        while (true) {
            nr += dr[k];
            nc += dc[k];
            if (nr < 0 || nr >= H || nc < 0 || nc >= W) break;

            if (A[nr][nc] == 2) bombBetween = true;
            if (A[nr][nc] == V) { foundV = true; break; }
        }

        if (!foundV) continue;

        // Apply operation
        nr = r; nc = c;

        if (!bombBetween) {
            // Fill only until the first V
            while (true) {
                nr += dr[k];
                nc += dc[k];
                if (A[nr][nc] == V) break;
                A[nr][nc] = V;
            }
        } else {
            // Bomb exists: fill ALL cells to the border
            while (true) {
                nr += dr[k];
                nc += dc[k];
                if (nr < 0 || nr >= H || nc < 0 || nc >= W) break;
                A[nr][nc] = V; // bombs overwritten too
            }
        }
    }
}
*/

int Solve(void) {
    int cnt = 0;
    for (int i=0; i<N; i++) {
        Touch(R[i], C[i]);
    }

    for(int i = 0; i < H; i++) {
        for (int j =0; j < W; j++) {
            if (A[i][j] == 1) cnt++;
        }
    }
    return cnt;
}

int main(void) {
    int ans = -1;
    InputData();
    ans = Solve();
    cout << ans;
    return 0;
}
