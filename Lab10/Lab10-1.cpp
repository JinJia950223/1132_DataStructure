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

    int getTreeHeight(TreeNode* node) {                                         // 利用遞迴計算樹的高度
        if (node == nullptr) return 0;                                          // 如果樹為空，回傳
        return 1 + max(getTreeHeight(node->left), getTreeHeight(node->right));  // 逐步計算樹高
    }

    int getLevelSum(TreeNode* node, int level) {  // 遞迴計算某層的節點總和
        if (node == nullptr) return 0;            // 如果為空則回傳
        if (level == 0) return node->value;
        return getLevelSum(node->left, level - 1) + getLevelSum(node->right, level - 1);  // 計算層總和
    }

    void LevelSum() {  // 輸入要計算的層數，顯示總和
        int level;
        cout << "請輸入要查詢的層數(從0開始): ";
        cin >> level;
        int height = getTreeHeight(root);
        if (level >= height) {
            cout << "超過樹高" << endl;
        } else {
            int levelSum = getLevelSum(root, level);
            cout << "第" << level << "層的總和為: " << levelSum << endl;
        }
    }

    void Breadth_first_search(TreeNode* root) {  // 廣度優先遍歷
        if (root == nullptr) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();              // 紀錄節點數量
            for (int i = 0; i < levelSize; i++) {  // 遍歷當層的所有節點
                TreeNode* current = q.front();
                q.pop();
                cout << current->value << " ";
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
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

    tree.LevelSum();
    system("pause");
    return 0;
}
