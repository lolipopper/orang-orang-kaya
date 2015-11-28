#include "kota.h"

long long priceCity(Kota K)
{
    if ((K.level == 0) || (K.level == 1)) {
        return K.price;
    }
    else if (K.level == 2) {
        return 2.5 * K.price;
    }
    else if (K.level == 3) {
        return 4 * K.price;
    }
}

long long priceUpgrade(Kota K)
{
    if (K.level == 1) {
        return 1.5 * K.price;
    }
    else if (K.level == 2) {
        return 3 * K.price;
    }
}

long long priceSell (Kota K)
{
    return priceCity(K)/2;
}

void infoCity(Kata K, TabKota TK)
{
    int i, j;

    i = 1;
    while ((!IsKataSama(K, NamaKota(TK,i))) && (i<= 32)) {
        i++;
    }
    if (i <= 32) {
        printf("  ");
        for (j=0; j<K.Length; j++) {
            printf("%c", K.TabKata[j]);
        }
        printf(", pemilik properti ");
        if (Owner(TK,i) == '0') {
            printf("tidak ada, ");
        }
        else {
            printf("%c, ", Owner(TK,i));
        }
        printf("bangunan level %d\n", Level(TK,i));
        printf("  Biaya sewa : %lld\n", priceCity(TK.TK[i]));
        printf("  Biaya ambil alih : %lld\n", priceCity(TK.TK[i]));
        printf("  Biaya upgrade bangunan : %lld\n", priceUpgrade(TK.TK[i]));
        printf("\n");
    }
    else {
        printf("  Tidak ada kota dengan nama tersebut.\n\n");
    }
}
