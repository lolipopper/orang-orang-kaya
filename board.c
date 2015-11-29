#include "board.h"

void PrintInfoKota(TabKota TK, int id)
{
    printf("  Nama     : %s",NamaKota(TK,id));
    printf("  Price    : %lld\n",Price(TK,id));
    printf("  SellPrice: %lld\n",priceSell(City(TK,id)));
    printf("  Rekreasi : %d\n",isRekreasi(TK,id));
    printf("  Block    : %d\n",Block(TK,id));
    printf("  Level    : %d\n",Level(TK,id));
    printf("  Owner    : %c\n",Owner(TK,id));
    printf("\n");
}

void PrintInfoAdr(Address p, TabKota TK)
{
    printf("[%d] ",Id(p));
        if (Type(p) == 1){
            if(isRekreasi(TK,Id(p)) == true){
                printf("<KOTA REKREASI> ");
            }else{
                printf("<KOTA> ");
            }
            printf("%s",NamaKota(TK,Id(p)));
        }else if (Type(p) == 2){
            printf("<START>\n");
        }else if (Type(p) == 3){
            printf("<CHANCE>\n");
        }else if (Type(p) == 4){
            printf("<BONUS>\n");
        }else if (Type(p) == 5){
            printf("<DESERTED ISLAND>\n");
        }else if (Type(p) == 6){
            printf("<WORLD CUP>\n");
        }else if (Type(p) == 7){
            printf("<WORLD TRAVEL>\n");
        }else{
            printf("<TAX>\n");
        }
        //printf("\n");
}

void PrintInfoBoard(ListBoard LB, TabKota TK)
{
    Address p;
    if (IsListEmpty(LB) == true){
        printf("KOSONG\n");
    }else{
        //printf("%d\n",Info(p).type);
        p = First(LB);
        while (p != Last(LB))
        {
            PrintInfoAdr(p,TK);
            p = Next(p);
        }
        PrintInfoAdr(p,TK);
        printf("< END >\n");
        printf("\n");
    }
}

void PrintNamaPetak(TabKota TK, Address P, int baris, int *length) {
/*KAMUS*/
    int i;
/*ALGORITMA*/
    if(Type(P) == 1) {
        *length = NamaKota(TK, Id(P)).Length;
        for(i = 0; i < *length; i++) {
            printf("%c", TK.TK[Id(P)].name.TabKata[i]);
        }
    }
    else if(Type(P) == 2) {
        printf("START");
        *length = 5;
    }
    else if(Type(P) == 3) {
        printf("CHANCE");
        *length = 6;
    }
    else if(Type(P) == 4) {
        printf("BONUS");
        *length = 5;
    }
    else if(Type(P) == 5) {
        if(baris == 1) {
            printf("DESERTED");
            *length = 8;
        }
        else {
            printf("ISLAND");
            *length = 6;
        }
    }
    else if(Type(P) == 6) {
        if(baris == 1) {
            printf("WORLD");
            *length = 5;
        }
        else {
            printf("CUP");
            *length = 3;
        }
    }
    else if(Type(P) == 7) {
        if(baris == 1) {
            printf("WORLD");
            *length = 5;
        }
        else {
            printf("TRAVEL");
            *length = 6;
        }
    }
    else if(Type(P) == 8) {
        printf("TAX");
        *length = 3;
    }
}

int SearchKota(Kata K,TabKota TK)
/* Mengembalikan id dengan nama kota K berada
   bila tidak ada kota bernama K, dikembalikan 33 (jumlah petak + 1)
*/
{
    int id;
    id = 1;
    while ((!IsKataSama(K, NamaKota(TK,id))) && (id<= 32)) {
        id++;
    }
    return id;
    /*
    Address p;
    boolean found;

    found = false;
    p = First(LB);
    while ((found == false) && (p != Last(LB)))
    {
        if (Info(p).type == 1){
            if((IsKataSama(NamaKota(TK,Id(p)), NamaKota) == true)){
                found = true;
            }
        }
        p = Next(p);
    }

    if (Info(p).type == 1){
        if((IsKataSama(NamaKota(TK,Id(p)), NamaKota) == true)){
            found = true;
        }
    }

    if (found == true)
        return p;
    else
        return Nil; */
}

