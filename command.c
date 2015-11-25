#include "command.h"

void MovPlayer(TabKota TK, ListBoard LB)
{
    if (!Jail(PTurn)) {
        if (!rolled) {
            roll();
            printf("  %d + %d = %d\n", Dice1(D), Dice2(D), (Dice1(D) + Dice2(D)));
            MoveNPetak(TK, LB, (Dice1(D) + Dice2(D)));
            if (!reroll()) {
                rolled = true;
            }
        }
    }
    else {
        printf("Maaf, kamu sedang dipenjara.\n\n");
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
		if (Position(PTurn) == 1) {
            printf("  Kamu melewati board Start. Kamu mendapatkan bonus 150K.\n");
            Money(PTurn) += 150;
            ShowMoney();
		}
		P = Next(P);
		mov -=1;
	}
	PrintPos(TK, LB);
	if (Type(P) == 8) {
		boardTax();
	}
	if (Type(P) == 4) {
		boardBonus();
	}
	if (Type(P) == 5) {
		boardDesertedIsland();
	}
	if (Type(P) == 3) {
		boardChance();
	}
	if (Type(P) == 6) {
        boardWorldCup();
	}
	printf("\n");
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
	printf("  Uangmu sekarang : %lldK \n", Money(PTurn));
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
		printf("board Deserted Island");
	}
	if (Type(Petak) == 6) {
		printf("board World Cup");
	}
	if (Type(Petak) == 7) {
		printf("board World Travel");
	}
	if (Type(Petak) == 8) {
		printf("board Tax");
	}
	if (Type(Petak) == 1) {
		length = (NamaKota(Kota, Position(PTurn)).Length);
		for(i = 0; i < length; i++)
			printf("%c", Kota.TK[Position(PTurn)].name.TabKata[i]);
	}
	printf("\n");
}

void buy()
{
    int pos;
    TabKota Kota;
    ListBoard LB;
    Address P;

    pos = Position(PTurn);
    P = First(LB);

        printf("pos : %d\n", pos);
        printf("id : %d\n", Id(P));
    while (pos != Id(P)) {
        printf("pos : %d\n", pos);
        printf("id : %d\n", Id(P));
        P = Next(P);
    }
    if (Type(P) == 1) {
        if (Owner(Kota,pos) != PlayerId(PTurn)) {
            if (isRekreasi(Kota,pos) == true) {
                if (Money(PTurn) < priceCity(Kota.TK[pos])) {
                    printf("Uangmu tidak cukup untuk membeli tempat rekreasi ini.\n");
                }
                else {
                    Money(PTurn) -= priceCity(Kota.TK[pos]);
                    Owner(Kota,pos) = PlayerId(PTurn);
                    Level(Kota,pos)++;
                    printf("  Selamat, kota ini menjadi milikmu!\n");
                    printf("  Level bangunan %d\n", Level(Kota,pos));
                    ShowMoney();
                }
            }
            else {
                if (Level(Kota,pos) == 3) {
                    printf("Kota ini telah menjadi landmark. Landmark tidak bisa dibeli.\n");
                }
                else {
                    if (Money(PTurn) < priceCity(Kota.TK[pos])) {
                        printf("Uangmu tidak cukup untuk membeli kota ini.\n");
                    }
                    else {
                        Money(PTurn) -= priceCity(Kota.TK[pos]);
                        Owner(Kota,pos) = PlayerId(PTurn);
                        Level(Kota,pos)++;
                        printf("  Selamat, kota ini menjadi milikmu!\n");
                        printf("  Level bangunan %d\n", Level(Kota,pos));
                        ShowMoney();
                    }
                }
            }
        }
        else {
            printf("Kota ini milik kamu. Kamu tidak bisa membeli kotamu sendiri.\n");
        }
    }
    else {
        printf("Board ini tidak bisa dibeli.\n");
    }
}
