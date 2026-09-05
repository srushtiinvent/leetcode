class Solution {
public:
    int score(vector<string>& cards, char x) {
        int c = 0;
        int a[26] = {0};
        int b[26] = {0};
        
        for (const string& s : cards) {
            if (s[0] == x && s[1] == x) {
                c++;
            } else if (s[0] == x) {
                a[s[1] - 'a']++;
            } else if (s[1] == x) {
                b[s[0] - 'a']++;
            }
        }
        
        int sa = 0, ma = 0;
        int sb = 0, mb = 0;
        
        for (int i = 0; i < 26; i++) {
            sa += a[i];
            ma = max(ma, a[i]);
            
            sb += b[i];
            mb = max(mb, b[i]);
        }
        
        int ans = 0;
        for (int i = 0; i <= c; i++) {
            int j = c - i;
            
            int p1 = min((sa + i) / 2, sa + i - max(ma, i));
            int p2 = min((sb + j) / 2, sb + j - max(mb, j));
            
            ans = max(ans, p1 + p2);
        }
        
        return ans;
    }
};