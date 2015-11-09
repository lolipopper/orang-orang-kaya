#include "player.h"

void ConsPlayer(Player *P,int position,long long money, int nFreeTax, int nFreePrison,int nOffLight,int nProtect,char playerId,int kekayaan);
{
	Position(*P)=position;
	Money(*P)=money;
	CardFreeTax(*P)=nFreeTax;
	CardFreePrison(*P)=nFreePrison;
	CardOff(*P)=nOffLight;
	CardProtect(*P)=nProtect;
	PlayerId(*P)=playerId;
	Kekayaan(*P)=kekayaan;
}

//Initialize
void InitPlayer(Player *P,char playerId);
{
	ConsPlayer(P,0,0,0,0,0,0,playerId,0);
}