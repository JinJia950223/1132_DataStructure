#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
   private:
    Node* top;

   public:
    Stack() { top = nullptr; }

    void push(char ch) {             // 儲存符號，將符號放入堆疊最上方
        Node* newNode = new Node();  // 建立新的節點儲存新資料
        newNode->data = ch;          // 把字元儲存到節點中
        newNode->next = top;         // 更新，新的指標指向原來的頂端
        top = newNode;               // 重新指向頂端
    }

    char pop() {               // 移除堆疊頂端的符號
        if (top == nullptr) {  // 如果堆疊為空，回傳
            cout << "堆疊為空，無法取出元素。\n";
            return '\0';
        }
        char poppedValue = top->data;  // 取得頂端的資料
        Node* temp = top;              // TEMP儲存元的節點
        top = top->next;               // 更新頂端
        delete temp;                   // 刪除頂端的節點
        return poppedValue;            // 回傳
    }

    char peek() {              // 輸出堆疊最頂端的符號
        if (top == nullptr) {  // 如果堆疊為空，回傳
            return '\0';
        }
        return top->data;  // 回傳頂端的符號
    }

    bool isEmpty() {  // 判斷堆疊是否為空
        return (top == nullptr);
    }
};

int precedence(char op) {  // 做運算符號的先後順序比較，先乘除後加減
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void InfixToPostfix(const char* infix, char* postfix) {  // 中序表達式轉換成後續表達式
    Stack s;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; ++i) {
        char ch = infix[i];

        if (isalnum(ch)) {       // 如果陣列中是數字直接輸出
            postfix[j++] = ch;   // 運算元直接輸出
        } else if (ch == '(') {  // 遇到左括號放入堆疊
            s.push(ch);
        } else if (ch == ')') {  // 如果遇到右括號持續輸出運算符號直到遇到左括號
            while (!s.isEmpty() && s.peek() != '(') {
                postfix[j++] = s.pop();
            }
            s.pop();  // 不輸出括號
        } else {      // 先乘除後加減
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix[j++] = s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {  // 最後將堆疊內剩下的符號輸出
        postfix[j++] = s.pop();
    }

    postfix[j] = '\0';  // 結束字串
}

int main() {
    char infix[100], postfix[100];
    cout << "請輸入中序表達式（例如 A+B*C）: ";
    cin >> infix;

    InfixToPostfix(infix, postfix);
    cout << "轉換後的後序表達式為: " << postfix << endl;

    return 0;
}
