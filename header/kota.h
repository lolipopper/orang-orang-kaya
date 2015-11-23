#ifndef KOTA_H
#define KOTA_H
#include "boolean.h"
#include "mesinkata.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define IdxMax 32
#define IdxMin 1

//DEFINISI TIPE
typedef int IdxType;
typedef struct {
	Kata name;
	long price;
	boolean rekreasi;
	int block;
	int level;
	Player owner;
	boolean LightOff;
} Kota;

typedef struct {
	ElType TK[IdxMax+1];
} TabKota;

//SELEKTOR
#define NamaKota(Kota) (Kota).name
#define Price(Kota) (Kota).price
#define IsRekreasi(Kota) (Kota).rekreasi
#define Block(Kota) (Kota).block
#define Level(Kota) (Kota).level
#define Owner(Kota) (Kota).owner
#define IsLightOff(Kota) (Kota).LightOff
#define LengthNama(Kota) (Kota).name.Length

void buy(Player *P, Kota *K);
void payRent(Player *P,Kota K);
void upgrade(Kota *K);
int UpgradePrice(Kota K);

#endif
