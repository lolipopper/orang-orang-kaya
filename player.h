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
	int nFreeTax;
	int nFreePrison;
	int nOffLight;
	int nProtect;
	char playerId;
	int kekayaan;
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
#define Position(P) (P)->info.position
#define PlayerId(P) (P)->info.playerId
#define Money(P) (P)->info.money
#define Kekayaan(P) (P)->info.kekayaan
#define CardFreeTax(P) (P)->info.nFreeTax
#define CardFreePrison(P) (P)->info.nFreePrison
#define CardProtect(P) (P)->info.nProtect
#define CardOff(P) (P)->info.nOffLight

//Constructor
void ConsPlayer(Player *P,int position,long long money, int nFreeTax, int nFreePrison,int nOffLight,int nProtect,char playerId,int kekayaan);

//Initialize
void InitPlayer(Player *P,char playerId);
#endif


