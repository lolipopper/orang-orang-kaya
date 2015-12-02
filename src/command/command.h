#ifndef COMMAND_H
#define COMMAND_H

#include "../kota/kota.h"
#include "../board/board.h"
#include "../player/player.h"
#include "../chance/chance.h"

boolean buyupgrade;

void MovPlayer(TabKota *TK, ListBoard *LB);
/* prosedur gerak untuk player */

void MoveNPetak(TabKota *TK, ListBoard *LB, int N);
/* prosedur memindahkan player sesuai dengan dadu yang di roll oleh player tersebut */

void EndTurn();
/* prosedur untuk mengakhiri turn player tertentu */

void ShowMoney();
/* prosedur untuk menunjukkan jumlah uang player pada giliran saat ini */

void PrintPos(TabKota TK, ListBoard LB);
/* prosedur untuk menunjukkan posisi player tertentu pada board */

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

void sell(Kata K, TabKota *TK);
/* prosedur untuk menambahkan kota dengan nama K ke list offered */

void sellbank(Kata K, TabKota *TK);
/* prosedr untuk menjual kota dengan nama K ke bank */

void showOffered(TabKota TK);
/* prosedur untuk menampilkan info kota yang ada di list offered */

void buyoffered (Kata K, TabKota *TK);
/* prosedur untuk membeli kota yang ada di list offered */

void Save (ListBoard LB, TabKota TK, SKata K);
/* prosedur untuk melakukan save game */

boolean Load (ListBoard *LB,TabKota *TK, SKata K);
/* mengembalikan 1 jika file dapat dibaca, 0 jika tidak */

void removeOffered(TabKota *TK,Player P);
/* prosedur untuk menghapus kota pada list offered */

boolean isWinTour(TabKota Kota);
/* mengembalikan true jika ada pemain yang mendapatkan semua petak rekreasi, false jika tidak */

boolean isWinBlock(TabKota Kota);
/* mengembalikan true jika ada pemain yang mendapatkan 3 blok, false jika tidak */

void bangkrut(Player P,TabKota *TK,ListPlayer *Turn);

#endif
