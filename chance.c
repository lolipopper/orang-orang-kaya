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
    printf("  Jumlah kartu pada Deck :\n");
    printf("  Go to Jail : %d\n", C.el[0]);
    printf("  Free Prison : %d\n", C.el[1]);
    printf("  Free Tax : %d\n", C.el[2]);
    printf("  Protect : %d\n", C.el[3]);
    printf("  Light Off : %d\n\n", C.el[4]);
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
            random = rand() %5;
        } while ((*C).el[random] == 0);
        (*C).el[random] -= 1;
        if (random == 0) {
            printf("  Maaf, anda kurang beruntung. Anda mendapatkan kartu Go to Jail!\n");
            Position(PTurn) = 9;
            boardDesertedIsland(C);
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

void protect(Kata K, TabKota *TK, card *C)
{
    int i, j;

    if (CardProtect(PTurn) != 0) {
        i = 1;
        while ((!IsKataSama(K, NamaKota(*TK,i))) && (i<= 32)) {
            i++;
        }
        if (i <= 32) {
            if (LightOff(*TK,i) == false) {
                printf("  Lampu pada kota ini tidak mati. Kartu protect hanya bisa digunakan pada\n");
                printf("  kota dengan lampu yang mati.\n\n");
            }
            else {
                LightOff(*TK,i) = false;
                printf("  Kota ");
                for(j=0; j<K.Length; j++) {
                    printf("%c", K.TabKata[j]);
                }
                printf(" hidup lampu.\n\n");
                CardProtect(PTurn) -= 1;
                (*C).el[3] += 1;
            }
        }
        else {
            printf("  Tidak ada kota dengan nama tersebut.\n\n");
        }
    }
    else {
        printf("  Kamu tidak memiliki kartu Protect.\n\n");
    }
}

void off(Kata K, TabKota *TK, card *C)
{
    int i, j;

    if (CardOff(PTurn) != 0) {
        i = 1;
        while ((!IsKataSama(K, NamaKota(*TK,i))) && (i<= 32)) {
            i++;
        }
        if (i <= 32) {
            if ((Owner(*TK,i) != '0') && (Owner(*TK,i) != PlayerId(PTurn))) {
                if (LightOff(*TK,i) == true) {
                    printf("  Lampu pada kota ini sudah mati. Kartu Off Light hanya bisa digunakan pada\n");
                    printf("  kota dengan lampu yang sudah mati.\n\n");
                }
                else {
                    LightOff(*TK,i) = true;
                    printf("  Kota ");
                    for(j=0; j<K.Length; j++) {
                        printf("%c", K.TabKata[j]);
                    }
                    printf(" mati lampu.\n\n");
                    CardOff(PTurn) -= 1;
                    (*C).el[4] += 1;
                }
            }
            else {
                printf("  Kartu Off Light hanya bisa digunakan pada kota milik orang lain.\n\n");
            }
        }
        else {
            printf("  Tidak ada kota dengan nama tersebut.\n\n");
        }
    }
    else {
        printf("  Kamu tidak memiliki kartu Off Light.\n\n");
    }
}
