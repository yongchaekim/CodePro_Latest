#include <iostream>
using namespace std;

int R, C;
int Mat[50][50];

void InputData(void) {
    cin >> R >> C;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cin >> Mat[r][c];
        }
    }
}

void OutputData(void) {
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C); j++) {
            cout << Mat[i][j] << " ";
        }
        cout << endl;
    }
}

#define SWAP(a, b) {int temp = a;a = b;b = temp;}
void Rotate(int sr, int sc, int er, int ec) {
	int a = Mat[sr][sc];
	
	// No ring if height==1 or width==1
  if (sr >= er || sc >= ec) return;
	
	// Down (left column)
    for (int r = sr + 1; r <= er; r++) {
        SWAP(Mat[r][sc], a);
    }

    // Right (bottom row)
    for (int c = sc + 1; c <= ec; c++) {
        SWAP(Mat[er][c], a);
    }

    // Up (right column)
    for (int r = er - 1; r >= sr; r--) {
        SWAP(Mat[r][ec], a);
    }

    // Left (top row)
    for (int c = ec - 1; c >= sc; c--) {
        SWAP(Mat[sr][c], a);
    }
}

void Solve(void) {
    int n = R > C ? R : Cl
    for (int i = 0; i < n; i++) {
        Rotate(0+i, 0+i, R-1-i, C-1-i);
    }
}

int main(void) {
    InputData();
    Solve();
    OutputData();
    return 0;
}
