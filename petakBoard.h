#ifndef PETAKBOARD_H
#define PETAKBOARD_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define Nil NULL

//DEFINISI TIPE
typedef struct {
	int id;
	boolean special;
	int type;
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
#define type(P) (P)->info.type
#define Id(P) (P)->info.id
#define Special(P) (P)->info.special

#endif

