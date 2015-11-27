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
