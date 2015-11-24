#ifndef ACTION_H
#define ACTION_H

#include "kota.h"
#include "player.h"

//ACTION
void buy(Player *P, Kota *K);

void payRent(Player *P,Kota K);

void Upgrade(ListBoard LB, TabKota *TK);

void ShowMoney();

void MoveNPetak(TabKota TK, ListBoard LB, int N);
//move sebanyak N petak yang telah ditentukan

void MovPlayer(TabKota TK, ListBoard LB);
//Gerakin player dengan akses id player

void EndTurn();

void PrintPos(TabKota TK, ListBoard LB);
//print posisi player yang sedang mendapat giliran

//FUNCTION
boolean TourMono(TabKota TK, ListBoard LB);
//true jika semua rekreasi dimiliki oleh satu orang

#endif

