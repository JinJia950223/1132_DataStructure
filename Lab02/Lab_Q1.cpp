// Method 2
class Solution {
public:
  vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> result; // 存結果
	    int count; // 計數器

	    // 外層迴圈遍歷 nums 陣列中的每個元素
	    for (int i = 0; i < nums.size(); i++){   //count+3
		    count = 0; //count++
		    // 每次重新計算當前元素的較小數量
		    // 內層迴圈再次遍歷 nums 陣列,統計比 nums[i] 小的元素數量
		    for (int j = 0; j < nums.size(); j++) { //count+3
			    if (nums[j] < nums[i]) { count++; } // 如果 nums[j] 比nums[i] 小,則計數器 +1
		    } //count+2
		    result.push_back(count); // 將計算出的數量存入 result
	    }
	    return result; //count++
  }
}; //16n+1
