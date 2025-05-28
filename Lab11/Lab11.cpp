#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Record {
   public:
    string product;  // 儲存產品名稱
    int ValidDate;   // 儲存有效日期
    int hot;         // 儲存暢銷度

    Record(string product, int ValidDate, int hot)  // 初始化
        : product(product), ValidDate(ValidDate), hot(hot) {}
};

class ConvenientStore {
   private:
    vector<Record> records;

   public:
    // 讀取檔案，將檔案內容依數量，名稱、有效日期、暢銷度依序讀取。
    // 因為泡麵中間有空格，因此做偵錯處理，讀取前面子串作為產品名稱，最後兩個數字為有效日期及暢銷度。
    void fileRead(ifstream& infile) {
        if (!infile.is_open()) {  // 偵錯，若檔案無法開啟，回傳。
            cout << "Can't open file " << endl;
            return;
        }
        int num;                         // 儲存產品數量
        infile >> num;                   // 先讀取產品數量
        for (int i = 0; i < num; i++) {  // 依序讀取產品名稱、有效日期、暢銷度
            string line;
            getline(infile, line);
            if (line.empty()) {
                i--;
                continue;
            }  // 跳過空行
            istringstream iss(line);
            vector<string> tokens;
            string token;
            // 先全部分割
            while (iss >> token) tokens.push_back(token);
            if (tokens.size() < 3) continue;
            // 熱銷程度和有效期限在最後兩個
            int hot = stoi(tokens.back());
            tokens.pop_back();
            int ValidDate = stoi(tokens.back());
            tokens.pop_back();
            // 剩下的合起來就是商品名稱
            string product = tokens[0];
            for (size_t j = 1; j < tokens.size(); ++j) {
                product += " " + tokens[j];
            }
            records.emplace_back(product, ValidDate, hot);
        }
    }
    // 產品排序，有效日期較少排前面，若有效日期跟暢銷度相同依暢銷度排列。
    void sortRecords() {
        sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
            if (a.ValidDate != b.ValidDate)
                return a.ValidDate < b.ValidDate;
            return a.hot > b.hot;
        });
    }
    // 輸出排序
    void printRecords() {
        cout << "Products sort: " << endl;
        for (const auto& rec : records) {
            cout << rec.product << endl;
        }
    }
};

int main() {
    ifstream file("input3.txt");
    if (!file.is_open()) {
        cout << "can't open!" << endl;
        return 1;
    }

    ConvenientStore store;
    store.fileRead(file);
    store.sortRecords();
    store.printRecords();

    file.close();
    return 0;
}
