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

void printCard(card C)
{
    printf("Jumlah kartu pada Deck :\n");
    printf("Go to Jail : %d\n", C.el[0]);
    printf("Free Prison : %d\n", C.el[1]);
    printf("Free Tax : %d\n", C.el[2]);
    printf("Protect : %d\n", C.el[3]);
    printf("Light Off : %d\n", C.el[4]);
}

void randomCard(card *C)
{
    int random;

    if (isDeckEmpty(*C)) {
        printf("  Kartu chance telah habis.\n");
    }
    else {
        do {
            srand ( time(NULL) );
            random = rand() %4;
        } while ((*C).el[random] == 0);
        (*C).el[random] -= 1;
        if (random == 0) {
            printf("  Maaf, anda kurang beruntung. Anda mendapatkan kartu Go to Jail!\n");
            Position(PTurn) = 9;
            boardDesertedIsland();
            (*C).el[0] += 1;
        }
        else if (random == 1) {
            printf("  Selamat, anda mendapatkan kartu Free Prison!\n");
            CardFreePrison(PTurn) += 1;
        }
        else if (random == 2) {
            printf("  Selamat, anda mendapatkan kartu Free Tax!\n");
            CardFreeTax(PTurn) += 1;
        }
        else if (random == 3) {
            printf("  Selamat, anda mendapatkan kartu Protect!\n");
            CardProtect(PTurn) += 1;
        }
        else if (random == 4) {
            printf("  Selamat, anda mendapatkan kartu Light Off!\n");
            CardOff(PTurn) += 1;
        }
    }
}
