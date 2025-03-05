class Solution {
public:
    int findLucky(vector<int>& arr) {
        vector<int> luck(501,0); //設一個vector儲存0到500
        //count++
        int max = -1; //預設最大值不在範圍內
        //count++
        for(int i = 0;i < arr.size();i++){ //count+3
            luck[arr[i]]++; //計算每個數字的出現次數
            //count++
        }
        for(int i = 1;i < luck.size();i++){ //count+3
            if(luck[i]==i && luck[i] > max){ //count+2
            //如果數字和出現次數相同，且數值大於最大值
                max = luck[i]; //將最大值換成當前數字
                //count++
            }
        }
        if(max == 0) //如果最大值為零則輸出不存在
        //count++
        //count++
        return -1;
    //count++
    return max;
    }
};
