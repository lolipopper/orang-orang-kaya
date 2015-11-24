#include "action.h"

void buy(Player *P, Kota *K)
{
	if ((*K).level < 3)
	{
		(*P).money -= (*K).price;
		(*P).kekayaan += (*K).price;
		(*K).owner = (*P).playerId;
		if ((*K).level == 0)
			(*K).level++;
	}
}

void payRent(Player *P,Kota K)
{
	(*P).money -= K.price;
	(*P).kekayaan -= K.price;
	Money(SearchPl(K.owner)) += K.price;
	Kekayaan(SearchPl(K.owner)) += K.price;
}

void Upgrade(ListBoard LB, TabKota *TK)
{
	//Kamus
	Address P;
	int i, upgrade, length;

	//Algoritma
	P = First(LB);
	i = Position(PTurn);
	while (i > 1)
	{
		P = Next(P);
		i -= 1;
	}
	if (Type(P) == 1)
	{
		if (Owner((*TK), Id(P)) == PlayerId(PTurn))
		{
			if (Level((*TK), Id(P)) < 5)
			{
				if (Level((*TK), Id(P)) != 3)
					upgrade = ((Price((*TK), Position(PTurn))) * 7 / 4);
				else
					upgrade = ((Price((*TK), Position(PTurn))) * 3);
				if (Money(PTurn) >= upgrade)
				{
					Money(PTurn) -= upgrade;
					Level((*TK), Position(PTurn)) += 1;
					printf("Selamat! Bangunanmu di ");
					length = (NamaKota((*TK), Position(PTurn)).Length);
					for(i = 0; i < length; i++)
						printf("%c", (*TK).TK[Position(PTurn)].name.TabKata[i]);
					printf(" telah mencapai aras %d\n", Level((*TK), Id(P)));
				}
				else
					printf("Uangmu tidak cukup untuk meningkatkan aras bangunan anda...\n");
				ShowMoney();
			}
			else
				printf("Bangunanmu sudah mencapai aras maksimum dan tidak dapat ditingkatkan lagi.\n");
		}
		else
			printf("Kota ini bukan properti milikmu.\n");
	}
	else
		printf("Petak ini bukan tempat untuk konstruksi bangunan.\n");
}

//Action
void ShowMoney()
{
	printf("Uangmu sekarang : %lld GWD\n\n", Money(PTurn));
}

void MoveNPetak(TabKota TK, ListBoard LB, int N)
{
	//Kamus
	int i, mov;
	Address P;

	//Algoritma
	i = Position(PTurn);
	P = First(LB);
	while (i > 1)
	{
		P = Next(P);
		i -= 1;
	}
	mov = N;
	while (mov > 0)
	{
		Position(PTurn) += 1;
		if (Position(PTurn) > 32)
			Position(PTurn) -= 32;
		P = Next(P);
		if (Position(PTurn) == 2)
		{
			Money(PTurn) += Bonus;
			printf("Selamat, kamu melewati start dan mendapatkan bonus\n");
			ShowMoney();
		}
		mov -=1;
	}
	if (Type(P) == 4)
	{
		printf("Selamat, kamu mendapatkan uang bonus\n");
		Money(PTurn) += Bonus;
		ShowMoney();
	}
	PrintPos(TK, LB);
}

void MovPlayer(TabKota TK, ListBoard LB)
{
	roll();
	printf("Kedua dadu menunjukkan:\n");
	printf("%d + %d = %d\n\n", Dice1(D), Dice2(D), (Dice1(D) + Dice2(D)));
	MoveNPetak(TK, LB, (Dice1(D) + Dice2(D)));
	if (!reroll())
		rolled = true;
}

void EndTurn()
{
	if (rolled)
	{
		printf("Player %c mengakhiri gilirannya\n\n", PlayerId(PTurn));
		rolled = false;
		PTurn = Next(PTurn);
	}
	else
		printf("Kamu harus melakukan 'roll dice'\n\n");
}

void PrintPos(TabKota Kota, ListBoard LB)
{
	int length;
	int i;
	Address Petak;

	Petak = First(LB);
	printf("Kamu berada di ");
	i = Position(PTurn);
	while (i > 1)
	{
		Petak = Next(Petak);
		i -= 1;
	}
	if (Type(Petak) == 2)
		printf("START");
	if (Type(Petak) == 3)
		printf("CHANCE");
	if (Type(Petak) == 4)
		printf("BONUS");
	if (Type(Petak) == 5)
		printf("DESERTED ISLAND");
	if (Type(Petak) == 6)
		printf("WORLD CUP");
	if (Type(Petak) == 7)
		printf("WORLD TRAVEL");
	if (Type(Petak) == 1)
	{
		length = (NamaKota(Kota, Position(PTurn)).Length);
		for(i = 0; i < length; i++)
			printf("%c", Kota.TK[Position(PTurn)].name.TabKata[i]);
	}
	printf("\n\n");
}

boolean TourMono(TabKota TK, ListBoard LB)
{
	//Kamus
	//IdxType i;

	//Algoritma
	return false;
}

