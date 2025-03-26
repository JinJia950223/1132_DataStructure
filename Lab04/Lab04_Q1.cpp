
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

class Card {  // 類別代表單張撲克牌，分花色跟數值
   public:
    string colors;                                    // 儲存花色
    string rank;                                      // 儲存數值
    Card(string s, string r) : colors(s), rank(r) {}  // 初始化花色和數值
    void display() const {
        cout << rank << " of " << colors << endl;
    }
};

class Stack {  // 模擬堆疊結構，儲存洗過的牌
   private:
    vector<Card> stack;

   public:
    void push(const Card& card) {  // 將卡牌放入stack的頂端
        stack.push_back(card);
    }

    Card pop() {              // 取出stack頂端的卡片
        if (stack.empty()) {  // 檢查stack中有沒有卡牌
            cout << "Stack is empty!" << endl;
        }
        Card topCard = stack.back();  // 取出stack頂端的卡片
        stack.pop_back();             // 移除vector中最上方卡牌
        return topCard;               // 回傳頂端的卡牌
    }

    bool isEmpty() const {     // 檢查stack中是否為空
        return stack.empty();  // 回傳為空
    }
};

class Deck {
   private:
    vector<Card> cards;
    Stack shuffledDeck;

   public:
    Deck() {
        string colors[] = {"Hearts", "Diamonds", "Clubs", "Spades"};                          // 定義撲克牌的花色
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};  // 定義撲克牌的數值

        for (int i = 0; i < 4; i++) {  // 將52張卡牌存入cards
            for (int j = 0; j < 13; j++) {
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }

    void shuffleDeck() {                             // 洗牌
        srand(time(0));                              // 隨機生成
        random_shuffle(cards.begin(), cards.end());  // 洗牌
        for (int i = 0; i < 52; i++) {               // 將洗完的排放入stack中
            shuffledDeck.push(cards[i]);
        }
    }

    void drawAllCards() {              // 發牌
        if (shuffledDeck.isEmpty()) {  // 檢查stack是否有牌
            cout << "No cards" << endl;
            return;
        } else {  // 持續發牌直到發完stack中的52張牌
            while (!shuffledDeck.isEmpty()) {
                Card drawnCard = shuffledDeck.pop();
                drawnCard.display();
            }
        }
    }
};

int main() {
    Deck deck;
    deck.shuffleDeck();  // 洗牌
    cout << "Shuffled deck:" << endl;
    deck.drawAllCards();  // 顯示洗完的牌
    return 0;
}
