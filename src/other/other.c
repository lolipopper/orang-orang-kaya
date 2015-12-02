#include "other.h"

boolean IsKataSama(Kata K1, Kata K2)
{
	int i;

	if (K1.Length == K2.Length) {
		i=0;
		while ((i<K1.Length) && (K1.TabKata[i]==K2.TabKata[i])) {
			i++;
		}
		if (i == K1.Length) {
            return true;
		}
		else {
            return false;
		}
	}
	else {
        return false;
	}
}

void roll()
{
    int a, b;
    srand ( time(NULL) );
	Dice1(D) = (rand() % 6) + 1;
	Dice2(D) = (rand() % 6) + 1;
	//printf("  Masukkan angka dadu yang diinginkan (dadu1 dadu2) : ");
	//scanf("%d", &a);
    //scanf("%d", &b);
	//Dice1(D) = a; Dice2(D) = b;
	// sengaja tidak dihapus untuk pengecekan modul
}

boolean reroll()
{
	return Dice1(D) == Dice2(D);
}

void help()
{
    printf("  Perintah-perintah yang dapat dijalankan: \n");
    printf("  roll dice              : mengocok dadu\n");
    printf("  turn                   : menampilkan turn player saat ini\n");
    printf("  board                  : menampilkan board\n");
    printf("  end turn               : mengakhiri giliran\n");
    printf("  info <nama petak>      : menampilkan informasi kota / tempat rekreasi\n");
    printf("  buy                    : membeli kota tempat player berada sekarang\n");
    printf("  upgrade                : melakukan upgrade pada kota milik sendiri\n");
    printf("  sell <nama petak>      : menempatkan aset ke list penjualan\n");
    printf("  sell bank <nama petak> : menjual aset ke bank\n");
    printf("  show offered           : menampilkan list penjualan\n");
    printf("  buyoffered             : membeli aset yang ada pada list penjualan\n");
    printf("  leaderboard            : menampilkan peringkat total kekayaan semua pemain\n");
    printf("  print kekayaan         : menampilkan informasi uang dan aset semua pemain\n");
    printf("  print card             : menampilkan informasi jumlah kartu pada deck\n");
    printf("  save <nama file>       : melakukan save permainan\n");
    printf("  load <nama file>       : melakukan load permainan\n\n");
}
