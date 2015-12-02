#ifndef BOARD_H
#define BOARD_H
#include "../other/other.h"
#include "../kota/kota.h"
#include "../boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//KONSTANTA
#define Nil NULL
#define ValUndef -999
#define NMax 20

// DEFINISI TIPE
typedef struct {
	int id;
	int type;
} Petak;

typedef struct TElmtList *Address;

typedef struct TElmtList {
	Petak 	info;
	Address 	next;
} ElmtList;

typedef struct {
	Address		first;
} ListBoard;

ListBoard LB;
int jumPetak, jumBlock;

//SELEKTOR
#define First(L) (L).first
#define Next(P) (P)->next
#define Info(P) (P)->info
#define Type(P) (P)->info.type
#define Id(P) (P)->info.id
#define Special(P) (P)->info.special

Kata CNama;

void PrintInfoKota(TabKota TK, int id);
/* prosedur untuk menampilkan info kota berdasarkan id kota */

void PrintInfoAdr(Address p, TabKota TK);
/* prosedur untuk menampilkan info kota berdasarkan address kota */

void PrintInfoBoard(ListBoard LB, TabKota TK);
/* prosedur untuk menampilkan info semua petak di dalam board */

void initBoard(ListBoard *LB, TabKota *TK);
/* prosedur untuk membaca board dari file eksternal */

void PrintNamaPetak(TabKota TK, Address P, int baris, int *length);
/* prosedur untuk menuliskan nama di dalam board */

int SearchKota(Kata K,TabKota TK);
/* mengembalikan id dari kota jika ditemukan, mengembalikan jumlah petak + 1 jika tidak ditemukan */

Address Last(ListBoard L);
/*	I.S. sembarang
	F.S. Mengirim address terakhir dari ListBoard. Jika ListBoard kosong, kembalikan Nil.
*/

boolean IsListEmpty (ListBoard L);
/* Mengirim true jika ListBoard kosong */

void CreateList (ListBoard *L);
/*	I.S. sembarang
	F.S. Terbentuk ListBoard kosong
*/

Address Alokasi (Petak X);
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

void Dealokasi (Address *P);
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/

void InsVLast (ListBoard *L, Petak X);
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen ListBoard di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/

void InsertLast (ListBoard *L, Address P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/

void InsertFirst (ListBoard *L, Address P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/

void DeleteAfter (ListBoard *L, Address *Pdel, Address Prec);
/*	I.S. ListBoard tidak kosong. Prec adalah anggota ListBoard L. Prec bukan elemen terakhir.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen ListBoard yang dihapus
*/

int NbElmt (ListBoard L);
/*	Mengirimkan banyaknya elemen ListBoard; mengirimkan 0 jika ListBoard kosong */

//PROSES TERHADAP ListBoard
void DeleteAll (ListBoard *L);
/*	Delete semua elemen ListBoard dan alamat elemen di-dealokasi
	I.S. : L terdefinisi, boleh kosong
	F.S. : Jika L tidak kosong, semua elemen ListBoard di-delete dan didealokasi
*/

void InversList (ListBoard *L);
/*	I.S. L terdefinisi, boleh kosong
	F.S. Elemen ListBoard L dibalik :
	Elemen terakhir menjadi elemen pertama, dan seterusnya.
	Membalik elemen ListBoard, tanpa melakukan alokasi/dealokasi.
*/

void PecahList (ListBoard *L1, ListBoard *L2, ListBoard L);
/*	I.S. L mungkin kosong
	F.S. Berdasarkan L, dibentuk dua buah ListBoard L1 dan L2
	L tidak berubah : untuk membentuk L1 dan L2 harus alokasi.
	L1 berisi separuh elemen L dan L2 berisi sisa elemen L.
	Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2.
	Jila alokasi gagal, semua elemen yang sudah dialokasikan harus di-dealokasi (bisa L1, L2 atau keduanya)
*/

boolean isPlayerOwnKota(ListBoard LB, TabKota TK);
/* mengembalikan true jika player memiliki minimal 1 kota, false jika tidak */

void hostnama(Kata *NamaKota, ListBoard LB, TabKota TK);
/* prosedur untuk menginput perintah untuk World Cup */

void travelnama(Kata *NamaKota, ListBoard LB, TabKota TK);
/* prosedur untuk menginput perintah untuk World Travel */

void boardWorldCup(ListBoard LB, TabKota *TK);
/* prosedur untuk menentukan tindakan player saat sampai di board World Cup */

void boardWorldTravel(ListBoard LB, TabKota TK);
/* prosedur untuk menentukan tindakan player saat sampai di board World Travel */

boolean IsPlayerOnBoard(AddressPl P, int pos);
/* memngembalikan true jika Player P berada di posisi petak dengan id pos, false jika tidak */

int PlayersOnBoard(int pos);
/* mengembalikan jumlah pemain yang ada di petak dengan id pos */

void PrintNameOnBoard(Address P, TabKota TK, int x);
/* prosedur untuk menuliskan nama petak pada board */

void PrintPriceOnBoard(Address P, TabKota TK, int x);
/* prosedur untuk menuliskan harga pada board */

void PrintOwnerOnBoard(Address P, TabKota TK, int x);
/* prosedur untuk menuliskan owner dan level kota pada board */

void PrintPlayersOnBoard(Address P, int x);
/* prosedur untuk menuliskan player pada board */

void ShowBoard(ListBoard LB, TabKota TK);
/* prosedur untuk menampilkan board */

#endif
