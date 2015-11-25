#ifndef KOTA_H
#define KOTA_H

#include "other.h"

// KONSTANTA
#define IdxMax 32
#define IdxMin 1

// DEFINISI TIPE
typedef int IdxType;
typedef struct {
	Kata name;
	long price;
	boolean rekreasi;
	int block;
	int level;
	char owner;
	boolean LightOff;
} Kota;

typedef struct {
	Kota TK[IdxMax+1];
} TabKota;

// SELEKTOR
#define NamaKota(Kota,i) (Kota).TK[(i)].name
#define Price(Kota,i) (Kota).TK[(i)].price
#define isRekreasi(Kota,i) (Kota).TK[(i)].rekreasi
#define Block(Kota,i) (Kota).TK[(i)].block
#define Level(Kota,i) (Kota).TK[(i)].level
#define Owner(Kota,i) (Kota).TK[(i)].owner
#define LightOff(Kota,i) (Kota).TK[(i)].owner

long long priceCity(Kota K);
/* mengembalikan harga sewa kota */

long long priceUpgrade(Kota K);
/* mengembalikan harga upgrade kota */

#endif
