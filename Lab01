class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        if (nums.size() < 2) //如果只有兩個以下的數字則必為升冪或是降冪
            return true;  
        
        bool up = true,down = true; //預設為正確
        
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] > nums[i+1])  //檢查是否為降冪
                up = false;
            if (nums[i] < nums[i+1])  //檢查是否為升冪
                down = false;
        }
        if(up == false && down == false) //如果兩個都不是，輸出錯誤
            return false;
        else
            return true; //如果兩個都是則輸出正確
    }
};
