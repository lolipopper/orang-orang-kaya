#include "player.h"

AddressPl AlokasiPl (Player Pl)
{
    AddressPl P;
    P = (AddressPl) malloc (sizeof(ElmtListPl));
    if (P == Nil){
        return Nil;
    }
    else {
        Info(P) = Pl;
        Next(P) = Nil;
        return P;
    }
}

void DealokasiPl (AddressPl *P)
{
    free(*P);
}

void ConsPlayer(Player *P, int position, long long money, int nFreeTax, int nFreePrison, int nOffLight, int nProtect, char playerId, int kekayaan)
{
	(*P).position = position;
	(*P).money = money;
	(*P).nFreeTax = nFreeTax;
	(*P).nFreePrison = nFreePrison;
	(*P).nOffLight = nOffLight;
	(*P).nProtect = nProtect;
	(*P).playerId = playerId;
	(*P).kekayaan = kekayaan;
}

void InitPlayer(Player *P, char playerId)
{
	ConsPlayer(P,1,1000,0,0,0,0,playerId,0);
}

void InitNPlayer()
{
	AddressPl Prec, P;
	Player Pl;
	int n;

	InitPlayer(&Pl, 'A');
	Prec = AlokasiPl(Pl);
	InitPlayer(&Pl, 'B');
	P = AlokasiPl(Pl);
	First(Turn) = Prec;
	Next(Prec) = P;

	printf("  Input banyak pemain (2 - 4) : ");
	scanf("%d", &n);
	printf("\n");
	if (n > 2)
	{
		Prec = Next(Prec);
		InitPlayer(&Pl, 'C');
		P = AlokasiPl(Pl);
		Next(Prec) = P;
		if (n > 3)
		{
			Prec = Next(Prec);
			InitPlayer(&Pl, 'D');
			P = AlokasiPl(Pl);
			Next(Prec) = P;
		}
	}
	Next(P) = First(Turn);
	PTurn = First(Turn);
	rolled = false;
	rolled = false;
}

AddressPl SearchPl (char id)
{
	AddressPl P;
	boolean found;

	P = First(Turn);
	do {
        found = (PlayerId(P) == id);
        if (!found) {
            P = Next(P);
        }
    } while ((P != First(Turn)) && (!found));
	if (found) {
		return P;
	}
	else {
		return Nil;
	}
}
