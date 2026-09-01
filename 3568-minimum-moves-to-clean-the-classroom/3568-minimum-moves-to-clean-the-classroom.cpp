#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0, K = 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                }
                else if (classroom[r][c] == 'L') {
                    id[r][c] = K++;
                }
            }
        }

        if (K == 0) return 0;

        int states = 1 << K;
        int target = states - 1;

        // best[r][c][mask] = maximum energy seen for this state
        vector<int> best(m * n * states, -1);

        auto index = [&](int r, int c, int mask) {
            return ((r * n + c) * states) + mask;
        };

        struct State {
            int r, c, mask, energy;
        };

        queue<State> q;

        q.push({sr, sc, 0, energy});
        best[index(sr, sc, 0)] = energy;

        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                int curIdx = index(r, c, mask);

                if (best[curIdx] > e)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n ||
                        classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;

                    if (ne < 0)
                        continue;

                    int nmask = mask;

                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    if (nmask == target)
                        return moves + 1;

                    int idx = index(nr, nc, nmask);

                    if (ne > best[idx]) {
                        best[idx] = ne;
                        q.push({nr, nc, nmask, ne});
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};