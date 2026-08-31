class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first_critical = 0, prev_critical = 0, min_dist = -1;
        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1; 
        
        while (curr && curr->next) {
            if ((curr->val > prev->val && curr->val > curr->next->val) || 
                (curr->val < prev->val && curr->val < curr->next->val)) {
                
                if (first_critical == 0) {
                    first_critical = index;
                } else {
                    int current_dist = index - prev_critical;
                    if (min_dist == -1 || current_dist < min_dist) {
                        min_dist = current_dist;
                    }
                }
                prev_critical = index;
            }
            prev = curr;
            curr = curr->next;
            index++;
        }
        
        if (min_dist == -1) return {-1, -1};
        
        return {min_dist, prev_critical - first_critical};
    }
};