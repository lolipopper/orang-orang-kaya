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
            fscanf(fiboard,"%c\n",&(TK->TK[i].owner));
            fscanf(fiboard,"%d\n",&(TK->TK[i].LightOff));
            fscanf(fiboard,"%d\n",&(TK->TK[i].WorldCup.isWCup));
            fscanf(fiboard,"%c\n",&(TK->TK[i].WorldCup.who));
            //printf("owner: %d\n",Owner(*TK,i));
            fscanf(fiboard,"%d\n",&(TK->TK[i].name.Length));
            isOffered(*TK,i) = false;
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
