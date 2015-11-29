#ifndef KOTA_H
#define KOTA_H

#include "other.h"
#include "player.h"

// KONSTANTA
#define IdxMax 32
#define IdxMin 1

// DEFINISI TIPE
typedef struct {
	boolean isWCup;
	char who;
} WCup;

typedef int IdxType;
typedef struct {
	Kata name;
	long price;
	boolean rekreasi;
	int block;
	int level;
	char owner;
	boolean LightOff;
	WCup WorldCup;
	boolean isOffered;
} Kota;

typedef struct {
	Kota TK[IdxMax+1];
} TabKota;

int jumRek;

// SELEKTOR
#define NamaKota(Kota,i) (Kota).TK[(i)].name
#define Price(Kota,i) (Kota).TK[(i)].price
#define isRekreasi(Kota,i) (Kota).TK[(i)].rekreasi
#define Block(Kota,i) (Kota).TK[(i)].block
#define Level(Kota,i) (Kota).TK[(i)].level
#define Owner(Kota,i) (Kota).TK[(i)].owner
#define LightOff(Kota,i) (Kota).TK[(i)].LightOff
#define isWorldCup(Kota,i) (Kota).TK[(i)].WorldCup.isWCup
#define whoWorldCup(Kota,i) (Kota).TK[(i)].WorldCup.who
#define isOffered(Kota,i) (Kota).TK[(i)].isOffered
#define City(Kota,i) (Kota).TK[(i)]
long long priceCity(Kota K);
/* mengembalikan harga sewa kota */

long long priceUpgrade(Kota K);
/* mengembalikan harga upgrade kota */

long long priceSell (Kota K);

void infoCity(Kata K, TabKota TK);
/* prosedur untuk menampilkan info dari kota tertentu */

void DeleteAllOwnedBuildings(TabKota *TK,Player P);	//ke board/kota

#endif
