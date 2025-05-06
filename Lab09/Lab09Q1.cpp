#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// 從文件中讀取數據並存入向量
vector<int> readFromFile(const string& filename) {
    vector<int> arr;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return arr;
    }

    string line;
    while (getline(file, line)) {  // 持續讀取整行內容
        stringstream ss(line);     // 創建字符串流
        string value;
        while (getline(ss, value, ',')) {  // 用逗號分隔值
            try {
                arr.push_back(stoi(value));  // 將字符串轉換為整數並存入向量
            } catch (exception& e) {
                cerr << "Invalid number format in file: " << value << endl;
            }
        }
    }

    file.close();
    return arr;
}

class MaxHeap {
   public:
    vector<int> heap;  // 儲存Max Heap的元素

    // 建立Max Heap
    void buildMaxHeap(vector<int>& arr) {
        heap = arr;

        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {  // 從最後一個非葉子節點開始向上執行Max Heap
            heapify(i);
        }
    }

    void heapify(int i) {       // 堆化函式（確保以 i 為根的子樹符合Max Heap性質）
        int largest = i;        // 假設當前節點是最大的
        int left = 2 * i + 1;   // 左子節點索引
        int right = 2 * i + 2;  // 右子節點索引

        // 檢查左子節點是否為有效範圍且比當前節點大
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        // 檢查右子節點是否為有效範圍且比當前節點大
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        // 如果父節點不是最大的，交換並繼續
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);  // 遞迴處理子樹
        }
    }

    // 顯示Heap的內容(使用BFS)
    void printHeap() {
        for (int val : heap) {   // 遍歷 Max Heap中的每個元素
            cout << val << " ";  // 輸出元素
        }
        cout << endl;
    }
};

int main() {
    // 從文件讀取輸入元素
    string filename = "./input3.txt";          // 請貼上input檔案的正確路徑
    vector<int> arr = readFromFile(filename);  // 讀取數據

    if (arr.empty()) {                                   // 如果數據為空
        cerr << "No valid data found in file." << endl;  // 輸出錯誤信息
        return -1;
    }

    cout << "Input Array: ";  // 輸出讀取的數據
    for (int val : arr) {
        cout << val << " ";  // 輸出每個元素
    }
    cout << endl;

    MaxHeap maxHeap;            // 創建Max Heap對象
    maxHeap.buildMaxHeap(arr);  // 建立Max Heap

    // 輸出Max Heap的內容
    cout << "Max Heap(By BFS): ";
    maxHeap.printHeap();
    cout << endl;

    // 等待用戶輸入以結束（跨平台）
    cout << "pause";
    cin.get();
    return 0;
}
