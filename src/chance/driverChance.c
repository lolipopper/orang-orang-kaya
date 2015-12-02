#include "chance.h"
#include "../board/board.h"

int main()
{
    ListBoard LB;
    TabKota TK;
    Kata K;
    int i, length;
    char dum;
    SKata input;

    printf("-------------------------------------------------\n");
    printf("---------------DRIVER MODUL CHANCE---------------\n");
    printf("-------------------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("--Pengecekan makeChance dan printCard\n");
    printCard(C); printf("  deck sebelum dilakukan makeChance.\n");
    makeChance(&C);
    printCard(C); printf("  deck setelah dilakukan makeChance.\n");
    printf("\n");
    printf("-------------------------------------------------\n\n");

    printf("Masukkan jumlah pemain = 2\n");
    InitNPlayer();

    printf("-------------------------------------------------\n");
    printf("--Pengecekan randomCard dan boardChance\n");
    printf("  Jika random mendapatkan kartu Go to Jail maka driver ini harus dijalankan ulang.\n");
    initBoard(&LB,&TK);
    printf("  Masukkan dadu1 = 6 dan dadu2 = 6\n");
    MovPlayer(&TK, &LB);
    printf("-------------------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("--Pengecekan off\n");
    printf("  Player mendapatkan kartu Off Light secara otomatis.\n");
    CardOff(PTurn) += 1;
    printf("  Masukkan dadu1 = 1 dan dadu2 = 0\n");
    MovPlayer(&TK, &LB);
    EndTurn();
    printf("  Masukkan dadu1 = 3 dan dadu2 = 4\n");
    MovPlayer(&TK, &LB);
    buy(&TK, &LB);
    EndTurn();
    printf("  Ketik off Seoul.\n");
    printf("> ");
    scanf("%s", input);
    if (strcmp(input, "off") == 0) {
        scanf("%c",&dum);
        gets(input);
        length = 0; i = 0;
        while (input[i] != '\0') {
            K.TabKata[i] = input[i];
            length++;
            i++;
        }
        K.Length = length;
        off(K, &TK, &C);
    }
    ShowBoard(LB, TK);
    printf("  Masukkan dadu1 = 2 dan dadu2 = 4\n");
    MovPlayer(&TK, &LB);
    EndTurn();
    printf("-------------------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("--Pengecekan protect\n");
    printf("  Player mendapatkan kartu Off Light secara otomatis.\n");
    CardProtect(PTurn) += 1;
    printf("  Ketik protect Seoul.\n");
    printf("> ");
    scanf("%s", input);
    if (strcmp(input, "protect") == 0) {
        scanf("%c",&dum);
        gets(input);
        length = 0; i = 0;
        while (input[i] != '\0') {
            K.TabKata[i] = input[i];
            length++;
            i++;
        }
        K.Length = length;
        protect(K, &TK, &C);
    }
    ShowBoard(LB, TK);
    printf("-------------------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("--Pengecekan boardBonus\n");
    printf("  Masukkan dadu1 = 27 dan dadu2 = 0\n");
    MovPlayer(&TK, &LB);
    EndTurn();
    printf("-------------------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("--Pengecekan boardTax\n");
    printf("  Masukkan dadu1 = 11 dan dadu2 = 0\n");
    MovPlayer(&TK, &LB);
    EndTurn();
    printf("-------------------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("--Pengecekan boardDesertedIsland\n");
    printf("  Masukkan dadu1 = 6 dan dadu2 = 0\n");
    MovPlayer(&TK, &LB);
    printf("-------------------------------------------------\n\n");

    printf("--Pengecekan selesai.\n");

    return 0;
}
