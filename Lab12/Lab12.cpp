#include <algorithm>
#include <vector>

class Solution {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        std::vector<int> temp_nums1(nums1.begin(), nums1.begin() + m);

        std::vector<int> arr(m + n);

        int i = 0, j = 0, k = 0;
        while (i < m && j < n) {
            if (temp_nums1[i] <= nums2[j]) {
                arr[k++] = temp_nums1[i++];
            } else {
                arr[k++] = nums2[j++];
            }
        }

        while (i < m) {
            arr[k++] = temp_nums1[i++];
        }
        while (j < n) {
            arr[k++] = nums2[j++];
        }

        nums1 = arr;
    }
};
