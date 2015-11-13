#ifndef PETAKBOARD_H
#define PETAKBOARD_H
#include "mesinkata.h"
#include "kota.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define Nil NULL
#define ValUndef -999

//DEFINISI TIPE
typedef struct {
	int id;
	int type;
	boolean special;
} Infotype;

typedef struct TElmtList *Address;

typedef struct TElmtList {
	Infotype 	info;
	Address 	next;
} ElmtList;

typedef struct {
	Address		first;
} ListBoard;

//SELEKTOR
#define First(L) (L).first
#define Next(P) (P)->next
#define Info(P) (P)->info
#define Type(P) (P)->info.type
#define Id(P) (P)->info.id
#define Special(P) (P)->info.special

Kata CNama;

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

Address Alokasi (Infotype X);
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

// PENCARIAN SEBUAH ELEMEN ListBoard

//PENAMBAHAN ELEMEN
void InsVFirst (ListBoard *L, Infotype X);
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen pertama L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen pertama dengan
	nilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/

void InsVLast (ListBoard *L, Infotype X);
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen ListBoard di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/

//PENGHAPUSAN ELEMEN
void DelVFirst (ListBoard *L, Infotype *X);
/*	I.S. ListBoard L tidak kosong
	F.S. Elemen pertama ListBoard dihapus : nilai info disimpan pada X
	dan alamat elemen pertama di-dealokasi
*/

void DelVLast (ListBoard *L, Infotype *X);
/*	I.S. ListBoard tidak kosong
	F.S. Elemen terakhir ListBoard dihapus : nilai info disimpan pada X
	dan alamat elemen terakhir di-dealokasi
*/

//PRIMITIF BERDASARKAN ALAMAT
//PENAMBAHAN ELEMEN BERDASARKAN ALAMAT
void InsertFirst (ListBoard *L, Address P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/

void InsertAfter (ListBoard *L, Address P, Address Prec);
/*	I.S. Prec pastilah elemen ListBoard dan bukan elemen terakhir, P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/

void InsertLast (ListBoard *L, Address P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/

//PENGHAPUSAN SEBUAH ELEMEN
void DeleteFirst (ListBoard *L, Address *P);
/*	I.S. ListBoard tidak kosong
	F.S. P adalah alamat elemen pertama ListBoard sebelum penghapusan
	Elemen ListBoard berkurang satu (mungkin menjadi kosong)
	First element yang baru adalah suksesor elemen pertama yang lama
*/

void DeleteLast (ListBoard *L, Address *P);
/*	I.S. ListBoard tidak kosong
	F.S. P adalah alamat elemen terakhir ListBoard sebelum penghapusan
	Elemen ListBoard berkurang satu (mungkin menjadi kosong)
	Last element baru adalah predesesor elemen terakhir yang lama, jika ada
*/

void DeleteAfter (ListBoard *L, Address *Pdel, Address Prec);
/*	I.S. ListBoard tidak kosong. Prec adalah anggota ListBoard L. Prec bukan elemen terakhir.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen ListBoard yang dihapus
*/

//PROSES SEMUA ELEMEN ListBoard
void PrintInfo (ListBoard L);
/*	I.S. ListBoard mungkin kosong
	F.S. Jika ListBoard tidak kosong,
	Semua info yg disimpan pada elemen ListBoard diprint dengan format [elemen-1, elemen-2, elemen-3, ...]
	Jika ListBoard kosong, hanya menuliskan "[]"
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

ListBoard FInversList (ListBoard L);
/*	Mengirimkan ListBoard baru, hasil invers dari L dengan menyalin semua elemen ListBoard.
	Alokasi mungkin gagal. Jika alokasi gagal, hasilnya ListBoard kosong dan semua elemen
	yang terlanjur di-alokasi, harus didealokasi.
*/

void CopyList (ListBoard L1, ListBoard *L2);
/*	I.S. L1 terdefinisi, L2 sembarang. F.S. L2 = L1
	L1 dan L2 "menunjuk" kepada ListBoard yang sama.
	Tidak ada alokasi/dealokasi elemen baru.
*/

ListBoard FCopyList (ListBoard L);
/*	Mengirimkan ListBoard yang merupakan salinan L dengan melakukan alokasi elemen baru.
	Jika ada alokasi gagal, hasilnya ListBoard kosong dan semua elemen yang terlanjur dialokasi,
	harus didealokasi.
*/

void CpAlokList (ListBoard Lin, ListBoard *Lout);
/*	I.S. Lout sembarang, Lin terdefinisi.
	F.S. Jika semua alokasi berhasil, maka Lout berisi hasil copy Lin
	Jika ada alokasi yang gagal, maka Lout = Nil dan semua elemen yang terlanjur
	dialokasi, didealokasi
*/

void Concat (ListBoard L1, ListBoard L2, ListBoard *L3);
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

void Concat1 (ListBoard *L1,  ListBoard *L2, ListBoard *L3);
/*	I.S. L1 dan L2 sembarang
	F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 dan L2
	Konkatenasi dua buah ListBoard: L1 dan L2 menghasilkan L3 yang baru (dengan elemen ListBoard L1 dan L2).
	L1 dan L2 menjadi ListBoard kosong.
	Tidak ada alokasi/dealokasi pada prosedur ini.
*/

void PecahList (ListBoard *L1, ListBoard *L2, ListBoard L);
/*	I.S. L mungkin kosong
	F.S. Berdasarkan L, dibentuk dua buah ListBoard L1 dan L2
	L tidak berubah : untuk membentuk L1 dan L2 harus alokasi.
	L1 berisi separuh elemen L dan L2 berisi sisa elemen L.
	Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2.
	Jila alokasi gagal, semua elemen yang sudah dialokasikan harus di-dealokasi (bisa L1, L2 atau keduanya)
*/

void PrintInfoKota(TabKota Kota, int id);

void PrintInfoAdr(Address p, TabKota Kota);

void PrintInfoBoard(ListBoard LB, TabKota Kota);

void initBoard(ListBoard *LB, TabKota *TK);

void PrintNamaPetak(TabKota Kota, Address P, int baris, int *length);

void ShowBoard(ListBoard LB, TabKota Kota);

Address SearchKota(ListBoard LB, TabKota Kota, Kata NamaKota);

#endif

