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

void randomCard(card *C, AddressPl *P)
{
    int random;

    if (isDeckEmpty(*C)) {
        printf("Kartu chance telah habis.\n");
    }
    else {
        do
            random = rand() %4;
        while ((*C).el[random] == 0);
        (*C).el[random] -= 1;
        if (random == 0) {
            printf("Maaf, anda kurang beruntung. Anda mendapatkan kartu Go to Jail!\n");
            gotojail(P);
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

void gotojail(AddressPl *P)
{
	Position(*P) = 9;
    Jail(*P) = true;
}

void freetax(AddressPl *P)
{
    char yn;

   if (CardFreeTax(*P) != 0) {
        printf("Anda memiliki kartu Free Tax. Apakah anda ingin menggunakan ? (Y/N)");
        scanf("%c", &yn);
        if (yn == 'Y') {
            CardFreeTax(*P) -= 1;
        }
        else {
            Money(*P) -= 100;
        }
   }
   else {
        Money(*P) -= 100;
   }
}

void freeme(AddressPl *P)
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

void protect(ListBoard LB, AddressPl *P, TabKota *TK, Kata input)
{
    Address adr;

    if (CardProtect(*P) == 0) {
        printf("Maaf, anda tidak memiliki kartu Protect.\n");
    }
    else {
        adr = SearchKota(LB, *TK, input);
        if (adr == Nil) {
            printf("Nama kota tidak terdefinisi.\n");
        }
        else {
            if (!(*TK).TK[Id(adr)].LightOff) {
                printf("Kota tersebut tidak berada dalam serangan.\n");
            }
            else {
                (*TK).TK[Id(adr)].LightOff = false;
                CardProtect(*P) -= 1;
            }
        }
    }
}

void off(ListBoard LB, AddressPl *P, TabKota *TK, Kata input)
{
	//Kamus
	Address adr;

	//Algoritma
    if (CardOff(*P) == 0) {
        printf("Maaf, anda tidak memiliki kartu Off.\n");
    }
    else {
        adr = SearchKota(LB, *TK, input);
        if (adr == Nil) {
            printf("Nama kota tidak terdefinisi.\n");
        }
        else {
            if ((*TK).TK[Id(adr)].LightOff) {
                printf("Sudah terjadi mati lampu di kota tersebut.\n");
            }
            else {
                (*TK).TK[Id(adr)].LightOff = true;
                CardOff(*P) -= 1;
            }
        }
    }
}
