#ifndef KOTA_H
#define KOTA_H

#include "boolean.h"
#include "player.h"
#include "kota.h"
#include "mesinkata.h"
#include "petakBoard.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int el[4];
} card;

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

void randomCard(card *C, Player *P);
/* I.S : Player P berada di kotak chance */
/* F.S : jika deck card kosong, Player tidak mendapatkan apapun.
         jika deck tidak kosong, kartu di deck berkurang 1 dan Player mendapatkan 1 kartu secara random */

void gotojail(Player *P);
/* I.S : Player mendapatkan kartu Go to Jail dan berada di board chance */
/* F.S : Player berada di board deserted island dan terkurung */
/* otomatis digunakan jika mendapatkan kartu ini */

void freetax(Player *P);
/* I.S : Player berada di board tax */
/* F.S : Jika player memiliki kartu free tax, ditanya.
         Jika tidak, money player - 100 */
// belum jelas

void freeme(Player *P);
/* I.S : Player berada di board deserted island dan terkurung */
/* F.S : Player berada di board deserted island dan bebas */

void protect(ListBoard LB, Player *P, TabKota *Kota, Kata input);
/* F.S : menghidupkan lampu di kota tertentu jika terjadi mati lampu */

void off(ListBoard LB, Player *P, TabKota *Kota, Kata input);
/* F.S : mematikan lampu di kota tertentu */

void leaderBoard(ListPlayer L, ListBoard LB);
/* F.S : menampilkan kekayaan tiap pemain */

#endif
