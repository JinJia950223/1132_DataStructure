#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int EMPTY = -1;  // 用 -1 代表沒有節點

class TreeNode {
   public:
    int value;        // 儲存節點的數值
    TreeNode* left;   // 左節子指標
    TreeNode* right;  // 右節子指標
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
   public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}  // 初始化

    TreeNode* buildTree(const vector<int>& arr) {            // 從設定的陣列中建構二元樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;  // 檢查貞烈是否為空
                                                             // 初始化並使用queue建立節子點，依序從arr中拿出數值建立左右子樹
        queue<TreeNode**> q;
        root = new TreeNode(arr[0]);
        q.push(&root);

        size_t i = 1;
        while (!q.empty() && i < arr.size()) {  // 建構節子點
            TreeNode** nodePtr = q.front();
            q.pop();

            if (i < arr.size() && arr[i] != EMPTY) {  // 建立左子節點
                (*nodePtr)->left = new TreeNode(arr[i]);
                q.push(&((*nodePtr)->left));
            }
            i++;

            if (i < arr.size() && arr[i] != EMPTY) {  // 建立右子節點
                (*nodePtr)->right = new TreeNode(arr[i]);
                q.push(&((*nodePtr)->right));
            }
            i++;
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) {  // 深度遍歷，使用前序遍歷
        if (node == nullptr) return;           // 如果節點為空則回傳
        cout << node->value << " ";
        Depth_first_search(node->left);   // 遞迴左節子點
        Depth_first_search(node->right);  // 遞迴右節子點
    }

    void Breadth_first_search(TreeNode* root) {  // 廣度優先遍歷
        if (root == nullptr) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {  // 紀錄節點數量
            TreeNode* current = q.front();
            q.pop();
            cout << current->value << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    // 遞迴搜尋指定值的節點
    TreeNode* findNode(TreeNode* node, int val) {
        if (node == nullptr) return nullptr;            // 如果為空則回傳
        if (node->value == val) return node;            // 如果找到目標節點則回傳
        TreeNode* leftRes = findNode(node->left, val);  // 在左子樹中遞迴尋找，若找到則回傳，否則到右子樹找
        if (leftRes != nullptr) return leftRes;
        return findNode(node->right, val);
    }

    // 計算以節點為根的子樹總和
    int subtreeSum(TreeNode* node) {
        if (node == nullptr) return 0;
        return node->value + subtreeSum(node->left) + subtreeSum(node->right);
    }

    // 用戶輸入節點數值，計算左右子樹總和並比較
    void CompareLeftRightSubtreeSum() {
        int target;
        cout << "請輸入欲檢查的節點數值: ";
        cin >> target;
        TreeNode* node = findNode(root, target);  // 找出目標節點
        if (node == nullptr) {
            cout << "未找到該節點!" << endl;
            return;
        }
        int leftSum = subtreeSum(node->left);    // 計算左子節點總和
        int rightSum = subtreeSum(node->right);  // 計算右子節點總和
        cout << "左子樹總和: " << leftSum << endl;
        cout << "右子樹總和: " << rightSum << endl;
        if (leftSum > rightSum) {
            cout << "左子樹總和較大" << endl;
        } else if (leftSum < rightSum) {
            cout << "右子樹總和較大" << endl;
        } else {
            cout << "左右子樹總和相等" << endl;
        }
    }
};

int main() {
    BinaryTree tree;  // 建立樹
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, EMPTY, EMPTY, 10, 11, EMPTY, EMPTY};
    tree.buildTree(arr);

    cout << "DFS Result: ";
    tree.Depth_first_search(tree.root);  // 輸出DFS
    cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);  // 輸出BFS
    cout << endl;

    tree.CompareLeftRightSubtreeSum();

    system("pause");
    return 0;
}
