#include <algorithm>  //用於max函式，找出最大值
#include <climits>    //用於INT_MIN
#include <iostream>
#include <queue>
#include <vector>  //動態陣列
using namespace std;

class TreeNode {
   public:
    int value;
    TreeNode* left;   // 儲存左子
    TreeNode* right;  // 儲存右子

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}  // 初始化
};

class BinaryTree {
   public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(vector<int>& arr) {  // 建立樹
        if (arr.empty()) return nullptr;     // 如果是空的，回傳

        queue<TreeNode*> q;  // 初始化queue和root
        root = new TreeNode(arr[0]);
        q.push(root);

        size_t i = 1;                           // 紀錄處理的數字
        while (!q.empty() && i < arr.size()) {  // 建立樹的節點
            TreeNode* current = q.front();      // 取出目前的節點
            q.pop();

            if (i < arr.size()) {                        // 如果還有值，建立左子
                current->left = new TreeNode(arr[i++]);  // 建立一個新的左節點，值為arr[i]
                q.push(current->left);                   // 放入queue
            }

            if (i < arr.size()) {                         // 建立右子節點
                current->right = new TreeNode(arr[i++]);  // 建立一個新的右節點，值為arr[i]
                q.push(current->right);                   // 放入queue
            }
        }

        return root;  // 回傳樹
    }

    void inorderTraversal(TreeNode* node) {  // 中序遍歷
        if (!node) return;                   // 如果節點為空，回傳
        inorderTraversal(node->left);        // 往左邊遞迴直到底
        cout << node->value << " ";          // 印出節點的值
        inorderTraversal(node->right);       // 處理右子
    }

    void postorderTraversal(TreeNode* node) {  // 後序遍歷
        if (!node) return;                     // 如果節點為空，回傳
        postorderTraversal(node->left);        // 往左邊遞迴直到底
        postorderTraversal(node->right);       // 換處理右子
        cout << node->value << " ";            // 印出節點的值
    }

    // 找出子樹的最大值
    int findMax(TreeNode* node) {
        if (!node) return INT_MIN;                                             // 如果沒有數字，回傳
        return max({node->value, findMax(node->left), findMax(node->right)});  // 找出左右節點的最大值
    }

    int leftMax() {  // 回傳左子的最大值
        return findMax(root->left);
    }

    int rightMax() {  // 回傳找出右子的最大值
        return findMax(root->right);
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};  // 建立樹的值
    tree.buildTree(arr);

    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);  // 中序遍歷
    cout << "\nPostorder Traversal: ";
    tree.postorderTraversal(tree.root);  // 後序遍歷

    cout << "\n最大左子樹數值: " << tree.leftMax();
    cout << "\n最大右子樹數值: " << tree.rightMax();
    cout << endl;

    return 0;
}
