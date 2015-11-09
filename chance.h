#ifndef KOTA_H
#define KOTA_H

#include "boolean.h"
#include "player.h"
#include "kota.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int el[4];
} card;

void makeChance(card *C);
/* I.S : array terdefinisi */
/* F.S : membuat deck dengan isi masing-masing jenis kartu sejumlah 5 dalam representasi array */
/* C.card[0] menyatakan jumlah kartu Go to Jail */
/* C.card[1] menyatakan jumlah kartu Free Prison */
/* C.card[2] menyatakan jumlah kartu Free Tax */
/* C.card[3] menyatakan jumlah kartu Protect */
/* C.card[4] menyatakan jumlah kartu Light Off */

boolean isDeckEmpty(card C);
/* mengembalikan true jika deck kosong, false jika tidak */

void randomCard(card *C, ElmtList *P);
/* I.S : ElmtList P berada di kotak chance */
/* F.S : jika deck card kosong, ElmtList tidak mendapatkan apapun.
         jika deck tidak kosong, kartu di deck berkurang 1 dan ElmtList mendapatkan 1 kartu secara random */

void gotojail(ElmtList *P);
/* I.S : ElmtList mendapatkan kartu Go to Jail dan berada di board chance */
/* F.S : ElmtList berada di board deserted island dan terkurung */

void freeme(ElmtList *P);
/* I.S : ElmtList berada di board deserted island dan terkurung */
/* F.S : ElmtList berada di board deserted island dan bebas */

void freetax(ElmtList *P);
/* I.S : ElmtList berada */
/* F.S : ElmtList tidak membayar tax */
// belum jelas

void protect(ElmtList *P, TabKota *Kota);
/* I.S : kota terdefinisi */
/* F.S : menghidupkan lampu di kota jika terjadi mati lampu */

void off(ElmtList *P, TabKota *Kota);

#endif
