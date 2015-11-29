#include "chance.h"

void makeChance(card *C)
{
    int i;

    for (i=0; i<=4; i++) {
        (*C).el[i] = 5;
    }
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

void boardChance()
{
    randomCard(&C);
}

void boardTax(card *C)
{
    boolean inputBenar;
    char input[20];

    printf("  Pajak Bumi dan Bangunan. Kamu harus membayar sebesar 10 persen dari aset kekayaanmu.\n");
    printf("  Aset kekayaanmu saat ini adalah %lldK\n", Kekayaan(PTurn));
    printf("  Kamu harus membayar sebesar %lldK\n", (Kekayaan(PTurn) / 10));
    printf("  Kamu bisa bebas dari pajak dengan menggunakan kartu Free Tax.\n");
    printf("  Ketik 'free tax' untuk menggunakan kartu Free Tax, 'pay' untuk tetap membayar.\n\n");
    inputBenar = false;
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "free") == 0) {
            scanf("%s", input);
            if (strcmp(input, "tax") == 0) {
                if (CardFreeTax(PTurn) == 0) {
                    printf("  Kamu tidak memiliki kartu Free Tax.\n\n");
                }
                else {
                    CardFreeTax(PTurn) -= 1;
                    printf("  Kamu bebas pajak.\n");
                    inputBenar = true;
                    (*C).el[2] += 1;
                }
            }
        }
        else if (strcmp(input, "pay") == 0) {
            printf("  Uang kamu berkurang sebesar %lldK.\n", (Kekayaan(PTurn) / 10));
            inputBenar = true;
            Money(PTurn) -= (Kekayaan(PTurn) / 10);
            ShowMoney();
        }
        else {
            printf("  Input salah\n\n");
        }
    } while (!inputBenar);
}

void boardDesertedIsland(card *C)
{
    boolean inputBenar;
    char input[20];

    printf("  Kamu masuk penjara.\n");
    printf("  Kamu bisa keluar dengan menggunakan kartu Free Prison atau membayar 100K\n");
    printf("  Ketik 'free me' untuk menggunakan kartu Free Prison, 'pay' untuk membayar, 'stay' untuk tetap di penjara.\n\n");
    inputBenar = false;
    do {
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "free") == 0) {
            scanf("%s", input);
            if (strcmp(input, "me") == 0) {
                if (CardFreePrison(PTurn) == 0) {
                    printf("  Kamu tidak memiliki kartu Free Prison.\n\n");
                }
                else {
                    CardFreePrison(PTurn) -= 1;
                    printf("  Kamu bebas dari penjara.\n");
                    Jail(PTurn) = false;
                    inputBenar = true;
                    (*C).el[1] += 1;
                    rolled = true;
                }
            }
        }
        else if (strcmp(input, "pay") == 0) {
            if (Money(PTurn) < 100) {
                printf("  Uangmu tidak cukup.\n");
            }
            else {
                Money(PTurn) -= 100;
                printf("  Kamu bebas dari penjara.\n");
                ShowMoney();
                Jail(PTurn) = false;
                inputBenar = true;
                rolled = true;
            }
        }
        else if (strcmp(input, "stay") == 0) {
            printf("  Kamu masuk penjara.\n");
            inputBenar = true;
            Jail(PTurn) = true;
            rolled = true;
            turnAwal = false;
        }
    } while (!inputBenar);
}

void boardBonus()
{
    long long int randomNum;

    randomNum = (rand() % 300) + 100;
    printf("  Selamat, kamu mendapatkan %lld.\n", randomNum);
    Money(PTurn) += randomNum;
    ShowMoney();
}

void returnCards(Player P,card *C)
{
    (*C).el[1]+=nFreePrison(P);
    (*C).el[2]+=nFreeTax(P);
    (*C).el[3]+=nProtect(P);
    (*C).el[4]+=nOffLight(P);
}
