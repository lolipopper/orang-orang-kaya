#include "player.h"

//Constructor
AddressPl AlokasiPl (Player Pl)
/*	Mengirimkan AddressPl hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka AddressPl tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
{
    AddressPl p;
    p = (AddressPl) malloc (sizeof(ElmtListPl));
    if (p == Nil){
        return Nil;
    } else {
        Info(p) = Pl;
        Next(p) = Nil;
        return p;
    }
}

void ConsPlayer(Player *P,int position,long long money, int nFreeTax, int nFreePrison,int nOffLight,int nProtect,char playerId,int kekayaan)
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

void DealokasiPl (AddressPl *P)
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian AddressPl P
*/
{
    free(*P);
}

//Initialize
void InitPlayer(Player *P,char playerId)
{
	ConsPlayer(P,1,1000,0,0,0,0,playerId,0);
}

void InitNPlayer()
{
	//Kamus
	AddressPl Prec, P;
	Player Pl;
	int n;

	//Algoritma
	InitPlayer(&Pl, 'A');
	Prec = AlokasiPl(Pl);
	InitPlayer(&Pl, 'B');
	P = AlokasiPl(Pl);
	First(Turn) = Prec;
	Next(Prec) = P;

	printf("Input banyak pemain (2 - 4) : ");
	scanf("%d", &n);
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

//Search
AddressPl SearchPl(char id)
{
	//Kamus
	AddressPl P;
	boolean found;

	//Algoritma
	P = First(Turn);
	do
		{
			found = (PlayerId(P) == id);
			if (!found)
				P = Next(P);
		}
		while ((P != First(Turn)) && (!found));
	if (found)
		return P;
	else
		return Nil;
	return P;
}
