#include <vector>
#include <string>
#include <queue>
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        int K = 0; 
        
        vector<vector<int>> litter_id(m, vector<int>(n, -1));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                } else if (classroom[i][j] == 'L') {
                    litter_id[i][j] = K++;
                }
            }
        }

        if (K == 0) return 0;
        
        int target_mask = (1 << K) - 1;

        vector<int> max_energy(m * n * (1 << K), -1);
        auto get_idx = [&](int r, int c, int mask) {
            return (r * n + c) * (1 << K) + mask;
        };

        queue<tuple<int, int, int, int>> q; 
        q.push({start_r, start_c, 0, energy});
        max_energy[get_idx(start_r, start_c, 0)] = energy;

        int steps = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int sz = q.size();
            
            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (max_energy[get_idx(r, c, mask)] > e) continue;

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                        int ne = e - 1; 
                        if (ne < 0) continue; 
                        int nmask = mask;
                        
                        if (classroom[nr][nc] == 'R') {
                            ne = energy; 
                        } else if (classroom[nr][nc] == 'L') {
                            nmask |= (1 << litter_id[nr][nc]);
                        }

                        if (nmask == target_mask) {
                            return steps + 1;
                        }

                        int idx = get_idx(nr, nc, nmask);
                        if (ne > max_energy[idx]) {
                            max_energy[idx] = ne;
                            q.push({nr, nc, nmask, ne});
                        }
                    }
                }
            }
            steps++;
        }
        
        return -1; 
    }
};