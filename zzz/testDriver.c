#include "action.h"
#include "chance.h"

int main()
{
    ListBoard LB;
    TabKota TK;
    card Deck;

    CreateList(&LB);
    initBoard(&LB,&TK);
    makeChance(&Deck);
    InitNPlayer();
    PrintInfoBoard(LB,TK);
    MovPlayer(TK, LB);
    EndTurn();
    MovPlayer(TK, LB);
    EndTurn();
    MovPlayer(TK, LB);
    EndTurn();
    MovPlayer(TK, LB);
    EndTurn();
    MovPlayer(TK, LB);
    int i = 25;
    while (i > 0)
    {
		randomCard(&Deck, &PTurn);
		i -= 1;
	}
    PrintPos(TK, LB);
    return 0;
}
