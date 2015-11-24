#include "petakBoard.h"

boolean IsListEmpty (ListBoard L)
/* Mengirim true jika ListBoard kosong */
{
    if (First(L) == Nil)
        return true;
    else
        return false;
}

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

// PENCARIAN SEBUAH ELEMEN ListBoard

//PRIMITIF BERDASARKAN ALAMAT
//PENAMBAHAN ELEMEN BERDASARKAN ALAMAT
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

void InsertAfter (ListBoard *L, Address P, Address Prec)
/*	I.S. Prec pastilah elemen ListBoard dan bukan elemen terakhir, P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
{
    Next(P) = Next(Next(Prec));
    Next(Prec) = P;
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

//PENGHAPUSAN SEBUAH ELEMEN
void DeleteFirst (ListBoard *L, Address *P)
/*	I.S. ListBoard tidak kosong
	F.S. P adalah alamat elemen pertama ListBoard sebelum penghapusan
	Elemen ListBoard berkurang satu (mungkin menjadi kosong)
	First element yang baru adalah suksesor elemen pertama yang lama
*/
{
    *P = First(*L);
    if (Next(First(*L)) == First(*L)){
        First(*L) = Nil;
    }else{
        Next(Last(*L)) = Next(*P);
        First(*L) = Next(*P);
    }

}

