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
    return priceCity(K) * 8 / 10;
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
        printf("  Biaya sewa : ");
		if(isWorldCup(TK, i))
			printf("%lldK\n", 2*priceCity(TK.TK[i]));
		else
			printf("%lldK\n", priceCity(TK.TK[i]));
        printf("  Biaya ambil alih : %lldK\n", priceCity(TK.TK[i]));
        printf("  Biaya upgrade bangunan : %lldK\n", priceUpgrade(TK.TK[i]));
        printf("  Status:\n");
		if(isWorldCup(TK, i) || LightOff(TK, i)) {
			if(isWorldCup(TK, i))
				printf("  - Host World Cup\n");
			if(LightOff(TK, i))
				printf("  - Light Off\n");
		}
		else
			printf("  -\n");
        printf("\n");
    }
    else {
        printf("  Tidak ada kota dengan nama tersebut.\n\n");
    }
}

void DeleteAllOwnedBuildings(TabKota *TK,Player P)
{
    int id;
    for (id=1;id<=32;id++)
    {
        if (Owner(*TK,id)==P.playerId)
        {
            Owner(*TK,id)='0';
        }
    }
}
