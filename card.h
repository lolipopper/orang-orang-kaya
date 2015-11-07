#ifndef CARD_H
#define CARD_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define IdxMax 25
#define IdxMin 1

typedef int IdxType;
typedef struct {
	long value;
	char type;
} ElType;

typedef struct {
	ElType TK[IdxMax+1];
} TabCard


#endif

