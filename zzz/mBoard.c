#include "petakBoard.h"

int main()
{
    int length;
    ListBoard LB;
    TabKota TK;

    CreateList(&LB);
    initBoard(&LB,&TK);
    PrintInfoBoard(LB,TK);
    //PrintInfoKota(TK,2);
    //PrintNamaPetak(TK, Next(Next(Next(First(LB)))), 1, &length);
    //printf("Length : %d\n", length);
    //ShowBoard(LB, TK);
    printf("Save\n");
    Save(LB,TK);
    printf("Load\n");
    Load(&LB,&TK);
    PrintInfoBoard(LB,TK);
    return 0;
}
