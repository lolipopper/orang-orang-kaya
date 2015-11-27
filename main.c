#include "string.h"
#include "boolean.h"
#include "kota.h"
#include "command.h"
#include "board.h"
#include "player.h"
#include "other.h"
#include "chance.h"

void menu();

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

    printf("-----------------------------------------------\n");
    printf("---------------LET'S GET WEALTHY---------------\n");
    printf("-----------------------------------------------\n");
    printf("Ketik new untuk memulai permainan.\n");
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "new") == 0) { // new
            InitNPlayer();
        }
        if (strcmp(input, "roll") == 0) { // roll dice
            scanf("%s", input);
            if (strcmp(input, "dice") == 0) {
                MovPlayer(TK, LB);
            }
        }
        if (strcmp(input, "info") == 0) {
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
        if (strcmp(input, "leaderboard") == 0) {
            showLeaderBoard();
        }
        if (strcmp(input, "buy") == 0) { // buy
            buy(TK, LB);
        }
        if (strcmp(input, "upgrade") == 0) {
            upgrade(TK,LB);
        }
        if (strcmp(input, "print") == 0) { // print card
            scanf("%s", input);
            if (strcmp(input, "card") == 0) {
                printCard(C);
            }
        }
        if (strcmp(input, "show") == 0) { // show money
            scanf("%s", input);
            if (strcmp(input, "money") == 0) {
                ShowMoney();
            }
        }
        if (strcmp(input, "end") == 0) { // end turn
            scanf("%s", input);
            if (strcmp(input, "turn") == 0) {
                EndTurn();
            }
        }
        if (strcmp(input, "board") == 0) { // board
            ShowBoard(*LB, *TK);
            printf("\n");
        }
    } while (strcmp(input, "exit") != 0);
}
