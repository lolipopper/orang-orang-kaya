#include "petakBoard.h"
#include "petakBoard.c"

int main()
{
    int length;
    ListBoard LB;
    TabKota TK;

    CreateList(&LB);
    initBoard(&LB,&TK);
    //PrintInfoBoard(LB,TK);
    //PrintInfoKota(TK,2);
    PrintNamaPetak(TK, Next(Next(Next(First(LB)))), 1, &length);
    printf("Length : %d\n", length);
    ShowBoard(LB, TK);
    return 0;
}
