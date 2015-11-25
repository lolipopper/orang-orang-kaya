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

void ConsPlayer(Player *P, int position, long long money, int nFreeTax, int nFreePrison, int nOffLight, int nProtect, char playerId, int kekayaan, boolean jail)
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
}

void InitPlayer(Player *P, char playerId)
{
	ConsPlayer(P,1,1000,0,0,0,0,playerId,0,false);
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

void boardTax()
{
    boolean inputBenar;
    char input[20];

    printf("  Pajak Bumi dan Bangunan. Kamu harus membayar sebesar 100K.\n");
    printf("  Kamu bisa bebas dari pajak dengan menggunakan kartu Free Tax.\n");
    printf("  Ketik 'free tax' untuk menggunakan kartu Free Tax, 'pay' untuk tetap membayar.\n");
    inputBenar = false;
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "free") == 0) {
            scanf("%s", input);
            if (strcmp(input, "tax") == 0) {
                if (CardFreeTax(PTurn) == 0) {
                    printf("  Kamu tidak memiliki kartu Free Tax.\n");
                }
                else {
                    CardFreeTax(PTurn) -= 1;
                    printf("  Kamu bebas pajak.\n");
                    inputBenar = true;
                }
            }
            else if (strcmp(input, "pay") == 0) {
                printf("Uang kamu berkurang sebesar 100K.\n");
                inputBenar = true;
                Money(PTurn) -= 100;
            }
        }
    } while (!inputBenar);
}

void boardBonus()
{
    long long int randomNum;

    randomNum = (rand() % 300) + 100;
    printf("  Selamat, kamu mendapatkan %lld.\n\n", randomNum);
    Money(PTurn) += randomNum;
    ShowMoney();
}

void boardDesertedIsland()
{
    boolean inputBenar;
    char input[20];

    printf("  Kamu masuk penjara.\n");
    printf("  Kamu bisa keluar dengan menggunakan kartu Free Prison atau membayar 300K\n");
    printf("  Ketik 'free me' untuk menggunakan kartu Free Prison, 'pay' untuk membayar, 'stay' untuk tetap di penjara.\n\n");
    inputBenar = false;
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "free") == 0) {
            scanf("%s", input);
            if (strcmp(input, "me") == 0) {
                if (CardFreePrison(PTurn) == 0) {
                    printf("  Kamu tidak memiliki kartu Free Prison.\n");
                }
                else {
                    CardFreePrison(PTurn) -= 1;
                    printf("  Kamu bebas dari penjara.\n");
                    inputBenar = true;
                }
            }
        }
        else if (strcmp(input, "pay") == 0) {
            if (Money(PTurn) < 300) {
                printf("  Uangmu tidak cukup.\n");
            }
            else {
                Money(PTurn) -= 300;
                printf("  Kamu bebas dari penjara.\n");
                inputBenar = true;
                }
        }
        else if (strcmp(input, "stay") == 0) {
            printf("  Kamu masuk penjara.\n");
            inputBenar = true;
            Jail(PTurn) = true;
        }
    } while (!inputBenar);
}

void boardChance()
{
    randomCard(&C);
}

void boardWorldCup()
{
    /*
    char input[20];
    ListBoard LB;
    Address P;
    TabKota TK;

    printf("  Ketik 'host <nama kota>. Nama kota yang terpilih akan mendapatkan harga sewa 2x lipat sampai pemain melewati start.\n");
    scanf("%s", input);
    if (strcmp(input, "host") == 0) {
        scanf("%s", input);
        P = First(LB);
        while (input != NamaKota(TK,Id(P))) {
            P = Next(P);
        }
    } */
}
