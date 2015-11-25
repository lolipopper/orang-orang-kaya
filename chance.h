#ifndef CHANCE_H
#define CHANCE_H

#include "boolean.h"
#include "kota.h"
#include "player.h"
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

boolean isDeckEmpty(card C);
/* mengembalikan true jika deck kosong, false jika tidak */

void printCard(card C);
/* prosedur untuk menampilkan jumlah kartu di dalam deck saat ini */

void randomCard(card *C);
/* I.S : Player P berada di kotak chance */
/* F.S : jika deck card kosong, Player tidak mendapatkan apapun.
         jika deck tidak kosong, kartu di deck berkurang 1 dan Player mendapatkan 1 kartu secara random */

#endif
