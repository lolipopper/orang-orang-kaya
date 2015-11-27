#ifndef COMMAND_H
#define COMMAND_H

#include "kota.h"
#include "player.h"
#include "board.h"

void MovPlayer(TabKota *TK, ListBoard *LB);
/* prosedur gerak untuk player */

void MoveNPetak(TabKota *TK, ListBoard *LB, int N);
/* memindahkan player sesuai dengan dadu yang di roll oleh player tersebut */

void EndTurn();
/* mengakhiri turn player tertentu */

void ShowMoney();
/* menunjukkan jumlah uang player tertentu */

void PrintPos(TabKota TK, ListBoard LB);
/* menunjukkan posisi player tertentu pada board */

void buy(TabKota *Kota, ListBoard *LB);
/* prosedur untuk melakukan pembelian kota */

void upgrade(TabKota *Kota, ListBoard *LB);
/* prosedur untuk melakukan upgrade pada kota */

void payRent(ListBoard *LB, TabKota *Kota);
/* prosedur untuk membayar sewa kota */

void showLeaderBoard();
/* prosedur untuk menampilkan urutan kekayaan player beserta kekayaannya */

void printKekayaan();
/* prosedur untuk menampilkan uang dan kekayaan dari masing" player */

void quicksort(long long x[3], char y[3], int first, int last);
/* prosedur untuk sorting array dengan metode quicksort */

#endif
