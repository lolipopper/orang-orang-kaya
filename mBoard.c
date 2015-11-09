#include "petakBoard.h"

int main()
{
    ListBoard LB;
    TabKota TK;

    CreateList(&LB);
    initBoard(&LB,&TK);
    PrintInfoBoard(LB,TK);
    PrintInfoKota(TK,2);
    return 0;
}
