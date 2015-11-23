#ifndef XXX_H
#define XXX_H

#include "boolean.h"
#include "player.h"
#include "kota.h"
#include "mesinkata.h"
#include "petakBoard.h"
#include "chance.h"
#include <stdio.h>
#include <stdlib.h>

void boardTax(Player *P);
/* prosedur untuk menentukan gerak player saat sampai di board Tax */

void boardWorldCup(Player *P);
/* prosedur untuk menentukan gerak player saat sampai di board World Cup */

void boardChance(Player *P);
/* prosedur untuk menentukan gerak plater saat sampai di board Chance */

void hostCity(TabKota *Kota);
/* I.S : hanya dapat dilakukan pada board World Cup */
/* F.S : kota yang dipilih akan memiliki harga sewa 2 kali lipat */

void leaderBoard(ListPlayer L, ListBoard LB);
/* F.S : menampilkan kekayaan tiap pemain */

#endif
