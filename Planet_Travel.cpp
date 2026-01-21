#include <iostream>
#include <vector>
using namespace std;

int N;
int W[100000 + 10];

void InputData() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> W[i];
}

long long Solve() {
    long long ans = 0;

    // stack stores (mass, how many consecutive equal masses)
    vector<pair<int,int>> st;


    for (int i = 0; i < N; i++) {
        int h = W[i];

        // Remove smaller masses:
        // With the strict rule, current can connect to only the nearest one in each popped block.
        while (!st.empty() && st.back().first < h) {
            ans += 1;
            st.pop_back();
        }

        if (st.empty()) {
            st.push_back({h, 1});
        }
        else if (st.back().first == h) {
            // Strict rule: current can connect only to the immediate previous equal (adjacent)
            ans += 1;
            st.back().second += 1;
        }
        else { // st.back().first > h
            // Can connect to the nearest taller one
            ans += 1;
            st.push_back({h, 1});
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    InputData();
    cout << Solve() << "\n";
    return 0;
}
