#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc, K = 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } else if (classroom[r][c] == 'L') {
                    id[r][c] = K++;
                }
            }
        }

        if (K == 0) return 0;

        const int MASKS = 1 << K;
        const int FULL = MASKS - 1;

        // best[(r*n+c)*MASKS + mask] = maximum energy
        // with which this state has been reached.
        vector<int> best(m * n * MASKS, -1);

        struct State {
            int pos;
            int mask;
            int energy;
        };

        queue<State> q;

        int startPos = sr * n + sc;
        best[startPos * MASKS] = energy;
        q.push({startPos, 0, energy});

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                State cur = q.front();
                q.pop();

                int pos = cur.pos;
                int r = pos / n;
                int c = pos % n;
                int mask = cur.mask;
                int e = cur.energy;

                if (best[pos * MASKS + mask] > e)
                    continue;

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n ||
                        classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    if (ne < 0)
                        continue;

                    int npos = nr * n + nc;
                    int nmask = mask;

                    char cell = classroom[nr][nc];

                    if (cell == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    if (cell == 'R') {
                        ne = energy;
                    }

                    if (nmask == FULL)
                        return moves + 1;

                    int idx = npos * MASKS + nmask;

                    if (ne > best[idx]) {
                        best[idx] = ne;
                        q.push({npos, nmask, ne});
                    }
                }
            }

            ++moves;
        }

        return -1;
    }
};