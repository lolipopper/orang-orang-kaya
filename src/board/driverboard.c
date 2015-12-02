#include "board.h"
//#include "player.h"

int main()
{
    TabKota TK;
    ListBoard LB;
    Address P;
    Kata K,KNgasal;

    K.TabKata[0] = 'J';
    K.TabKata[1] = 'a';
    K.TabKata[2] = 'k';
    K.TabKata[3] = 'a';
    K.TabKata[4] = 'r';
    K.TabKata[5] = 't';
    K.TabKata[6] = 'a';
    K.Length = 7;

    KNgasal.TabKata[0] = 'N';
    KNgasal.TabKata[1] = 'g';
    KNgasal.TabKata[2] = 'a';
    KNgasal.TabKata[3] = 's';
    KNgasal.TabKata[4] = 'a';
    KNgasal.TabKata[5] = 'l';
    KNgasal.Length = 6;

    printf("CEK INIT BOARD\n");
    initBoard(&LB,&TK);
    P = Next(First(LB));
    InitNumPlayer(3);
    printf("INIT BOARD DONE\n\nCEK SHOWBOARD\n");
    ShowBoard(LB,TK);
    printf("\nCEK PRINTINFOKOTA\n");
    PrintInfoKota(TK,2);
    printf("\nCEK PRINTINFOBOARD\n");
    PrintInfoBoard(LB,TK);
    printf("\nCEK SEARCHKOTA\n");
    printf("SearchKota(Jakarta,TK) = %d\n",SearchKota(K,TK));
    printf("SearchKota(Ngasal,TK) = %d\n",SearchKota(KNgasal,TK));

    return 0;
}
