#include "player.h"

void Save (ListBoard LB, TabKota TK, SKata K)
{
    FILE *fosave;
    Address p = First(LB);
    SKata SaveFName;
    strcpy(SaveFName,K);
    strcat(SaveFName,".txt");
    fosave = fopen(SaveFName,"w");
    int i;

    //SAVE BOARD
    while (p != Last(LB))
    {
        fprintf(fosave, "%d\n",Type(p));
        if (Type(p) == 1){
            fprintf(fosave,"%s",NamaKota(TK,Id(p)));
            fprintf(fosave,"%d\n",Price(TK,Id(p)));
            fprintf(fosave,"%d\n",isRekreasi(TK,Id(p)));
            fprintf(fosave,"%d\n",Block(TK,Id(p)));
            fprintf(fosave,"%d\n",Level(TK,Id(p)));
            fprintf(fosave,"%d\n",Owner(TK,Id(p)));
            fprintf(fosave,"%d\n",NamaKota(TK,Id(p)).Length);
        }
        fprintf(fosave,"\n");
        p = Next(p);
    }
    fprintf(fosave, "%d\n",Type(p));
    if (Type(p) == 1){
        fprintf(fosave,"%s",NamaKota(TK,Id(p)));
        fprintf(fosave,"%d\n",Price(TK,Id(p)));
        fprintf(fosave,"%d\n",isRekreasi(TK,Id(p)));
        fprintf(fosave,"%d\n",Block(TK,Id(p)));
        fprintf(fosave,"%d\n",Level(TK,Id(p)));
        fprintf(fosave,"%d\n",Owner(TK,Id(p)));
        fprintf(fosave,"%d\n",NamaKota(TK,Id(p)).Length);
    }
    fprintf(fosave,"\n");
    fprintf(fosave, "%d\n",ValUndef);
    fprintf(fosave,"\n");
    //SAVE PEMAIN
    fprintf(fosave, "%d\n",jumlahPemain);
    fprintf(fosave,"\n");
    AddressPl plyr;
    plyr = First(Turn);
    for (i=1; i<=jumlahPemain; i++)
    {
        fprintf(fosave,"%d\n",Position(plyr));
        fprintf(fosave,"%lld\n",Money(plyr));
        fprintf(fosave,"%lld\n",Kekayaan(plyr));
        fprintf(fosave,"%d\n",CardFreePrison(plyr));
        fprintf(fosave,"%d\n",CardFreeTax(plyr));
        fprintf(fosave,"%d\n",CardProtect(plyr));
        fprintf(fosave,"%d\n",CardOff(plyr));
        fprintf(fosave,"%c\n",PlayerId(plyr));
        fprintf(fosave,"%d\n",Jail(plyr));
        fprintf(fosave,"%d\n",MovWorldTravel(plyr));
        fprintf(fosave,"\n");
        plyr = Next(plyr);
    }

    fclose(fosave);

    printf("File telah disave dalam file %s\n",SaveFName);
}

void Load (ListBoard *LB,TabKota *TK, SKata K)
{
    FILE *fisave;
    Address p;
    int i;
	Petak ipt;
	int dummy;
    SKata LoadFName;

    strcpy(LoadFName,K);
    strcat(LoadFName,".txt");
	i=1;
    p = First(*LB);
	fisave = fopen(LoadFName,"r");
	if (fisave){
        fscanf(fisave,"%d\n", &ipt.type);
        CreateList(LB);
        while (ipt.type != ValUndef)
        {
            //printf("load\n");
            ipt.id = i;
            InsVLast(LB,ipt);
            //printf("\n");
            //printf("First= %d\n",Info(First(*LB)).type);
            //printf("IsEmpty = %d\n",IsListEmpty(*LB));
            //printf("type: %d\n",ipt.type);
            //printf("id  : %d\n",ipt.id);
            if (ipt.type == 1){
                //printf("masukn\n");
                fgets(TK->TK[i].name.TabKata, NMax, fisave);
                //printf("nama : %s",TK->TK[i].name);
                fscanf(fisave,"%d\n",&(Price(*TK,i)));
                //printf("harga: %d\n",TK->TK[i].price);
                fscanf(fisave,"%d\n",&(isRekreasi(*TK,i)));
                //printf("rekreasi: %d\n",TK->TK[i].rekreasi);
                fscanf(fisave,"%d\n",&(Block(*TK,i)));
                //printf("block: %d\n",TK->TK[i].block);
                fscanf(fisave,"%d\n",&(Level(*TK,i)));
                //printf("level: %d\n",Level(*TK,i));
                fscanf(fisave,"%d\n",&(Owner(*TK,i)));
                //printf("owner: %d\n",Owner(*TK,i));
                fscanf(fisave,"%d\n",&(TK->TK[i].name.Length));
            }
            //fscanf(fisave,"\n");
            i++;
            //scanf("%d",&dummy);
            fscanf(fisave,"\n");
            fscanf(fisave,"%d\n", &ipt.type);
        }
        AddressPl plyr;
        //printf("Reading Jumlah Player\n");
        fscanf(fisave,"%d\n",&jumlahPemain);
        DeleteAllPlayer();
        InitNumPlayer(jumlahPemain);

        plyr = First(Turn);
        printf("Reading INfo player\n");
        for (i=1;i<=jumlahPemain;i++)
        {
            //printf("Read %d\n",i);
            fscanf(fisave,"%d\n",&Position(plyr));
            fscanf(fisave,"%d\n",&Money(plyr));
            fscanf(fisave,"%d\n",&Kekayaan(plyr));
            fscanf(fisave,"%d\n",&CardFreePrison(plyr));
            fscanf(fisave,"%d\n",&CardFreeTax(plyr));
            fscanf(fisave,"%d\n",&CardProtect(plyr));
            fscanf(fisave,"%d\n",&CardOff(plyr));
            fscanf(fisave,"%c\n",&PlayerId(plyr));
            fscanf(fisave,"%d\n",&Jail(plyr));
            fscanf(fisave,"%d\n",&MovWorldTravel(plyr));
            plyr = Next(plyr);
        }
        printf("File %s telah diload\n",LoadFName);
	}else{
        printf("Nama file tidak ditemukan!\n");
	}
	fclose(fisave);
}

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
	ConsPlayer(P,1,1000,0,0,0,0,playerId,0,false, 0);
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
    printf("  Ketik \"travel <nama kota>\".\n");
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

void boardWorldCup(ListBoard LB, TabKota TK) {
    Address P;
    Kata NKota;

    hostnama(&NKota);
    P = First(LB);
    while (!IsKataSama(NamaKota(TK, Id(P)), NKota)) {
        P = Next(P);
    }
    isWorldCup(TK, Id(P)) = true;
    whoWorldCup(TK, Id(P)) = PlayerId(PTurn);
    idWorldCup = Id(P);
    printf("  %s menjadi host World Cup.\n", NKota);
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