void initBoard(ListBoard *LB,TabKota *TK)
{
    FILE *fiboard;
    Address p;
    int i;
	Petak ipt;
	int dummy;

	jumRek = 0;
	i=1;
    p = First(*LB);
	fiboard = fopen("board.txt","r");
	fscanf(fiboard,"%d\n", &ipt.type);
	CreateList(LB);
    while (ipt.type != ValUndef)
    {
        ipt.id = i;
        InsVLast(LB,ipt);
        if (ipt.type == 1){
            fgets(TK->TK[i].name.TabKata, NMax, fiboard);
            fscanf(fiboard,"%d\n",&(TK->TK[i].price));
            fscanf(fiboard,"%d\n",&(TK->TK[i].rekreasi));
            fscanf(fiboard,"%d\n",&(TK->TK[i].block));
            fscanf(fiboard,"%d\n",&(TK->TK[i].level));
            fscanf(fiboard,"%c\n",&(TK->TK[i].owner));
            fscanf(fiboard,"%d\n",&(TK->TK[i].LightOff));
            fscanf(fiboard,"%d\n",&(TK->TK[i].WorldCup.isWCup));
            fscanf(fiboard,"%c\n",&(TK->TK[i].WorldCup.who));
            fscanf(fiboard,"%d\n",&(TK->TK[i].name.Length));
            isOffered(*TK,i) = false;
            if (isRekreasi(*TK,i) == true){
                jumRek++;
            }
            jumBlock = Block(*TK,i);
        }
        i++;
        fscanf(fiboard,"%d\n", &ipt.type);
    }
    jumPetak = i-1;
	fclose(fiboard);

}

/*void FPrintKota(FILE *fokota, TabKota TK, int id)
{
    int i;

    fokota = fopen("save_file.txt","w");

    for(i=1; i<=NamaKota(TK,id).Length; i++){
        fprintf(fokota,"%c",NamaKota(TK,i),NamaKota(TK,id).TabKata[i-1]);
    }
    fclose(fokota);
}*/

Address Last(ListBoard L)
/*	I.S. sembarang
	F.S. Mengirim address terakhir dari ListBoard. Jika ListBoard kosong, kembalikan Nil.
*/
{
    Address p;

    if (IsListEmpty(L))
        return Nil;
    else{
        p = First(L);
        while (Next(p) != First(L))
            p = Next(p);
        return p;
    }
}

boolean IsListEmpty (ListBoard L)
/* Mengirim true jika ListBoard kosong */
{
    if (First(L) == Nil)
        return true;
    else
        return false;
}

void CreateList (ListBoard *L)
/*	I.S. sembarang
	F.S. Terbentuk ListBoard kosong
*/
{
    First(*L) = Nil;
}

Address Alokasi (Petak X)
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
{
    Address p;
    p = (Address) malloc (sizeof(ElmtList));
    if (p == Nil){
        return Nil;
    } else {
        Info(p) = X;
        Next(p) = Nil;
        return p;
    }
}

void Dealokasi (Address *P)
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/
{
    Next(*P) = Nil;
    free(*P);
}

void InsVLast (ListBoard *L, Petak X)
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen ListBoard di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
{
    Address p;
    p = Alokasi(X);
    if (p != Nil){
        InsertLast(L,p);
    }
}

void InsertLast (ListBoard *L, Address P)
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/
{
    if (IsListEmpty(*L) == true){
        InsertFirst(L,P);
    }else{
        Next(Last(*L)) = P;
        Next(P) = First(*L);
    }

}

void InsertFirst (ListBoard *L, Address P)
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
{
    if (IsListEmpty(*L)){
        First(*L) = P;
        Next(P) = P;
    }else{
        Next(Last(*L)) = P;
        Next(P) = First(*L);
        First(*L) = P;
    }
}

void DeleteAfter (ListBoard *L, Address *Pdel, Address Prec)
/*	I.S. ListBoard tidak kosong. Prec adalah anggota ListBoard L. Prec bukan elemen terakhir.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen ListBoard yang dihapus
*/
{
    *Pdel = Next(Prec);
    Next(Prec) = Next(*Pdel);
}

int NbElmt (ListBoard L)
/*	Mengirimkan banyaknya elemen ListBoard; mengirimkan 0 jika ListBoard kosong */
{
    int cnt;
    Address p;
    if(IsListEmpty(L) == true)
    {
        return 0;
    }else{
        cnt = 1;
        p = First(L);
        while (p != Last(L))
        {
            cnt++;
            p = Next(p);
        }
        return cnt;
    }
}

//PROSES TERHADAP ListBoard
void DeleteAll (ListBoard *L)
/*	Delete semua elemen ListBoard dan alamat elemen di-dealokasi
	I.S. : L terdefinisi, boleh kosong
	F.S. : Jika L tidak kosong, semua elemen ListBoard di-delete dan didealokasi
*/
{
    Address p,prec;
    if(IsListEmpty(*L) == false){
        p = Next(First(*L));
        prec = First(*L);
        while (p!= First(*L))
        {
            Dealokasi(&prec);
            prec = p;
            p = Next(p);
        }
        Dealokasi(&prec);
        First(*L) = Nil;
    }
}

