#include "command.h"

void MovPlayer(TabKota TK, ListBoard LB)
{
    if (!rolled) {
        roll();
        printf("  %d + %d = %d\n", Dice1(D), Dice2(D), (Dice1(D) + Dice2(D)));
        MoveNPetak(TK, LB, (Dice1(D) + Dice2(D)));
        if (!reroll()) {
            rolled = true;
        }
    }
}

void MoveNPetak(TabKota TK, ListBoard LB, int N)
{
	int i, mov;
	Address P;

	i = Position(PTurn);
	P = First(LB);
	while (i > 1) {
		P = Next(P);
		i -= 1;
	}
	mov = N;
	while (mov > 0) {
		Position(PTurn) += 1;
		if (Position(PTurn) > 32) {
			Position(PTurn) -= 32;
		}
		P = Next(P);
		mov -=1;
	}
	PrintPos(TK, LB);
}

void EndTurn()
{
	if (rolled) {
		printf("  Player %c mengakhiri gilirannya\n\n", PlayerId(PTurn));
		rolled = false;
		PTurn = Next(PTurn);
	}
	else {
		printf("  Kamu harus melakukan 'rolldice'\n\n");
	}
}

void ShowMoney()
{
	printf("  Uangmu sekarang : %lld \n\n", Money(PTurn));
}

void PrintPos(TabKota Kota, ListBoard LB)
{
	int length;
	int i;
	Address Petak;

	Petak = First(LB);
	printf("  Player %c sampai di ", PlayerId(PTurn));
	i = Position(PTurn);
	while (i > 1) {
		Petak = Next(Petak);
		i -= 1;
	}
	if (Type(Petak) == 2) {
		printf("board Start");
	}
	if (Type(Petak) == 3) {
		printf("board Chance");
	}
	if (Type(Petak) == 4) {
		printf("board Bonus");
	}
	if (Type(Petak) == 5) {
		printf("board Bonus");
	}
	if (Type(Petak) == 6) {
		printf("board World Cup");
	}
	if (Type(Petak) == 7) {
		printf("board World Travel");
	}
	if (Type(Petak) == 1) {
		length = (NamaKota(Kota, Position(PTurn)).Length);
		for(i = 0; i < length; i++)
			printf("%c", Kota.TK[Position(PTurn)].name.TabKata[i]);
	}
	printf("\n\n");
}

void buy(Player *P, Kota *K)
{
	if ((*K).level < 3) {
		(*P).money -= (*K).price;
		(*P).kekayaan += (*K).price;
		(*K).owner = (*P).playerId;
		if ((*K).level == 0) {
			(*K).level++;
		}
	}
}

void payRent(Player *P, Kota K)
{
	(*P).money -= K.price;
	(*P).kekayaan -= K.price;
	Money(SearchPl(K.owner)) += K.price;
	Kekayaan(SearchPl(K.owner)) += K.price;
}

void Upgrade(ListBoard LB, TabKota *TK)
{
	Address P;
	int i, upgrade, length;

	P = First(LB);
	i = Position(PTurn);
	while (i > 1) {
		P = Next(P);
		i -= 1;
	}
	if (Type(P) == 1) {
		if (Owner((*TK), Id(P)) == PlayerId(PTurn)) {
			if (Level((*TK), Id(P)) < 5) {
				if (Level((*TK), Id(P)) != 3) {
					upgrade = ((Price((*TK), Position(PTurn))) * 7 / 4);
				}
				else {
					upgrade = ((Price((*TK), Position(PTurn))) * 3);
				}
				if (Money(PTurn) >= upgrade) {
					Money(PTurn) -= upgrade;
					Level((*TK), Position(PTurn)) += 1;
					printf("  Selamat! Bangunanmu di ");
					length = (NamaKota((*TK), Position(PTurn)).Length);
					for(i = 0; i < length; i++) {
						printf("%c", (*TK).TK[Position(PTurn)].name.TabKata[i]);
					}
					printf(" telah mencapai aras %d\n", Level((*TK), Id(P)));
				}
				else {
					printf("  Uangmu tidak cukup untuk meningkatkan aras bangunan anda...\n");
				}
				ShowMoney();
			}
			else {
				printf("  Bangunanmu sudah mencapai aras maksimum dan tidak dapat ditingkatkan lagi.\n");
			}
		}
		else {
			printf("  Kota ini bukan properti milikmu.\n");
		}
	}
	else {
		printf("  Petak ini bukan tempat untuk konstruksi bangunan.\n");
	}
}

void infoKota(TabKota TK, int id)
{
    printf("Nama     : %s", NamaKota(TK,id));
    printf("Price    : %d\n", Price(TK,id));
    printf("Rekreasi : %d\n", isRekreasi(TK,id));
    printf("Block    : %d\n", Block(TK,id));
    printf("Level    : %d\n", Level(TK,id));
    printf("Owner    : %d\n", Owner(TK,id));
}
