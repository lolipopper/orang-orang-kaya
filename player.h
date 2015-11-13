#ifndef PLAYER_H
#define PLAYER_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define Nil NULL

//DEFINISI TIPE
typedef struct {
	int position;
	long long money;
	int kekayaan;
	int nFreePrison;
	int nFreeTax;
	int nProtect;
	int nOffLight;
	char playerId;
	boolean jail;
} Player;

typedef struct TElmtList *Address;

typedef struct TElmtList {
	Player  	info;
	Address 	next;
} ElmtList;

typedef struct {
	Address		first;
} ListPlayer;

//SELEKTOR
#define First(L) (L).first
#define Next(P) (P)->next
#define Position(P) (P).position
#define Money(P) (P).money
#define Kekayaan(P) (P).kekayaan
#define CardFreePrison(P) (P).nFreePrison
#define CardFreeTax(P) (P).nFreeTax
#define CardProtect(P) (P).nProtect
#define CardOff(P) (P).nOffLight
#define PlayerId(P) (P).playerId
#define Jail(P) (P).jail

#endif
