#include "string.h"
#include "boolean.h"
#include "kota.h"
#include "command.h"
#include "board.h"
#include "player.h"
#include "other.h"
#include "save.h"
#include "chance.h"

void menu();
void pesanKesalahan();

int main ()
{
    ListBoard LB;
    TabKota TK;

    makeChance(&C);
    initBoard(&LB,&TK);
    menu(&LB,&TK);

    return 0;
}

void menu(ListBoard *LB, TabKota *TK)
{
    char input[100];
    Kata K;
    int i, length;
    boolean inputBenar;

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
            inputBenar = true;
        }
        else if (strcmp(input, "load") == 0){
            scanf("%s", input);
            printf("Mulai Load\n");
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
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "roll") == 0) { // roll dice
            scanf("%s", input);
            if (strcmp(input, "dice") == 0) {
                MovPlayer(TK, LB);
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "info") == 0) { // info kota
            scanf("%s", input);
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
            scanf("%s", input);
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
                printCard(C);
            }
            else if (strcmp(input, "kekayaan") == 0) {
                printKekayaan();
            }
            else {
                pesanKesalahan();
            }
        }
        else if (strcmp(input, "protect") == 0) { // print card
            scanf("%s", input);
            length = 0; i = 0;
            while (input[i] != '\0') {
                K.TabKata[i] = input[i];
                length++;
                i++;
            }
            K.Length = length;
            protect(K, TK, &C);
        }
        else if (strcmp(input, "off") == 0) { // print card
            scanf("%s", input);
            length = 0; i = 0;
            while (input[i] != '\0') {
                K.TabKata[i] = input[i];
                length++;
                i++;
            }
            K.Length = length;
            off(K, TK, &C);
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
            scanf("%s", input);
            if (strcmp(input, "bank") == 0){
                scanf("%s", input);
                length = 0; i = 0;
                while (input[i] != '\0') {
                    K.TabKata[i] = input[i];
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
        else if (strcmp(input, "save") == 0){
            scanf("%s", input);
            Save(*LB,*TK,input);
        }
        else if (strcmp(input, "load") == 0){
            scanf("%s", input);
            printf("Mulai Load\n");
            Load(LB,TK,input);
        }
        else if (strcmp(input, "exit") == 0)
        {
            printf("Thanks for playing\n");
        }
        else
        {
            pesanKesalahan();
        }
    } while (strcmp(input, "exit") != 0);
}

void pesanKesalahan()
{
    printf("  Input salah.\n\n");
}
