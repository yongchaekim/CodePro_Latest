#include <iostream>
using namespace std;

#define MAX_N 8

struct POS {
    int x, y;
};

int N;
POS base[2];
POS pos[MAX_N + 10];

void Input_Data() {
    cin >> N; // Number of parcel collection points
    for (int i = 0; i < 2; i++) { // Parcel office locations
        cin >> base[i].x >> base[i].y;
    }
    for (int i = 0; i < N; i++) { // Parcel collection point locations
        cin >> pos[i].x >> pos[i].y;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ans = -1;

    // Input
    Input_Data();

    // TODO: Write solution here

    // Output
    cout << ans << "\n";
    return 0;
}
