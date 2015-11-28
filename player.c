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
/*	Delete semua elemen ListBoard dan alamat elemen di-dealokasi
	I.S. : L terdefinisi, boleh kosong
	F.S. : Jika L tidak kosong, semua elemen ListBoard di-delete dan didealokasi
*/
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

void hostnama(Kata *NKota) {
	char input[20], namakota[10];
	int i, length;

	printf("  Ketik \"host <nama kota>\".\n");
	printf("  Nama kota yang terpilih akan mendapatkan harga sewa 2x lipat sampai pemain melewati start.\n\n");

  INPUT:
	printf("> ");
    scanf("%s", input);
    if (strcmp(input, "host") == 0) {
        scanf("%s", input);
        if(strcmp(input, "New") == 0 || strcmp(input, "Sao") == 0) {
			scanf("%s", input);
			if(strcmp(input, "York") == 0)
				strcpy(namakota, "New York\0");
			else if(strcmp(input, "Delhi") == 0)
				strcpy(namakota, "New Delhi\0");
			else if(strcmp(input, "Paolo") == 0)
				strcpy(namakota, "Sao Paolo\0");
		}
		else
			strcpy(namakota, input);
        i = 0;
		length = 0;
        while(namakota[i] != '\0') {
			NKota->TabKata[i] = namakota[i];
			length++;
			i++;
		}
		NKota->Length = length;
	}
	else {
		printf("  Masukkan salah, ketik \"host <nama kota>\"\n\n");
		goto INPUT;
	}
}

void travelnama(Kata *NKota) {
	int i, length;
    char input[20], namakota[10];

	printf("  Kamu dapat pergi ke petak tujuan yang kamu inginkan pada saat giliran selanjutnya tanpa harus me-roll dadu.\n");
    printf("  Ketik \"travel <nama kota>\".\n\n");
  INPUT:
	printf("> ");
    scanf("%s", input);
    if (strcmp(input, "travel") == 0) {
        scanf("%s", input);
        if(strcmp(input, "New") == 0 || strcmp(input, "Sao") == 0) {
			scanf("%s", input);
			if(strcmp(input, "York") == 0)
				strcpy(namakota, "New York\0");
			else if(strcmp(input, "Delhi") == 0)
				strcpy(namakota, "New Delhi\0");
			else if(strcmp(input, "Paolo") == 0)
				strcpy(namakota, "Sao Paolo\0");
		}
		else
			strcpy(namakota, input);
        i = 0;
		length = 0;
        while(namakota[i] != '\0') {
			NKota->TabKata[i] = namakota[i];
			length++;
			i++;
		}
		NKota->Length = length;
	}
	else {
		printf("  Masukkan salah, ketik \"travel <nama kota>\"\n\n");
		goto INPUT;
	}
}

boolean isPlayerOwnKota(ListBoard LB, TabKota TK) {
	Address P;
	boolean ownKota;

	ownKota = false;
	P = First(LB);
	while(Next(P) != First(LB) && !ownKota) {
		if(Owner(TK, Id(P)) == PlayerId(PTurn))
			ownKota = true;
		P = Next(P);
	}
	return ownKota;
}

void boardWorldCup(ListBoard LB, TabKota TK) {
    Address P;
    Kata NKota;
    boolean ismine;

	ismine = false;
	if(isPlayerOwnKota(LB, TK)) {
		do {
			hostnama(&NKota);
			P = First(LB);
			while (!IsKataSama(NamaKota(TK, Id(P)), NKota)) {
				P = Next(P);
			}
			if(Owner(TK, Id(P)) == PlayerId(PTurn)) {
				isWorldCup(TK, Id(P)) = true;
				whoWorldCup(TK, Id(P)) = PlayerId(PTurn);
				if(PlayerId(PTurn) == 'A')
					idWorldCup[1] = Id(P);
				else if(PlayerId(PTurn) == 'B')
					idWorldCup[2] = Id(P);
				else if(PlayerId(PTurn) == 'C')
					idWorldCup[3] = Id(P);
				else if(PlayerId(PTurn) == 'D')
					idWorldCup[4] = Id(P);
				ismine = true;
			}
			else {
				printf("  Kota %s bukan milikmu. Pilihlah kota milikmu.", NKota);
			}
			printf("  %s menjadi host World Cup.\n", NKota);
		} while(!ismine);
	}
	else
		printf("  Sayang sekali kamu belum memiliki satu petak pun. Kamu tidak dapat memilih host World Cup.\n\n");
}

