#include <string.h>
#include "boolean.h"
#include "kota.h"
#include "command.h"
#include "board.h"
#include "player.h"
#include "other.h"
#include "chance.h"

void menu();
void pesanKesalahan();

int main ()
{
    ListBoard LB;
    TabKota TK;

    makeChance(&C);
    initBoard(&LB,&TK);
    menu(&LB,&TK,&C);

    return 0;
}

void menu(ListBoard *LB, TabKota *TK, card *C)
{
    boolean Win;
    SKata input;
    Kata K;
    int i, length;
    boolean inputBenar;
    char dum;

    printf("-----------------------------------------------\n");
    printf("---------------LET'S GET WEALTHY---------------\n");
    printf("-----------------------------------------------\n");
    printf("Ketik new untuk memulai permainan baru.\n");
    printf("Ketik load untuk memulai dari file save.\n");
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "new") == 0) { // new
            InitNPlayer();
            help();
            inputBenar = true;
            turnAwal = true;
        }
        else if (strcmp(input, "load") == 0){
            scanf("%s", input);
            printf("Loading...\n");
            boolean valid;
            valid = Load(LB,TK,input);
            if (valid)
                inputBenar = true;
            else
                inputBenar = false;
        }else{
            pesanKesalahan();
            inputBenar = false;
        }
    } while (!inputBenar);

    do {
        if (Jail(PTurn) && turnAwal) {
            printf("  Kamu sedang berada di penjara.\n");
            printf("  Kamu bisa keluar dengan menggunakan kartu Free Prison atau membayar 100K\n");
            printf("  Ketik 'free me' untuk menggunakan kartu Free Prison, 'pay' untuk membayar\n\n");
            rolled = true;
            turnAwal = false;
        }
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "roll") == 0) { // roll dice
            scanf("%s", input);
            if (strcmp(input, "dice") == 0) {
                buyupgrade = false;
                MovPlayer(TK, LB);
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "info") == 0) { // info kota
            scanf("%c",&dum);
            gets(input);
            length = 0; i = 0;
            while (input[i] != '\0') {
                K.TabKata[i] = input[i];
                length++;
                i++;
            }
            K.Length = length;
            infoCity(K, *TK);
        }
        else if (strcmp(input, "leaderboard") == 0) { // leaderboard
            showLeaderBoard();
        }
        else if (strcmp(input, "buy") == 0) { // buy
            buy(TK, LB);
        }
        else if (strcmp(input, "buyoffered") == 0) {
            scanf("%c",&dum);
            gets(input);
            length = 0; i = 0;
            while (input[i] != '\0') {
                K.TabKata[i] = input[i];
                length++;
                i++;
            }
            K.Length = length;
            buyoffered(K, TK);
        }
        else if (strcmp(input, "upgrade") == 0) { // upgrade
            upgrade(TK,LB);
        }
        else if (strcmp(input, "print") == 0) { // print card
            scanf("%s", input);
            if (strcmp(input, "card") == 0) {
                printCard(*C);
            }
            else if (strcmp(input, "kekayaan") == 0) {
                printKekayaan();
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "protect") == 0) { //protect
            scanf("%c",&dum);
            gets(input);
            length = 0; i = 0;
            while (input[i] != '\0') {
                K.TabKata[i] = input[i];
                length++;
                i++;
            }
            K.Length = length;
            protect(K, TK, C);
        }
        else if (strcmp(input, "off") == 0) { // off
            scanf("%c",&dum);
            gets(input);
            length = 0; i = 0;
            while (input[i] != '\0') {
                K.TabKata[i] = input[i];
                length++;
                i++;
            }
            K.Length = length;
            off(K, TK, C);
        }
        else if (strcmp(input, "show") == 0) { // show money
            scanf("%s", input);
            if (strcmp(input, "money") == 0) {
                ShowMoney();
            }
            else if (strcmp(input,"offered") == 0){
                showOffered(*TK);
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "end") == 0) { // end turn
            scanf("%s", input);
            if (strcmp(input, "turn") == 0) {
                EndTurn();
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "board") == 0) { // board
            ShowBoard(*LB, *TK);
            printf("\n");
        }
        else if (strcmp(input, "sell") == 0){
            SKata input2;
            scanf("%c",&dum);
            gets(input);
            length = 0; i = 0;
            memcpy(input2,&input,4);
            input2[4] = '\0';
            if (strcmp(input2, "bank") == 0){
                length = 0; i = 5;
                while (input[i] != '\0') {
                    K.TabKata[i-5] = input[i];
                    length++;
                    i++;
                }
                K.Length = length;
                sellbank(K,TK);
            }else{
                length = 0; i = 0;
                while (input[i] != '\0') {
                    K.TabKata[i] = input[i];
                    length++;
                    i++;
                }
                K.Length = length;
                sell(K,TK);
            }
        }
        else if (strcmp(input, "save") == 0){ // save
            scanf("%s", input);
            Save(*LB,*TK,input);
        }
        else if (strcmp(input, "load") == 0){ // load
            scanf("%s", input);
            printf("Loading...\n");
            Load(LB,TK,input);
        }
        else if (strcmp(input, "pay") == 0){ // kasus khusus di penjara
            if (Jail(PTurn)) {
                if (Money(PTurn) < 100) {
                    printf("  Uangmu tidak cukup.\n\n");
                }
                else {
                    Money(PTurn) -= 100;
                    printf("  Kamu bebas dari penjara.\n");
                    ShowMoney();
                    Jail(PTurn) = false;
                    rolled = true;
                    printf("\n");
                }
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "free") == 0) {
            scanf("%s", input);
            if (strcmp(input, "me") == 0) {
                if (Jail(PTurn)) {
                    if (CardFreePrison(PTurn) == 0) {
                        printf("  Kamu tidak memiliki kartu Free Prison.\n\n");
                    }
                    else {
                        CardFreePrison(PTurn) -= 1;
                        printf("  Kamu bebas dari penjara.\n\n");
                        Jail(PTurn) = false;
                        (*C).el[1] += 1;
                        rolled = true;
                    }
                }
                else {
                    pesanKesalahan();
                }
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "help") == 0) {
            help();
        }
        else {
            pesanKesalahan();
        }

        //CEK TOUR MONOPOLI
        Win = isWinTour(*TK);
        Win = isWinBlock(*TK);
    } while ((strcmp(input, "exit") != 0) && (Win == false));
}

void pesanKesalahan()
{
    printf("  Input salah.\n\n");
}
