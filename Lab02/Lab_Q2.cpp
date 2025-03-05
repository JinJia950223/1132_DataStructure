class Solution {
public:
	vector<int> runningSum(vector<int>& nums) {
		int n =nums.size();//設定n為整個陣列的大小 
		vector<int> result(n);
		
		result[0]=nums[0];//將結果設為nums陣列的第一位，以利接下來的動作 
		for(int i=1; i<n; i++){ //持續迴圈直到跑完整個陣列 
			result[i]=result[i-1]+nums[i];
			//將每一位前面的數字都加起來，並依序存到結果 
		}
		return result;
	}//最後輸出的結果為除了第一位直接輸出，後面每一位數字皆為前面數字的合 
};
