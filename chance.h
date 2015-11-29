#ifndef CHANCE_H
#define CHANCE_H

#include "boolean.h"
#include "kota.h"
#include "player.h"
#include "command.h"
#include <time.h>

//KAMUS GLOBAL
typedef struct {
    int el[5];
} card;

card C;

void makeChance(card *C);
/* I.S : array terdefinisi */
/* F.S : membuat deck dengan isi masing-masing jenis kartu sejumlah 5 dalam representasi array */
/* C.el[0] menyatakan jumlah kartu Go to Jail */
/* C.el[1] menyatakan jumlah kartu Free Prison */
/* C.el[2] menyatakan jumlah kartu Free Tax */
/* C.el[3] menyatakan jumlah kartu Protect */
/* C.el[4] menyatakan jumlah kartu Light Off */

void printCard(card C);
/* prosedur untuk menampilkan jumlah kartu di dalam deck saat ini */

void randomCard(card *C);
/* I.S : Player P berada di kotak chance */
/* F.S : jika deck card kosong, Player tidak mendapatkan apapun.
         jika deck tidak kosong, kartu di deck berkurang 1 dan Player mendapatkan 1 kartu secara random */

void protect(Kata K, TabKota *TK, card *C);
/* prosedur untuk menggunakan kartu protect */

void off(Kata K, TabKota *TK, card *C);
/* prosedur untuk menggunakan kartu off light */

void boardTax(card *C);
/* efek yang didapatkan player ketika sampai di board Tax */

void boardDesertedIsland(card *C);
/* efek yang didapatkan player ketika sampai di board Deserted Island */

void boardChance();
/* efek yang didapatkan player ketika sampai di board Chance */

void boardBonus();
/* efek yang didapatkan player ketika sampai di board Bonus */

void returnCards(Player P,card *C);					//ke chance

#endif