void InversList (ListBoard *L)
/*	I.S. L terdefinisi, boleh kosong
	F.S. Elemen ListBoard L dibalik :
	Elemen terakhir menjadi elemen pertama, dan seterusnya.
	Membalik elemen ListBoard, tanpa melakukan alokasi/dealokasi.
*/
{
    Address p,fixfirst;
    int nbelmt,i;

    if (IsListEmpty(*L) == false)
    {
        nbelmt = NbElmt(*L);
        fixfirst = First(*L);
        for (i=1;i<=nbelmt-1;i++)
        {
            DeleteAfter(L,&p,fixfirst);
            //printf("%d\n",Info(p));

            InsertFirst(L,p);
        }
    }
}

void PecahList (ListBoard *L1, ListBoard *L2, ListBoard L)
/*	I.S. L mungkin kosong
	F.S. Berdasarkan L, dibentuk dua buah ListBoard L1 dan L2
	L tidak berubah : untuk membentuk L1 dan L2 harus alokasi.
	L1 berisi separuh elemen L dan L2 berisi sisa elemen L.
	Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2.
	Jila alokasi gagal, semua elemen yang sudah dialokasikan harus di-dealokasi (bisa L1, L2 atau keduanya)
*/
{
    Address p,temp;
    int i,lengthL;
    boolean valid;
    if (IsListEmpty(L) == false){
        lengthL = NbElmt(L);
        p = First(L);
        i = 1;
        valid = true;
        CreateList(L1);
        CreateList(L2);
        while((i<=lengthL/2) && (valid == true))
        {
            temp = Alokasi(Info(p));
            if (temp == Nil){
                DeleteAll(L1);
                valid = false;
            }else{
                InsertLast(L1,temp);
                p = Next(p);
                i++;
            }
        }

        valid = true;
        while ((p != Last(L)) && (valid == true))
        {
            temp = Alokasi(Info(p));
            if (temp == Nil){
                DeleteAll(L2);
                valid = false;
            }else{
                InsertLast(L2,temp);
                p = Next(p);
            }
        }
        if (valid == true)
        {
            temp = Alokasi(Info(p));
            if (temp == Nil){
                DeleteAll(L2);
                valid = false;
            }else{
                InsertLast(L2,temp);
                p = Next(p);
            }
        }
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

void boardWorldCup(ListBoard LB, TabKota TK) {
    Address P;
    Kata NKota;
	int i;
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
				printf("  Kota ");
				i = 0;
				while(i < NKota.Length) {
					printf("%c", NKota.TabKata[i]);
					i++;
				}
				printf(" bukan milikmu. Pilihlah kota milikmu.\n\n");
            }
            if(ismine) {
				printf("  ");
				i = 0;
				while(i < NKota.Length) {
					printf("%c", NKota.TabKata[i]);
					i++;
				}
				printf(" menjadi host World Cup.\n");
			}
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

void PrintNameOnBoard(Address P, TabKota TK, int x) {
	int length, m;
	
	printf(" ");
	if(Type(P) == 1) {
		if(isWorldCup(TK, Id(P))) printf("(");
		PrintNamaPetak(TK, P, 1, &length);
		if(isWorldCup(TK, Id(P))) printf(")");
		if(LightOff(TK, Id(P))) {
			printf("*");
			if(isWorldCup(TK, Id(P)))
				for(m = 0; m < (x-(length+5)); m++) printf(" ");
			else
				for(m = 0; m < (x-(length+3)); m++) printf(" ");
		}
		else {
			if(isWorldCup(TK, Id(P)))
				for(m = 0; m < (x-(length+4)); m++) printf(" ");
			else
				for(m = 0; m < (x-(length+2)); m++) printf(" ");
		}
	}
	else {
		PrintNamaPetak(TK, P, 1, &length);
		for(m = 0; m < (x-(length+2)); m++) printf(" ");
	}
}

void PrintPriceOnBoard(Address P, TabKota TK, int x) {
	int m;
	long long harga;
	
	if(Type(P) == 1) {
		for(m = 0; m < 3; m++) printf(" ");
		harga = priceCity(TK.TK[Id(P)]);
		printf("%dK", harga);
		if(harga < 10)
			for(m = 0; m < x-2-4; m++) printf(" ");
		else if(harga >= 10 && harga < 100)
			for(m = 0; m < x-3-4; m++) printf(" ");
		else
			for(m = 0; m < x-4-4; m++) printf(" ");
	}
	else
		for(m = 1; m < x; m++) printf(" ");
}

void PrintOwnerOnBoard(Address P, TabKota TK, int x) {
	int m;
	
	if(Type(P) == 1) {
		if(Owner(TK, Id(P)) != '0') {
			for(m = 0; m < 4; m++) printf(" ");
			printf("%c", Owner(TK, Id(P)));
			if(Level(TK, Id(P)) > 0) {
				printf("%d", Level(TK, Id(P)));
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

void PrintPlayersOnBoard(Address P, int x) {
	AddressPl Play;
	int players, m;
	
	players = PlayersOnBoard(Id(P));
	if(players != 0) {
		if(players == 1) printf("    ");
		else if(players == 2) printf("  ");
		else if(players == 3) printf(" ");
		else if(players == 4) printf(" ");
		Play = First(Turn);
		if(IsPlayerOnBoard(Play, Id(P)))
			printf("%c ", PlayerId(Play));
		while(Next(Play) != First(Turn)) {
			Play = Next(Play);
			if(IsPlayerOnBoard(Play, Id(P))) {
				printf("%c ", PlayerId(Play));
			}
		}
		if(players == 1) for(m = 0; m < x-5-2; m++) printf(" ");
		else if(players == 2) for(m = 0; m < x-3-4; m++) printf(" ");
		else if(players == 3) for(m = 0; m < x-2-6; m++) printf(" ");
		else if(players == 4) for(m = 0; m < x-2-8; m++) printf(" ");
	}
	else for(m = 1; m < x; m++) printf(" ");
}

void ShowBoard(ListBoard LB, TabKota TK) {
/*KAMUS*/
	Address PF, PL, Pt;
	int i, j, m, n, k, l;
	int npetak, x, y, M, N;
	int length, posnama;
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
						PrintNameOnBoard(PF, TK, x);
						j += x-2;
						PF = Next(PF);
					}
				}
				else if(i == posnama+1) { //Posisi Harga
					if((j%x)== 0) printf("|");
					else {
						if(j > 0 && j < (M-x)) {
							PrintPriceOnBoard(PF, TK, x);
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
						if(j > 0 && j < (M-x))
							PrintOwnerOnBoard(PF, TK, x);
						else
							for(m = 1; m < x; m++) printf(" ");
						j += x-2;
						PF = Next(PF);
					}
				}
				else if(i == posnama+3) { //Posisi Players
					if((j%x) == 0) printf("|");
					else if((j%x) != 0){
						PrintPlayersOnBoard(PF, x);
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
						PrintNameOnBoard(PL, TK, x);
						j += x-2;
					}
					else if(j > (M-x) && j < M) {
						PrintNameOnBoard(PF, TK, x);
						j += x-2;
					}
					else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
					else printf(" ");
				}
				else if((i%y) == posnama+1) { //Posisi Harga
					if(j > 0 && j < x) {
						PrintPriceOnBoard(PL, TK, x);
						j += x-2;
					}
					else if(j > (M-x) && j < M) {
						PrintPriceOnBoard(PF, TK, x);
						j += x-2;
					}
					else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
					else printf(" ");
				}
				else if((i%y) == posnama+2) { //Posisi Milik
					if(j > 0 && j < x) {
						PrintOwnerOnBoard(PL, TK, x);
						j += x-2;
					}
					else if(j > (M-x) && j < M) {
						PrintOwnerOnBoard(PF, TK, x);
						j += x-2;
					}
					else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
					else printf(" ");
				}
				else if((i%y) == posnama+3) { //Posisi Players
					if(j > 0 && j < x) {
						PrintPlayersOnBoard(PL, x);
						j += x-2;
						PL = Next(PL);
					}
					else if(j > (M-x) && j < M) {
						PrintPlayersOnBoard(PF, x);
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
						PrintNameOnBoard(PL, TK, x);
						j += x-2;
						PL = Next(PL);
					}
				}
				else if(i == (N-y)+posnama+1) { //Posisi Harga
					if((j%x)== 0) printf("|");
					else {
						if(j > x && j < (M-x))
							PrintPriceOnBoard(PL, TK, x);
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
						if(j > x && j < (M-x))
							PrintOwnerOnBoard(PL, TK, x);
						else
							for(m = 1; m < x; m++) printf(" ");
						j += x-2;
						PL = Next(PL);
					}
				}
				else if(i == (N-y)+posnama+3) { //Posisi Players
					if((j%x)== 0) printf("|");
					else {
						PrintPlayersOnBoard(PL, x);
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