void boardWorldTravel(ListBoard LB, TabKota TK) {
	Kata NKota;
	Address P;

	travelnama(&NKota);
    P = First(LB);
    while (!IsKataSama(NamaKota(TK, Id(P)), NKota)) {
        P = Next(P);
    }
    MovWorldTravel(PTurn) = Id(P) - Position(PTurn);
    if(MovWorldTravel(PTurn) < 0)
		MovWorldTravel(PTurn) += 32;
    rolled = false;
    printf("  Kamu akan sampai di %s pada giliran selanjutnya setelah ketik perintah \"roll dice\"", NKota);
}

boolean IsPlayerOnBoard(AddressPl P, int pos) {
    if(Position(P) == pos) return true;
    else return false;
}

int PlayersOnBoard(int pos) {
    AddressPl P;
    int counts;

    counts = 0;
    P = First(Turn);
    if(Position(P) == pos) {
        counts++;
    }
    while(Next(P) != First(Turn)) {
        P = Next(P);
        if(Position(P) == pos) {
            counts++;
        }
    }
    return counts;
}

void ShowBoard(ListBoard LB, TabKota TK) {
    /*KAMUS*/
    Address PF, PL, Pt;
    AddressPl Play;
    int i, j, m, n, k, l;
    int npetak, x, y, M, N;
    int length, harga, posnama, players;
    ListBoard L1, L2;

/*ALGORITMA*/
    /*INISIALISASI*/
    npetak = 9;//Jumlah Petak
    x = 12 + 1; //Ukuran Petak
    y = 6;     //Ukuran Petak
    M = x*npetak; //Panjang Board
    N = y*npetak; //Lebar Board
    posnama = 1; //posisi baris nama dalam petak
    k = 0;

    CreateList(&L1);
    CreateList(&L2);
    PecahList(&L1, &L2, LB);
    InversList(&L2);
    PF = First(L1);
    PL = First(L2);

    for(i = 0; i <= N; i++){ //Perulangan Baris
        j = 0;
        while (j <= M) { //Perulangan Kolom
            if(i == 0) printf("_");
            else if(i == y || i == N) {
                if((j%x)== 0) printf("|");
                else printf("_");
            }
            else if(i%y == 0 && i != 0 && i != y && i != (N-y) && i != N) {
                if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                else if((j > 0 && j < x) || (j > (M-x) && j < M)) printf("_");
                else printf(" ");
            }
            else if(i > 0 && i < y) {
                if(i == posnama) { //Posisi Nama Petak
					if((j%x) == 0) printf("|");
                    else if((j%x) != 0){
                        printf(" ");
                        if(isWorldCup(TK, Id(PF))) printf("(");
                        PrintNamaPetak(TK, PF, 1, &length);
                        if(isWorldCup(TK, Id(PF))) printf(")");
                        if(Type(PF) == 1) {
                            if(LightOff(TK, Id(PF))) {
                                printf("*");
                                if(isWorldCup(TK, Id(PF)))
									for(m = 0; m < (x-(length+5)); m++) printf(" ");
								else
									for(m = 0; m < (x-(length+3)); m++) printf(" ");
                            }
                            else {
								if(isWorldCup(TK, Id(PF)))
									for(m = 0; m < (x-(length+4)); m++) printf(" ");
								else
									for(m = 0; m < (x-(length+2)); m++) printf(" ");
							}
                        }
                        else {
							if(isWorldCup(TK, Id(PF)))
								for(m = 0; m < (x-(length+4)); m++) printf(" ");
							else
								for(m = 0; m < (x-(length+2)); m++) printf(" ");
						}
                        j += x-2;
                        PF = Next(PF);
                    }
                }
                else if(i == posnama+1) { //Posisi Harga
                    if((j%x)== 0) printf("|");
                    else {
                        if(j > 0 && j < (M-x)) {
                            if(Type(PF) == 1) {
                                for(m = 0; m < 3; m++) printf(" ");
                                harga = Price(TK, Id(PF));
                                printf("%dK", harga);
                                if(harga < 10)
                                    for(m = 0; m < x-2-4; m++) printf(" ");
                                else if(harga >= 10 && harga < 100)
                                    for(m = 0; m < x-3-4; m++) printf(" ");
                                else
                                    for(m = 0; m < x-4-4; m++) printf(" ");
                            }
                            else {
                                for(m = 1; m < x; m++) printf(" ");
                            }
                        }
                        else {
                            for(m = 0; m < 2; m++) printf(" ");
                            PrintNamaPetak(TK, PF, 2, &length);
                            for(m = 0; m < (x-length-3); m++) printf(" ");
                        }
                        j += x-2;
                        PF = Next(PF);
                    }
                }
                else if(i == posnama+2) { //Posisi Kepemilikan
                    if((j%x)== 0) printf("|");
                    else {
                        if(j > 0 && j < (M-x)) {
                            if(Type(PF) == 1) {
                                if(Owner(TK, Id(PF)) != '0') {
                                    for(m = 0; m < 4; m++) printf(" ");
                                    printf("%c", Owner(TK, Id(PF)));
                                    if(Level(TK, Id(PF)) > 0) {
                                        printf("%d", Level(TK, Id(PF)));
                                        for(m = 0; m < x-5-2; m++) printf(" ");
                                    }
                                    else
                                        for(m = 0; m < x-4-2; m++) printf(" ");
                                }
                                else
                                    for(m = 1; m < x; m++) printf(" ");
                            }
                            else {
                                for(m = 1; m < x; m++) printf(" ");
                            }
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                        PF = Next(PF);
                    }
                }
                else if(i == posnama+3) { //Posisi Players
					if((j%x) == 0) printf("|");
                    else if((j%x) != 0){
                        players = PlayersOnBoard(Id(PF));
                        if(players != 0) {
                            if(players == 1) printf("    ");
                            else if(players == 2) printf("  ");
                            else if(players == 3) printf(" ");
                            else if(players == 4) printf(" ");
                            Play = First(Turn);
                            if(IsPlayerOnBoard(Play, Id(PF))) {
                                printf("%c ", PlayerId(Play));
                            }
                            while(Next(Play) != First(Turn)) {
                                Play = Next(Play);
                                if(IsPlayerOnBoard(Play, Id(PF))) {
                                    printf("%c ", PlayerId(Play));
                                }
                            }
                            if(players == 1) for(m = 0; m < x-5-2; m++) printf(" ");
                            else if(players == 2) for(m = 0; m < x-3-4; m++) printf(" ");
                            else if(players == 3) for(m = 0; m < x-2-6; m++) printf(" ");
                            else if(players == 4) for(m = 0; m < x-2-8; m++) printf(" ");
                        }
                        else for(m = 1; m < x; m++) printf(" ");
                        j += x-2;
                        PF = Next(PF);
                    }
                }
                else {
                    if((j%x)== 0) printf("|");
                    else printf(" ");
                }
            }
            else if(i > y && i < (N-y) && (i%y) != 0) {
                if((i%y) == posnama) { //Posisi Nama
                    if(j > 0 && j < x) {
                        for(m = 0; m < 1; m++) printf(" ");
                        if(isWorldCup(TK, Id(PF))) printf("(");
                        PrintNamaPetak(TK, PL, 1, &length);
                        if(isWorldCup(TK, Id(PF))) printf(")");
                        if(Type(PL) == 1) {
                            if(LightOff(TK, Id(PL))) {
                                printf("*");
                                if(isWorldCup(TK, Id(PF)))
									for(m = 0; m < (x-(length+5)); m++) printf(" ");
                                else
									for(m = 0; m < (x-(length+3)); m++) printf(" ");
                            }
                            else {
								if(isWorldCup(TK, Id(PF)))
									for(m = 0; m < (x-(length+4)); m++) printf(" ");
								else
									for(m = 0; m < (x-(length+2)); m++) printf(" ");
							}
                        }
                        else {
							if(isWorldCup(TK, Id(PF)))
								for(m = 0; m < (x-(length+4)); m++) printf(" ");
							else
								for(m = 0; m < (x-(length+2)); m++) printf(" ");
                        }
                        j += x-2;
                    }
                    else if(j > (M-x) && j < M) {
                        for(m = 0; m < 1; m++) printf(" ");
                        if(isWorldCup(TK, Id(PF))) printf("(");
                        PrintNamaPetak(TK, PF, 1, &length);
                        if(isWorldCup(TK, Id(PF))) printf("(");
                        if(LightOff(TK, Id(PF))) {
                            printf("*");
                            if(isWorldCup(TK, Id(PF)))
								for(m = 0; m < (x-(length+5)); m++) printf(" ");
                            else
								for(m = 0; m < (x-(length+3)); m++) printf(" ");
                        }
                        else {
							if(isWorldCup(TK, Id(PF)))
								for(m = 0; m < (x-(length+4)); m++) printf(" ");
							else
								for(m = 0; m < (x-(length+2)); m++) printf(" ");
                        }
                        j += x-2;
                    }
                    else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                    else printf(" ");
                }
                else if((i%y) == posnama+1) { //Posisi Harga
                    if(j > 0 && j < x) {
                        if(Type(PL) == 1) {
                            for(m = 0; m < 3; m++) printf(" ");
                            harga = Price(TK, Id(PL));
                            printf("%dK", harga);
                            if(harga < 10)
                                for(m = 0; m < x-2-4; m++) printf(" ");
                            else if(harga >= 10 && harga < 100)
                                for(m = 0; m < x-3-4; m++) printf(" ");
                            else
                                for(m = 0; m < x-4-4; m++) printf(" ");
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                    }
                    else if(j > (M-x) && j < M) {
                        if(Type(PF) == 1) {
                            for(m = 0; m < 3; m++) printf(" ");
                            harga = Price(TK, Id(PF));
                            printf("%dK", harga);
                            if(harga < 10)
                                for(m = 0; m < x-2-4; m++) printf(" ");
                            else if(harga >= 10 && harga < 100)
                                for(m = 0; m < x-3-4; m++) printf(" ");
                            else
                                for(m = 0; m < x-4-4; m++) printf(" ");
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                    }
                    else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                    else printf(" ");
                }
                else if((i%y) == posnama+2) { //Posisi Milik
                    if(j > 0 && j < x) {
                        if(Type(PL) == 1) {
                            if(Owner(TK, Id(PL)) != '0') {
                                for(m = 0; m < 4; m++) printf(" ");
                                printf("%c", Owner(TK, Id(PL)));
                                if(Level(TK, Id(PL)) > 0) {
                                    printf("%d", Level(TK, Id(PL)));
                                    for(m = 0; m < x-5-2; m++) printf(" ");
                                }
                                else
                                    for(m = 0; m < x-4-2; m++) printf(" ");
                            }
                            else
                                for(m = 1; m < x; m++) printf(" ");
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                    }
                    else if(j > (M-x) && j < M) {
                        if(Type(PF) == 1) {
                            if(Owner(TK, Id(PF)) != '0') {
                                for(m = 0; m < 4; m++) printf(" ");
                                printf("%c", Owner(TK, Id(PF)));
                                if(Level(TK, Id(PF)) > 0) {
                                    printf("%d", Level(TK, Id(PF)));
                                    for(m = 0; m < x-5-2; m++) printf(" ");
                                }
                                else
                                    for(m = 0; m < x-4-2; m++) printf(" ");
                            }
                            else
                                for(m = 1; m < x; m++) printf(" ");
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                    }
                    else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                    else printf(" ");
                }
                else if((i%y) == posnama+3) { //Posisi Players
                    if(j > 0 && j < x) {
                        players = PlayersOnBoard(Id(PL));
                        if(players != 0) {
                            if(players == 1) printf("    ");
                            else if(players == 2) printf("  ");
                            else if(players == 3) printf(" ");
                            else if(players == 4) printf(" ");
                            Play = First(Turn);
                            if(IsPlayerOnBoard(Play, Id(PL))) {
                                printf("%c ", PlayerId(Play));
                            }
                            while(Next(Play) != First(Turn)) {
                                Play = Next(Play);
                                if(IsPlayerOnBoard(Play, Id(PL))) {
                                    printf("%c ", PlayerId(Play));
                                }
                            }
                            if(players == 1) for(m = 0; m < x-5-2; m++) printf(" ");
                            else if(players == 2) for(m = 0; m < x-3-4; m++) printf(" ");
                            else if(players == 3) for(m = 0; m < x-2-6; m++) printf(" ");
                            else if(players == 4) for(m = 0; m < x-2-8; m++) printf(" ");
                        }
                        else for(m = 1; m < x; m++) printf(" ");
                        j += x-2;
                        PL = Next(PL);
                    }
                    else if(j > (M-x) && j < M) {
                        players = PlayersOnBoard(Id(PF));
                        if(players != 0) {
                            if(players == 1) printf("    ");
                            else if(players == 2) printf("  ");
                            else if(players == 3) printf(" ");
                            else if(players == 4) printf(" ");
                            Play = First(Turn);
                            if(IsPlayerOnBoard(Play, Id(PF))) {
                                printf("%c ", PlayerId(Play));
                            }
                            while(Next(Play) != First(Turn)) {
                                Play = Next(Play);
                                if(IsPlayerOnBoard(Play, Id(PF))) {
                                    printf("%c ", PlayerId(Play));
                                }
                            }
                            if(players == 1) for(m = 0; m < x-5-2; m++) printf(" ");
                            else if(players == 2) for(m = 0; m < x-3-4; m++) printf(" ");
                            else if(players == 3) for(m = 0; m < x-2-6; m++) printf(" ");
                            else if(players == 4) for(m = 0; m < x-2-8; m++) printf(" ");
                        }
                        else for(m = 1; m < x; m++) printf(" ");
                        j += x-2;
                        PF = Next(PF);
                    }
                    else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                    else printf(" ");
                }
                else {
                    if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                    else printf(" ");
                }
            }
            else if(i == (N-y)) {
                Pt = PL;
                if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                else printf("_");
            }
            else if(i > (N-y) && i < N) {
                if(i == (N-y)+posnama) { //Posisi Nama Petak
					if((j%x)== 0) printf("|");
                    else {
                        printf("  ");
                        if(isWorldCup(TK, Id(PF))) printf("(");
                        PrintNamaPetak(TK, PL, 1, &length);
                        if(isWorldCup(TK, Id(PF))) printf(")");
                        if(LightOff(TK, Id(PL))) {
                            printf("*");
                            if(isWorldCup(TK, Id(PF)))
								for(m = 0; m < (x-(length+6)); m++) printf(" ");
							else
								for(m = 0; m < (x-(length+4)); m++) printf(" ");
                        }
                        else {
							if(isWorldCup(TK, Id(PF)))
								for(m = 0; m < (x-(length+5)); m++) printf(" ");
							else
								for(m = 0; m < (x-(length+3)); m++) printf(" ");
                        }
                        j += x-2;
                        PL = Next(PL);
                    }
                }
                else if(i == (N-y)+posnama+1) { //Posisi Harga
                    if((j%x)== 0) printf("|");
                    else {
                        if(j > x && j < (M-x)) {
                            if(Type(PL) == 1) {
                                for(m = 0; m < 3; m++) printf(" ");
                                harga = Price(TK, Id(PL));
                                printf("%dK", harga);
                                if(harga < 10)
                                    for(m = 0; m < x-2-4; m++) printf(" ");
                                else if(harga >= 10 && harga < 100)
                                    for(m = 0; m < x-3-4; m++) printf(" ");
                                else
                                    for(m = 0; m < x-4-4; m++) printf(" ");
                            }
                            else {
                                for(m = 1; m < x; m++) printf(" ");
                            }
                        }
                        else {
                            for(m = 0; m < 2; m++) printf(" ");
                            PrintNamaPetak(TK, PL, 2, &length);
                            for(m = 1; m < (x-length-2); m++) printf(" ");
                        }
                        j += x-2;
                        PL = Next(PL);
                    }
                }
                else if(i == (N-y)+posnama+2) { //Posisi Milik
                    if((j%x)== 0) printf("|");
                    else {
                        if(j > x && j < (M-x)) {
                            if(Type(PL) == 1) {
                                if(Owner(TK, Id(PL)) != '0') {
                                    for(m = 0; m < 4; m++) printf(" ");
                                    printf("%c", Owner(TK, Id(PL)));
                                    if(Level(TK, Id(PL)) > 0) {
                                        printf("%d", Level(TK, Id(PL)));
                                        for(m = 0; m < x-5-2; m++) printf(" ");
                                    }
                                    else
                                        for(m = 0; m < x-4-2; m++) printf(" ");
                                }
                                else
                                    for(m = 1; m < x; m++) printf(" ");
                            }
                            else {
                                for(m = 1; m < x; m++) printf(" ");
                            }
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                        PL = Next(PL);
                    }
                }
                else if(i == (N-y)+posnama+3) { //Posisi Players
                    if((j%x)== 0) printf("|");
                    else {
                        players = PlayersOnBoard(Id(PL));
                        if(players != 0) {
                            if(players == 1) printf("    ");
                            else if(players == 2) printf("  ");
                            else if(players == 3) printf(" ");
                            else if(players == 4) printf(" ");
                            Play = First(Turn);
                            if(IsPlayerOnBoard(Play, Id(PL))) {
                                printf("%c ", PlayerId(Play));
                            }
                            while(Next(Play) != First(Turn)) {
                                Play = Next(Play);
                                if(IsPlayerOnBoard(Play, Id(PL))) {
                                    printf("%c ", PlayerId(Play));
                                }
                            }
                            if(players == 1) for(m = 0; m < x-5-2; m++) printf(" ");
                            else if(players == 2) for(m = 0; m < x-3-4; m++) printf(" ");
                            else if(players == 3) for(m = 0; m < x-2-6; m++) printf(" ");
                            else if(players == 4) for(m = 0; m < x-2-8; m++) printf(" ");
                        }
                        else for(m = 1; m < x; m++) printf(" ");
                        j += x-2;
                        PL = Next(PL);
                    }
                }
                else {
                    if((j%x)== 0) printf("|");
                    else printf(" ");
                }
            }
            j++;
        }
        printf("\n");
        if(i == posnama || i == posnama+1 || i == posnama+2) PF = First(L1);
        if(i == (N-y)+posnama || i == (N-y)+posnama+1 || i == (N-y)+posnama+2) PL = Pt;
    }
    printf("* menandakan kota sedang mati lampu.\n");
    printf("() menandakan sedang terjadi World Cup pada kota tersebut.\n");
}

/*
void deletePlayer(ListPlayer *L,Player P)
{
    AddressPl temp=First(*L);
    while (Info(temp)!=P)
    {
        temp=Next(temp);
    }
}
*/
boolean isWinTour(TabKota Kota)
{
    boolean valid = false;
    int jumRekPl,j,i;
    AddressPl Plyr;
    Plyr = First(Turn);
    i=1;
    while ((i<=jumlahPemain) && (valid == false))
    {
        jumRekPl = 0;
        for (j=1; j<=jumPetak; j++){
            if ((isRekreasi(Kota,j) == true) && (Owner(Kota,j) == PlayerId(Plyr))){
                jumRekPl ++;
            }
        }
        if (jumRekPl == jumRek){
            valid = true;
            printf("  Player %c memenangkan game karena Tour\n",PlayerId(Plyr));
        }
        Plyr = Next(Plyr);
        i++;
    }
    return valid;
}

boolean isWinBlock(TabKota Kota)
{
    boolean valid = false;
    int jumBlockPl,k,j,i,temp;
    AddressPl Plyr = First(Turn);
    i = 1;
    while ((i <= 1) && (valid == false))
    {
        jumBlockPl = 0;
        for (j=1; j<=3; j++){
            temp = 0;
            for (k=1; k<=jumPetak; k++){
                if ((Block(Kota,k) == j) && (Owner(Kota,k) == PlayerId(Plyr))){
                    temp ++;
                }
            }
            temp /= 3;
            jumBlockPl += temp;
        }
        if (jumBlockPl >= 3){
            valid = true;
            printf("  Player %c memenangkan game karena Triple Monopoly\n",PlayerId(Plyr));
        }
        i++;
        Plyr = Next(Plyr);
    }
    return valid;
}
