#include "xxx.h"

void boardTax(Player *P)
{
    printf("Anda sampai di board Tax. Anda harus membayar pajak!\n");
    if (CardFreeTax(*P) == 0) { // tidak ada kartu free tax
        Money(*P) -= 100;
    }
    else { // ada kartu free tax
        freetax(P);
    }
}

void boardWorldCup(Player *P)
{
    printf("Anda sampai di board World Cup. Silahkan pilih kota yang ingin anda jadikan tempat World Cup.\n");
    // baca command, do command
}

void boardChance(Player *P)
{
    randomCard(&C, P);
}

void hostCity(TabKota *Kota)
{
    // tinggal city yang dipilih rent nya dikali 2
    // akan dibahas besok karena dirasa butuh type baru yaitu harga sewa
}

void leaderBoard(ListPlayer L, ListBoard LB)
{
    /*
    Address adrPlayer, adrBoard;
    long long kekayaan[3];
    TabKota Kota;
    int i;

    kekayaan[0] = 0;
    kekayaan[1] = 0;
    kekayaan[2] = 0;
    kekayaan[3] = 0;
    i = 0;
    adrPlayer = First(L);
    adrBoard = First(LB);
    do {
        kekayaan[i] = Info(Money(P));
        while (adrBoard != Last(LB)) {
            if (Info(adrBoard).type == 1) {
                if (Kota[Info(adrBoard).id].owner = 'A') {
                    kekayaan[i] = kekayaan[i] + Kota[Info(adrBoard).id].price;
                    if (Kota[Info(adrBoard).id].level = 3) {
                        kekayaan[i] = kekayaan[i] + (Kota[Info(adrBoard).id].price * 3) + (Kota[Info(adrBoard).id].price * 1.75)
                    }
                    else if  (Kota[Info(adrBoard).id].level = 2) {
                        kekayaan[i] = kekayaan[i] + (Kota[Info(adrBoard).id].owner * 1.75);
                    }
                }
            }
            adrBoard = Next(adrBoard);
        }

    } while (i <= 3); */
}