void DeleteLast (ListBoard *L, Address *P)
/*	I.S. ListBoard tidak kosong
	F.S. P adalah alamat elemen terakhir ListBoard sebelum penghapusan
	Elemen ListBoard berkurang satu (mungkin menjadi kosong)
	Last element baru adalah predesesor elemen terakhir yang lama, jika ada
*/
{
    Address prec;
    if (Next(First(*L)) == First(*L)){
        *P = First(*L);
        First(*L) = Nil;
    }else{
        prec = First(*L);
        while (Next(prec) != Last(*L))
        {
            prec= Next(prec);
        }
        *P = Last(*L);
        Next(prec) = First(*L);
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

//PENAMBAHAN ELEMEN
void InsVFirst (ListBoard *L, Petak X)
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen pertama L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen pertama dengan
	nilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
{
    Address p;
    p = Alokasi(X);
    if (p != Nil){
        InsertFirst(L,p);
    }
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
//PENGHAPUSAN ELEMEN
void DelVFirst (ListBoard *L, Petak *X)
/*	I.S. ListBoard L tidak kosong
	F.S. Elemen pertama ListBoard dihapus : nilai info disimpan pada X
	dan alamat elemen pertama di-dealokasi
*/
{
    Address p;
    DeleteFirst(L,&p);
    *X = Info(p);
    Dealokasi(&p);
}

void DelVLast (ListBoard *L, Petak *X)
/*	I.S. ListBoard tidak kosong
	F.S. Elemen terakhir ListBoard dihapus : nilai info disimpan pada X
	dan alamat elemen terakhir di-dealokasi
*/
{
    Address p;
    DeleteLast(L,&p);
    *X = Info(p);
    Dealokasi(&p);
}

//PROSES SEMUA ELEMEN ListBoard
void PrintInfo (ListBoard L)
/*	I.S. ListBoard mungkin kosong
	F.S. Jika ListBoard tidak kosong,
	Semua info yg disimpan pada elemen ListBoard diprint dengan format [elemen-1, elemen-2, elemen-3, ...]
	Jika ListBoard kosong, hanya menuliskan "[]"
*/
{
    Address p;
    printf("[");
    if (IsListEmpty(L) == true){
        printf("]\n");
    }else{
        //printf("%d\n",Info(p).type);
        p = First(L);
        while (p != Last(L))
        {
            printf("%d, ",Info(p).type);
            p = Next(p);
        }
        printf("%d]\n", Info(p).type);
    }
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

void CopyList (ListBoard L1, ListBoard *L2)
/*	I.S. L1 terdefinisi, L2 sembarang. F.S. L2 = L1
	L1 dan L2 "menunjuk" kepada ListBoard yang sama.
	Tidak ada alokasi/dealokasi elemen baru.
*/
{
    First(*L2) = First(L1);
}

void CpAlokList (ListBoard Lin, ListBoard *Lout)
/*	I.S. Lout sembarang, Lin terdefinisi.
	F.S. Jika semua alokasi berhasil, maka Lout berisi hasil copy Lin
	Jika ada alokasi yang gagal, maka Lout = Nil dan semua elemen yang terlanjur
	dialokasi, didealokasi
*/
{
    Address p,temp;
    boolean valid;
    valid = true;
    p = First(Lin);
    CreateList(Lout);
    if (IsListEmpty(Lin) == false){
        while ((p!=Last(Lin))&&(valid == true))
        {
            temp = Alokasi(Info(p));
            if (temp == Nil){
                DeleteAll(Lout);
                valid = false;
            }else{
                InsertLast(Lout,temp);
                p = Next(p);
            }
        }
        if (valid == true){
            temp = Alokasi(Info(p));
            if (temp == Nil){
                DeleteAll(Lout);
                valid = false;
            }else{
                InsertLast(Lout,temp);
            }
        }
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

ListBoard FInversList (ListBoard L)
/*	Mengirimkan ListBoard baru, hasil invers dari L dengan menyalin semua elemen ListBoard.
	Alokasi mungkin gagal. Jika alokasi gagal, hasilnya ListBoard kosong dan semua elemen
	yang terlanjur di-alokasi, harus didealokasi.
*/
{
    ListBoard temp;
    Address p,tempadr;
    CreateList(&temp);
    boolean valid;
    int nbelmt,i;

    if (IsListEmpty(L) == false)
    {
        i = 1;
        CpAlokList(L,&temp);
        nbelmt = NbElmt(L); valid = true;
        while((i<=nbelmt-1) && (valid == true))
        {
            DeleteLast(&temp,&p);
            tempadr = Alokasi(Info(p));
            if (p==Nil){
                DeleteAll(&temp);
                valid = false;
            }else{
                InsertFirst(&temp,tempadr);
                PrintInfo(temp);
                i++;
            }
        }
    }
    return temp;
}

ListBoard FCopyList (ListBoard L)
/*	Mengirimkan ListBoard yang merupakan salinan L dengan melakukan alokasi elemen baru.
	Jika ada alokasi gagal, hasilnya ListBoard kosong dan semua elemen yang terlanjur dialokasi,
	harus didealokasi.
*/
{
    ListBoard temp;
    Address p,tempadr;
    CreateList(&temp);
    boolean valid;

    if (IsListEmpty(L) == false){
        valid = true;
        p = First(L);
        while ((p!= Last(L)) && (valid == true))
        {
            tempadr = Alokasi(Info(p));
            if (tempadr == Nil){
                DeleteAll(&temp);
                valid = false;
            }else{
                InsertLast(&temp,tempadr);
                p = Next(p);
            }
        }
        tempadr = Alokasi(Info(p));
        if (tempadr == Nil){
            DeleteAll(&temp);
        }else{
            InsertLast(&temp,tempadr);
        }
    }
    return temp;
}

void Concat (ListBoard L1, ListBoard L2, ListBoard *L3)
/*	I.S. L1 dan L2 terdefinisi, boleh kosong.
	F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 dan L2
	Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi L1 dan L2.
	Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi harus didealokasi
	dan L3 = Nil.
	Konkatenasi dua buah ListBoard : L1 dan L2 menghasilkan L3 yang "baru".
	Elemen L3 adalah hasil alokasi elemen yang "baru".
	Jika ada alokasi yang gagal, maka L3 harus bernilai Nil dan semua elemen yang
	pernah dialokasi harus didealokasi.
*/
{
    Address p,temp;
    boolean valid;
    CreateList(L3);
    p = First(L1);
    valid = true;

    while ((p != Last(L1)) && (valid == true))
    {
        temp = Alokasi(Info(p));
        if (temp == Nil){
            DeleteAll(L3);
            valid = false;
        }else{
            InsertLast(L3,temp);
            p = Next(p);
        }
    }
    if (valid == true){
        temp = Alokasi(Info(p));
        if (temp == Nil){
            DeleteAll(L3);
            valid = false;
        }else{
            InsertLast(L3,temp);
            p = Next(p);
        }
    }

    p = First(L2);
    while ((p != Last(L2)) && (valid == true))
    {
        temp = Alokasi(Info(p));
        if (temp == Nil){
            DeleteAll(L3);
            valid = false;
        }else{
            InsertLast(L3,temp);
            p = Next(p);
        }
    }
    if (valid == true){
        temp = Alokasi(Info(p));
        if (temp == Nil){
            DeleteAll(L3);
            valid = false;
        }else{
            InsertLast(L3,temp);
            p = Next(p);
        }
    }
}

void Concat1 (ListBoard *L1,  ListBoard *L2, ListBoard *L3)
/*	I.S. L1 dan L2 sembarang
	F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 dan L2
	Konkatenasi dua buah ListBoard: L1 dan L2 menghasilkan L3 yang baru (dengan elemen ListBoard L1 dan L2).
	L1 dan L2 menjadi ListBoard kosong.
	Tidak ada alokasi/dealokasi pada prosedur ini.
*/
{
    First(*L3) = First(*L1);
    Next(Last(*L2)) = First(*L1);
    Next(Last(*L1)) = First(*L2);
    First(*L1) = Nil;
    First(*L2) = Nil;
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

void PrintInfoKota(TabKota TK, int id)
{
    printf("Nama     : %s",NamaKota(TK,id));
    printf("Price    : %d\n",Price(TK,id));
    printf("Rekreasi : %d\n",isRekreasi(TK,id));
    printf("Block    : %d\n",Block(TK,id));
    printf("Level    : %d\n",Level(TK,id));
    printf("Owner    : %d\n",Owner(TK,id));
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

void ShowBoard(ListBoard LB, TabKota TK) {
    /*KAMUS*/
    Address PF, PL, Pt;
    int i, j, m, n;
    int npetak, x, y, M, N;
    int length, harga, posnama;
    ListBoard L1, L2;

/*ALGORITMA*/
    /*INISIALISASI*/
    npetak = 9;//Jumlah Petak
    x = 10 + 1; //Ukuran Petak
    y = 5;     //Ukuran Petak
    M = x*npetak; //Panjang Board
    N = y*npetak; //Lebar Board
    posnama = 1; //posisi baris nama dalam petak

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
                if(i == posnama) { //Posisi Nama
					if((j%x) == 0) printf("|");
                    else if((j%x) != 0){
                        printf(" ");
                        PrintNamaPetak(TK, PF, 1, &length);
                        for(m = 0; m < (x-(length+2)); m++) printf(" ");
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
                                harga = Price(TK, Id(PF))/1000;
                                printf("%dK", harga);
                                if(harga < 100)
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
                else {
                    if((j%x)== 0) printf("|");
                    else printf(" ");
                }
            }
            else if(i > y && i < (N-y) && (i%y) != 0) {
                if((i%y) == posnama) {
                    if(j > 0 && j < x) {
                        for(m = 0; m < 1; m++) printf(" ");
                        PrintNamaPetak(TK, PL, 1, &length);
                        for(m = 0; m < (x-length-2); m++) printf(" ");
                        j += x-2;
                    }
                    else if(j > (M-x) && j < M) {
                        for(m = 0; m < 1; m++) printf(" ");
                        PrintNamaPetak(TK, PF, 1, &length);
                        for(m = 0; m < (x-length-2); m++) printf(" ");
                        j += x-2;
                    }
                    else if(j == 0 || j == x || j == (M-x) || j == M) printf("|");
                    else printf(" ");
                }
                else if((i%y) == posnama+1) {
                    if(j > 0 && j < x) {
                        if(Type(PL) == 1) {
                            for(m = 0; m < 3; m++) printf(" ");
                            harga = Price(TK, Id(PL))/1000;
                            printf("%dK", harga);
                            if(harga < 100)
                                for(m = 0; m < x-3-4; m++) printf(" ");
                            else
                                for(m = 0; m < x-4-4; m++) printf(" ");
                        }
                        else {
                            for(m = 1; m < x; m++) printf(" ");
                        }
                        j += x-2;
                        PL = Next(PL);
                    }
                    else if(j > (M-x) && j < M) {
                        if(Type(PF) == 1) {
                            for(m = 0; m < 3; m++) printf(" ");
                            harga = Price(TK, Id(PF))/1000;
                            printf("%dK", harga);
                            if(harga < 100)
                                for(m = 0; m < x-3-4; m++) printf(" ");
                            else
                                for(m = 0; m < x-4-4; m++) printf(" ");
                            }
                            else {
                                for(m = 1; m < x; m++) printf(" ");
                            }
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
                if(i == (N-y)+posnama) { //Posisi Nama
					if((j%x)== 0) printf("|");
                    else {
                        printf("  ");
                        PrintNamaPetak(TK, PL, 1, &length);
                        for(m = 1; m < (x-length-2); m++) printf(" ");
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
                                harga = Price(TK, Id(PL))/1000;
                                printf("%dK", harga);
                                if(harga < 100)
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
                else {
                    if((j%x)== 0) printf("|");
                    else printf(" ");
                }
            }
            j++;
        }
        printf("\n");
        if(i == posnama) PF = First(L1);
        if(i == (N-y)+posnama) PL = Pt;
    }
}

Address SearchKota(ListBoard LB, TabKota TK, Kata NamaKota)
{
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
        return Nil;
}

void initBoard(ListBoard *LB,TabKota *TK)
{
    FILE *fiboard;
    Address p;
    int i;
	Petak ipt;
	int dummy;

	i=1;
    p = First(*LB);
	fiboard = fopen("board.txt","r");
	fscanf(fiboard,"%d\n", &ipt.type);
	CreateList(LB);
    while (ipt.type != ValUndef)
    {
        ipt.id = i;
        InsVLast(LB,ipt);
        //printf("\n");
        //printf("First= %d\n",Info(First(*LB)).type);
        //printf("IsEmpty = %d\n",IsListEmpty(*LB));
        //printf("type: %d\n",ipt.type);
        //printf("id  : %d\n",ipt.id);
        if (ipt.type == 1){
            //printf("masukn\n");
            fgets(TK->TK[i].name.TabKata, NMax, fiboard);
            //printf("nama : %s",TK->TK[i].name);
            fscanf(fiboard,"%d\n",&(TK->TK[i].price));
            //printf("harga: %d\n",TK->TK[i].price);
            fscanf(fiboard,"%d\n",&(TK->TK[i].rekreasi));
            //printf("rekreasi: %d\n",TK->TK[i].rekreasi);
            fscanf(fiboard,"%d\n",&(TK->TK[i].block));
            //printf("block: %d\n",TK->TK[i].block);
            fscanf(fiboard,"%d\n",&(TK->TK[i].level));
            //printf("level: %d\n",Level(*TK,i));
            fscanf(fiboard,"%d\n",&(TK->TK[i].owner));
            //printf("owner: %d\n",Owner(*TK,i));
            fscanf(fiboard,"%d\n",&(TK->TK[i].name.Length));
        }
        //fscanf(fiboard,"\n");
        i++;
        //scanf("%d",&dummy);
        fscanf(fiboard,"%d\n", &ipt.type);
    }
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

void Save (ListBoard LB, TabKota TK)
{
    FILE *fosave;
    Address p = First(LB);

    fosave = fopen("save_file.txt","w");

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
    fprintf(fosave, "%d",ValUndef);
    fclose(fosave);
}

void Load (ListBoard *LB,TabKota *TK)
{
    FILE *fisave;
    Address p;
    int i;
	Petak ipt;
	int dummy;

	i=1;
    p = First(*LB);
	fisave = fopen("save_file.txt","r");
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
	fclose(fisave);
}
