class Solution {
public:
    bool isPalindrome(int x) {
        int org = x;
        int rev=0;
        if(x<0)
        {
            return false;
        }
        if(x==0)
        {
            return true;
        }
        while(x>0)
        {
            int r = x % 10;
            x = x /10;
            if(rev >INT_MAX/10 || rev==INT_MAX/10 && r >7)
            {
                return false;
            }
            if(rev<INT_MIN/10 || rev == INT_MIN/10 && r<-8)
            {
                return false;
            }
            rev = rev *10 + r;
            if(org==rev)
            {
                return true;
            }
        }
        return false;
    }
};