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

void ConsPlayer(Player *P, int position, long long money, int nFreeTax, int nFreePrison, int nOffLight, int nProtect, char playerId, int kekayaan, boolean jail, int movworldtravel)
{
	(*P).position = position;
	(*P).money = money;
	(*P).nFreeTax = nFreeTax;
	(*P).nFreePrison = nFreePrison;
	(*P).nOffLight = nOffLight;
	(*P).nProtect = nProtect;
	(*P).playerId = playerId;
	(*P).kekayaan = kekayaan;
	(*P).jail = jail;
	(*P).movWorldTravel = movworldtravel;
}

void InitPlayer(Player *P, char playerId)
{
	ConsPlayer(P,1,2000,0,0,0,0,playerId,0,false, 0);
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
	jumlahPemain = n;
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
}

void DeleteAllPlayer ()
{
    AddressPl p,prec;
    p = First(Turn);
    if(First(Turn) != Nil){
        p = Next(First(Turn));
        prec = First(Turn);
        while (p!= First(Turn))
        {
            DealokasiPl(&prec);
            prec = p;
            p = Next(p);
        }
        DealokasiPl(&prec);
        First(Turn) = Nil;
    }
}

void InitNumPlayer(int n)
{
	AddressPl Prec, P;
	Player Pl;

	InitPlayer(&Pl, 'A');
	Prec = AlokasiPl(Pl);
	InitPlayer(&Pl, 'B');
	P = AlokasiPl(Pl);
	First(Turn) = Prec;
	Next(Prec) = P;

	jumlahPemain = n;
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

void deletePlayer(ListPlayer *L,Player P)
{
    boolean found=false;
    AddressPl temp=Next(First(*L));
    AddressPl prev=First(*L);

    while(!found)
    {
        if (PlayerId(temp)==P.playerId)
        {
            found=true;
        }
        else
        {
            prev=temp;
            temp = Next(temp);
        }
    }

    if (temp==First(*L))
    {
        First(*L) = Next(temp);
    }
    Next(prev) = Next(temp);
    DealokasiPl(&temp);
}
