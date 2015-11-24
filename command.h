#ifndef ACTION_H
#define ACTION_H

#include "kota.h"
#include "player.h"

void MovPlayer(TabKota TK, ListBoard LB);
/* prosedur gerak untuk player */

void MoveNPetak(TabKota TK, ListBoard LB, int N);
/* memindahkan player sesuai dengan dadu yang di roll oleh player tersebut */

void EndTurn();
/* mengakhiri turn player tertentu */

void ShowMoney();
/* menunjukkan jumlah uang player tertentu */

void PrintPos(TabKota TK, ListBoard LB);
/* menunjukkan posisi player tertentu pada board */

void buy(Player *P, Kota *K);
/* prosedur untuk melakukan pembelian kota */

void payRent(Player *P, Kota K);
/* prosedur untuk membayar sewa ke player lain */

void Upgrade(ListBoard LB, TabKota *TK);
/* prosedur untuk mengupgrade bangunan */

void infoKota(TabKota TK, int id);
/* prosedur untuk menampilkan info kota */

#endif
