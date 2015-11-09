#ifndef KOTA_H
#define KOTA_H
#include "boolean.h"
#include "mesinkata.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define IdxMax 32
#define IdxMin 1

typedef int IdxType;
typedef struct {
	Kata name;
	long price;
	boolean rekreasi;
	int block;
	int level;
	char owner;
} ElType;

typedef struct {
	ElType TK[IdxMax+1];
} TabKota;

#define Price(Kota,i) (Kota).TK[(i)].price
#define NamaKota(Kota,i) (Kota).TK[(i)].name
#define isRekreasi(Kota,i) (Kota).TK[(i)].rekreasi
#define Block(Kota,i) (Kota).TK[(i)].block
#define Level(Kota,i) (Kota).TK[(i)].level
#define Owner(Kota,i) (Kota).TK[(i)].owner

#endif
