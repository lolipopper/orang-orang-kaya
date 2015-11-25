#include "kota.h"

long long priceCity(Kota K)
{
    if ((K.level == 0) || (K.level == 1)) {
        return K.price;
    }
    else if (K.level == 2) {
        return 2 * K.price;
    }
    else if (K.level == 3) {
        return 3 * K.price;
    }
}
