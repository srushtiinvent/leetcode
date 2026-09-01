#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0, K = 0;

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

        if (K == 0)
            return 0;

        const int MASKS = 1 << K;
        const int FULL = MASKS - 1;

        vector<int> best(m * n * MASKS, -1);

        struct State {
            int pos;
            int mask;
            int e;
        };

        vector<State> cur, next;
        cur.reserve(m * n);
        next.reserve(m * n);

        int start = sr * n + sc;

        best[start * MASKS] = energy;
        cur.push_back({start, 0, energy});

        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!cur.empty()) {
            next.clear();

            for (const State &s : cur) {
                int pos = s.pos;
                int r = pos / n;
                int c = pos - r * n;
                int mask = s.mask;
                int e = s.e;

                if (best[pos * MASKS + mask] > e)
                    continue;

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if ((unsigned)nr >= (unsigned)m ||
                        (unsigned)nc >= (unsigned)n ||
                        classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;

                    if (ne < 0)
                        continue;

                    char cell = classroom[nr][nc];
                    int nmask = mask;

                    if (cell == 'L') {
                        nmask |= 1 << id[nr][nc];
                    }

                    if (cell == 'R') {
                        ne = energy;
                    }

                    if (nmask == FULL)
                        return moves + 1;

                    int npos = nr * n + nc;
                    int idx = npos * MASKS + nmask;

                    if (ne > best[idx]) {
                        best[idx] = ne;
                        next.push_back({npos, nmask, ne});
                    }
                }
            }

            cur.swap(next);
            ++moves;
        }

        return -1;
    }
};