#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    string name;
    int score;
};

int drawCard() {
    return rand() % 10 + 1; // 發牌功能，隨機生成 1-10 之間的數字
}

// 初始化玩家
void initializePlayer(Player* player, string name) {
    player->name = name;
    int card1 = drawCard();
    int card2 = drawCard();
    player->score = card1 + card2;
    
    // 如果兩張牌總和是 10，且有 A，則 A 當作 11
    if ((card1 == 1 || card2 == 1) && player->score == 10) {
        player->score = 11 + (card1 == 1 ? card2 : card1);
    }
    
    cout << name << " 初始手牌總點數: " << player->score << endl;
}

// 顯示玩家分數
void displayScore(Player* player) {
    cout << player->name << " 當前總分: " << player->score << endl;
}

// 玩家回合
void playerTurn(Player* player) {
    char choice;
    while (player->score < 21) { // 當玩家總分少於21點可持續選擇是否抽牌 
        cout << "要抽牌嗎？(h = 抽, s = 停) : ";
        cin >> choice;
        if (choice == 'h') {
            int newCard = drawCard(); // 抽新牌
            player->score += newCard; // 加到玩家手牌
            cout << player->name << " 抽到了 " << newCard << " 點，目前總分: " << player->score << endl; // 顯示卡牌分數 
            if (player->score > 21) { // 如果分數大於21顯示爆掉 
                cout << player->name << " 爆掉了！遊戲結束。\n";
                return;
            }
        }
        else if (choice == 's') { // 不要抽牌則退出 
            break;
        }
    }
}

// 莊家回合
void dealerTurn(Player* dealer) { 
    while (dealer->score < 17) { // 若是莊家回合則持續抽牌，直到21點爆掉 
        int newCard = drawCard(); // 抽新牌
        dealer->score += newCard; // 加到莊家分數 
        cout << "莊家抽到 " << newCard << " 點，目前總分: " << dealer->score << endl;
        if (dealer->score > 21) { // 如果莊家分數超過21點顯示爆掉 
            cout << "莊家爆了！玩家獲勝！" << endl;
            return;
        }
    }
}

// 判斷勝負
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21) { // 如果分數大於21顯示爆掉 
        cout << "你爆了！莊家獲勝！\n";
    }
    else if (dealer->score > 21 || player->score > dealer->score) { // 如果莊家爆掉或莊家分數小於玩家則顯示贏了 
        cout << "你贏了！！\n";
    }
    else if (player->score == dealer->score) { // 莊家玩家分數相等則顯示平手 
        cout << "平手！\n";
    }
    else {
        cout << "莊家贏了！\n";
    }
}

// 主程式
int main() {
    srand(time(0)); // 隨機產生抽卡數值 

    Player player, dealer;
    initializePlayer(&player, "玩家"); // 初始化莊家、玩家 
    initializePlayer(&dealer, "莊家");

    displayScore(&player);
    playerTurn(&player);

    if (player.score <= 21) { 
        cout << "\n莊家回合...\n";
        displayScore(&dealer);
        dealerTurn(&dealer);
        determineWinner(&player, &dealer);
    }

    return 0;
}
