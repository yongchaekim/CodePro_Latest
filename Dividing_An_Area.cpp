#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N;
string Info;

using P = pair<int,int>;
using E = pair<P,P>; // undirected edge (a,b) stored sorted

E make_edge(P a, P b) {
    if (b < a) swap(a, b);
    return {a, b};
}

bool containsPoint(const vector<P>& v, const P& p) {
    for (const auto& x : v) if (x == p) return true;
    return false;
}

bool containsEdge(const vector<E>& v, const E& e) {
    for (const auto& x : v) if (x == e) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Info;

    int dx[4] = {1, -1, 0, 0};   // 0:E, 1:W, 2:S, 3:N
    int dy[4] = {0, 0, -1, 1};

    int x = 0, y = 0;

    vector<P> points;
    vector<E> edges;
    points.push_back({0, 0});

    int enclosed = 0;

    for (char c : Info) {
        int d = c - '0';

        // split each move into 2 steps (handles mid-edge crossings)
        for (int k = 0; k < 2; k++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            P a = {x, y};
            P b = {nx, ny};
            E e = make_edge(a, b);

            if (!containsEdge(edges, e)) {
                if (containsPoint(points, b)) enclosed++; // new area formed
                edges.push_back(e);
                if (!containsPoint(points, b)) points.push_back(b);
            }

            x = nx; y = ny;
        }
    }

    cout << enclosed << "\n";
    return 0;
}
