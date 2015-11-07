#ifndef KOTA_H
#define KOTA_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define IdxMax 32
#define IdxMin 1

typedef int IdxType;
typedef struct {
	char *name;
	long price;
	boolean rekreasi;
	int block;
	int level;
	char owner;
	boolean blackOut;
	boolean worldCup;
} ElType;

typedef struct {
	ElType TK[IdxMax+1];
} TabKota

#endif
