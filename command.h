#ifndef COMMAND_H
#define COMMAND_H

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

void buy();
/* prosedur untuk melakukan pembelian kota */

#endif
