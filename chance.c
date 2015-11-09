#include "chance.h"

void makeChance(card *C)
{
    int i;

    for (i=0; i<=4; i++) {
        (*C).el[i] = 5;
    }
}

boolean isDeckEmpty(card C)
{
    int i;
    boolean kosong;

    kosong = true;
    i = 0;
    while ((i<=4) && (kosong)) {
        if (C.el[i] != 0) {
            kosong = false;
        }
        i++;
    }
    return kosong;
}

void randomCard(card *C, ElmtList *P)
{
    int i;
    int random;

    if isDeckEmpty(*C) {
        printf("Kartu chance telah habis.\n");
    }
    else {
        do
            random = rand() %4;
        while ((*C).el[random] == 0);
        (*C).el[random] -= 1;
        if (random == 0) {
            printf("Maaf, anda kurang beruntung. Anda mendapatkan kartu Go to Jail!\n");
            gotojail(*P);
            (*C).el[0] += 1;
        }
        else if (random == 1) {
            printf("Selamat, anda mendapatkan kartu Free Prison!\n");
            CardFreePrison(*P) += 1;
        }
        else if (random == 2) {
            printf("Selamat, anda mendapatkan kartu Free Tax!\n");
            CardFreeTax(*P) += 1;
        }
        else if (random == 3) {
            printf("Selamat, anda mendapatkan kartu Protect!\n");
            CardProtect(*P) += 1;
        }
        else if (random == 4) {
            printf("Selamat, anda mendapatkan kartu Light Off!\n");
            CardOff(*P) += 1;
        }
    }
}

void gotojail(ElmtList *P)
{
    Position(*P) = 9;
    Jail(*P) = true;
}

void freeme(ElmtList *P)
{
    if (CardFreePrison(*P) != 0) {
        printf("Anda bebas dari penjara.\n");
        Jail(*P) = false;
        CardFreePrison(*P) -= 1;
    }
    else {
        printf("Maaf, anda tidak memiliki kartu Free Prison.\n");
    }
}

void freetax(ElmtList *P)
{
   //belum jelas
}

void protect(ElmtList *P, TabKota *Kota, )
{
    // masih bingung sama off
}
