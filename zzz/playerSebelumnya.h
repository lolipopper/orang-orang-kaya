#ifndef PLAYER_H
#define PLAYER_H
#include "boolean.h"
#include "other.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

//KONSTANTA
#define Nil NULL
#define Bonus 20000

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

typedef struct TElmtListPl *AddressPl;

typedef struct TElmtListPl {
	Player  	info;
	AddressPl 	next;
} ElmtListPl;

typedef struct {
	AddressPl		first;
} ListPlayer;

//SELEKTOR
#define Info(P) (P)->info
#define First(L) (L).first
#define Next(P) (P)->next
#define Position(P) (P)->info.position
#define Money(P) (P)->info.money
#define Kekayaan(P) (P)->info.kekayaan
#define CardFreePrison(P) (P)->info.nFreePrison
#define CardFreeTax(P) (P)->info.nFreeTax
#define CardProtect(P) (P)->info.nProtect
#define CardOff(P) (P)->info.nOffLight
#define PlayerId(P) (P)->info.playerId
#define Jail(P) (P)->info.jail

//KAMUS GLOBAL
ListPlayer Turn;
AddressPl PTurn;
boolean rolled;

//CONSTRUCTOR
AddressPl AlokasiPl (Player X);

void ConsPlayer(Player *P,int position,long long money, int nFreeTax, int nFreePrison,int nOffLight,int nProtect,char playerId,int kekayaan);

//DESTRUCTOR
void DealokasiPl (AddressPl *P);

//INITIALIZE
void InitPlayer(Player *P,char playerId);

void InitNPlayer();
//Inisialisasi banyak player serta menginisialisasi List Turn

//SEARCH
AddressPl SearchPl(char id);
//Search di List Turn Player dengan playerId = id

#endif
