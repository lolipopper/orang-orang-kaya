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

    printf("-----------------------------------------------\n");
    printf("---------------LET'S GET WEALTHY---------------\n");
    printf("-----------------------------------------------\n");
    printf("Ketik new untuk memulai permainan.\n");
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "new") == 0) {
            InitNPlayer();
        }
        if (strcmp(input, "roll") == 0) {
            scanf("%s", input);
            if (strcmp(input, "dice") == 0) {
                MovPlayer(*TK, *LB);
            }
        }
        if (strcmp(input, "buy") == 0) {
            buy();
        }
        if (strcmp(input, "info") == 0) {
            scanf("%s", input);
            if (strcmp(input, "card") == 0) {
                printCard(C);
            }
        }
        if (strcmp(input, "end") == 0) {
            scanf("%s", input);
            if (strcmp(input, "dice") == 0) {
                EndTurn();
            }
        }
        if (strcmp(input, "board") == 0) {
            ShowBoard(*LB, *TK);
            printf("\n");
        }
    } while (strcmp(input, "exit") != 0);
}
