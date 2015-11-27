#include "command.h"

void MovPlayer(TabKota *TK, ListBoard *LB)
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

void MoveNPetak(TabKota *TK, ListBoard *LB, int N)
{
	int i, mov;
	Address P;

	i = Position(PTurn);
	P = First(*LB);
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
	PrintPos(*TK, *LB);
	if (Type(P) == 1) {
        payRent(LB, TK);
	}
	if (Type(P) == 3) {
		boardChance();
	}
	if (Type(P) == 4) {
		boardBonus();
	}
	if (Type(P) == 5) {
		boardDesertedIsland();
	}
	if (Type(P) == 6) {
        //boardWorldCup();
	}
	if (Type(P) == 8) {
		boardTax();
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

void buy(TabKota *Kota, ListBoard *LB)
{
    int pos;
    Address P;
    AddressPl Pl;

    pos = Position(PTurn);
    P = First(*LB);
    while (pos != Id(P)) {
        P = Next(P);
    }
    if (Type(P) == 1) {
        if (Owner(*Kota,pos) != PlayerId(PTurn)) {
            if (isRekreasi(*Kota,pos) == true) {
                if (Money(PTurn) < priceCity((*Kota).TK[pos])) {
                    printf("  Uangmu tidak cukup untuk membeli tempat rekreasi ini.\n");
                }
                else {
                    Money(PTurn) -= priceCity((*Kota).TK[pos]);
                    Kekayaan(PTurn) += priceCity((*Kota).TK[pos]);
                    Owner(*Kota,pos) = PlayerId(PTurn);
                    Level(*Kota,pos)++;
                    printf("  Selamat, tempat rekreasi ini menjadi milikmu!\n");
                    ShowMoney();
                }
            }
            else {
                if (Level(*Kota,pos) == 3) {
                    printf("  Kota ini telah menjadi landmark. Landmark tidak bisa dibeli.\n");
                }
                else {
                    if (Money(PTurn) < priceCity((*Kota).TK[pos])) {
                        printf("  Uangmu tidak cukup untuk membeli kota ini.\n");
                    }
                    else {
                        Money(PTurn) -= priceCity((*Kota).TK[pos]);
                        Kekayaan(PTurn) += priceCity((*Kota).TK[pos]);
                        Pl = First(Turn);
                        while (PlayerId(Pl) != Owner(*Kota,pos)) {
                            Pl = Next(Pl);
                        }
                        Kekayaan(Pl) -= priceCity((*Kota).TK[pos]);
                        Owner(*Kota,pos) = PlayerId(PTurn);
                        if (Level(*Kota,pos) == 0) {
                            Level(*Kota,pos)++;
                        }
                        printf("  Selamat, kota ini menjadi milikmu!\n");
                        printf("  Level bangunan %d\n", Level(*Kota,pos));
                        ShowMoney();
                    }
                }
            }
        }
        else {
            printf("  Kota ini milik kamu. Kamu tidak bisa membeli kotamu sendiri.\n");
        }
    }
    else {
        printf("  Board ini tidak bisa dibeli.\n");
    }
}

void upgrade(TabKota *Kota, ListBoard *LB)
{
    int pos;
    Address P;

    pos = Position(PTurn);
    P = First(*LB);
    while (pos != Id(P)) {
        P = Next(P);
    }
    if (Type(P) == 1) {
        if (Owner(*Kota,pos) == PlayerId(PTurn)) {
            if (isRekreasi(*Kota,pos) == true) {
                printf("  Maaf, board rekreasi tidak bisa diupgrade lagi.\n");
            }
            else {
                if (Level(*Kota,pos) == 3) {
                    printf("  Kota ini telah menjadi landmark. Landmark tidak bisa upgrade.\n");
                }
                else {
                    if (Money(PTurn) < priceUpgrade((*Kota).TK[pos])) {
                        printf("  Uangmu tidak cukup untuk mengupgrade kota ini.\n");
                    }
                    else {
                        Money(PTurn) -= priceUpgrade((*Kota).TK[pos]);
                        Kekayaan(PTurn) += priceUpgrade((*Kota).TK[pos]);
                        Level(*Kota,pos)++;
                        printf("  Selamat, level kota ini naik menjadi %d\n", Level(*Kota,pos));
                        ShowMoney();
                        printf("\n");
                    }
                }
            }
        }
        else {
            printf("  Kota ini bukan milik kamu. Kamu hanya bisa mengupgrade kota milikmu.\n");
        }
    }
    else {
        printf("  Board ini tidak bisa diupgrade.\n");
    }
}

void payRent(ListBoard *LB, TabKota *Kota)
{
    int pos;
    AddressPl Pl;

    pos = Position(PTurn);
    Pl = First(Turn);

    if ( (Owner(*Kota,pos) != '0') || (PlayerId(Pl) != PlayerId(PTurn)) ) {
        while (PlayerId(Pl) != Owner(*Kota,pos)) {
            Pl = Next(Pl);
        }
        printf("  Kamu harus membayar sewa ke pemilik kota ini sebanyak %d\n", priceCity((*Kota).TK[pos]));
        Money(PTurn) -= priceCity((*Kota).TK[pos]);
        Money(Pl) += priceCity((*Kota).TK[pos]);
        ShowMoney();
    }
}

void infoCity(Kata K, TabKota TK)
{
    int i, j;

    i = 1;
    while ((!IsKataSama(K, NamaKota(TK,i))) && (i<= 32)) {
        i++;
    }
    if (i <= 32) {
        printf("  ");
        for (j=0; j<K.Length; j++) {
            printf("%c", K.TabKata[j]);
        }
        printf(", pemilik properti ");
        if (Owner(TK,i) == '0') {
            printf("tidak ada, ");
        }
        else {
            printf("%c, ", Owner(TK,i));
        }
        printf("bangunan level %d\n", Level(TK,i));
        printf("  Biaya sewa : %lld\n", priceCity(TK.TK[i]));
        printf("  Biaya ambil alih : %lld\n", priceCity(TK.TK[i]));
        printf("  Biaya upgrade bangunan : %lld\n", priceUpgrade(TK.TK[i]));
        printf("\n");
    }
    else {
        printf("  Tidak ada kota dengan nama tersebut.\n");
    }
}

void showLeaderBoard()
{
    long long kekayaan[jumlahPemain - 1];
    AddressPl Pl;
    int i;

    Pl = First(Turn);
    i = 0;
    do {
        kekayaan[i] = Money(Pl) + Kekayaan(Pl);
        Pl = Next(Pl);
        i++;
    } while (i<=jumlahPemain-1);
    printf("Player A %lldK\n", kekayaan[0]);
    printf("Player B %lldK\n", kekayaan[1]);
    if (jumlahPemain > 2) {
        printf("Player C %lldK\n", kekayaan[2]);
        if (jumlahPemain > 3) {
            printf("Player B %lldK\n", kekayaan[4]);
        }
    }
    printf("\n");
}

