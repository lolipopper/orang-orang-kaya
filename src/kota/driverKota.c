#include "../board/board.h"
#include "../chance/chance.h"

#include <string.h>
#include "../command/command.h"

void menu();
void pesanKesalahan();

int main ()
{
    ListBoard LB;
    TabKota TK;

    printf("-------------------------------------------------\n");
    printf("---------------DRIVER MODUL CHANCE---------------\n");
    printf("-------------------------------------------------\n\n");
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

    InitNPlayer();
    printf("Untuk melihat info kota, ketik info <nama kota>\n");
    scanf("%s", input);
    if (strcmp(input, "info") == 0) { // info kota
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
    printf("KONDISI AWAL BOARD.\n");
    ShowBoard(*LB,*TK);
    MovPlayer(TK, LB);
    buy(TK, LB);
    printf("KONDISI BOARD SETELAH PLAYER A MEMILIK 1 KOTA.\n");
    ShowBoard(*LB,*TK);
    DeleteAllOwnedBuildings(TK, Info(PTurn));
    printf("KONDISI BOARD SETELAH SEMUA KEPEMILIKAN PLAYER A DIHAPUS DENGAN FUNGSI.\n");
    ShowBoard(*LB,*TK);
    printf("PENGECEKAN DRIVER KOTA SELESAI.\n");
}
