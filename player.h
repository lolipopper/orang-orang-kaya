#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

// KONSTANTA
#define Nil NULL
#define Bonus 500

// DEFINISI TIPE
typedef struct {
	int position;
	long long money;
	long long kekayaan;
	int nFreePrison;
	int nFreeTax;
	int nProtect;
	int nOffLight;
	char playerId;
	boolean jail;
	int movWorldTravel;
} Player;

typedef struct TElmtListPl *AddressPl;

typedef struct TElmtListPl {
	Player  	info;
	AddressPl 	next;
} ElmtListPl;

typedef struct {
	AddressPl		first;
} ListPlayer;

// SELEKTOR
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
#define MovWorldTravel(P) (P)->info.movWorldTravel

// KAMUS GLOBAL
ListPlayer Turn;
AddressPl PTurn;
boolean rolled;
boolean turnAwal;
int jumlahPemain;
int idWorldCup[4+1];

AddressPl AlokasiPl (Player X);
/* melakukan alokasi player */

void DealokasiPl (AddressPl *P);
/* melakukan dealokasi player */

void ConsPlayer(Player *P, int position, long long money, int nFreeTax, int nFreePrison, int nOffLight, int nProtect, char playerId, int kekayaan, boolean jail, int movworldtravel);
/* prosedur untuk menentukan info dari player */

void InitPlayer(Player *P, char playerId);
/* prosedur untuk menginisialisasi kondisi awal info player */

void InitNPlayer();
/* proseudr untuk menentukan jumlah pemain */

void InitNumPlayer(int n);

void DeleteAllPlayer ();

AddressPl SearchPl(char id);
/* melakukan search di List Turn Player dengan playerId = id */

void deletePlayer(ListPlayer *L,Player P);

void DeleteAllOwnedBuildings(TabKota *TK,Player P);	//ke board/kota

void removeOffered(TabKota *TK,Player P);			//ke command

boolean isWinTour(TabKota Kota);					//command?

boolean isWinBlock(TabKota Kota);					//command?

#endif
