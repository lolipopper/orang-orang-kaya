#include "player.h"

void PrintInfoPlayer(AddressPl P1);

int main() {
	int i, n, position, kekayaan, nFreeTax, nFreePrison, nOffLight, nProtect, movworldtravel;
	long long uang;
	boolean jail;
	char dum, playerId;
	AddressPl Ply, Play;
	Player P1, P2;

	printf("===================================================\n");
	printf("|                                                 |\n");
	printf("|---------------DRIVER MODUL PLAYER---------------|\n");
	printf("|                                                 |\n");
	printf("===================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan ConsPlayer dan AlokasiPl\n");
	printf("-------------------------------------------------\n");
	printf("  Masukkan nilai awal untuk player sesuka Anda.\n");
	printf("  Posisi Awal              : "); scanf("%d", &position);
	printf("  Uang Awal                : "); scanf("%ll", &uang);
	printf("  Jml Kartu Free Tax       : "); scanf("%d", &nFreeTax);
	printf("  Jml Kartu Free Prison    : "); scanf("%d", &nFreePrison);
	printf("  Jml Kartu Off Light      : "); scanf("%d", &nOffLight);
	printf("  Jml Kartu Protect        : "); scanf("%d", &nProtect);
	getchar();
	printf("  ID Player (1 huruf)      : "); scanf("%c", &playerId);
	printf("  Kekayaan                 : "); scanf("%d", &kekayaan);
	printf("  Dalam Penjara (1 atau 0) : "); scanf("%d", &jail);
	printf("  Jalan akibat WOrld Travel : "); scanf("%d", &movworldtravel);

	printf("\n\n%lld\n\n", uang);
	ConsPlayer(&P1, position, uang, nFreeTax, nFreePrison, nOffLight, nProtect, playerId, kekayaan, jail, movworldtravel);
	Ply = AlokasiPl(P1);

	PrintInfoPlayer(Ply);

	printf("=================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan DealokasiPl\n");
	printf("-------------------------------------------------\n\n");

	printf("- Player %c didealokasi sehingga inputan tadi menjadi:\n", PlayerId(Ply));
	DealokasiPl(&Ply);

	PrintInfoPlayer(Ply);

	printf("=================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan InitPlayer\n");
	printf("-------------------------------------------------\n\n");

	getchar();
	printf("  Silahkan masukkan Player ID (1 huruf) yang Anda inginkan.\n");
	printf("  ID Player : "); scanf("%c", &dum);
	InitPlayer(&P2, dum);
	Play = AlokasiPl(P2);

	printf("\n  InitPlayer menghasilkan berikut ini.\n");
	PrintInfoPlayer(Play);
	DealokasiPl(&Play);

	printf("=================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan InitNPlayer\n");
	printf("-------------------------------------------------\n\n");

	printf("  Masukkan jumlah pemain yang Anda inginkan.\n");
	InitNPlayer();

	printf("\n  Info para pemain adalah:\n");
	Ply = First(Turn);
	do {
		PrintInfoPlayer(Ply);
		Ply = Next(Ply);
	} while(Ply != First(Turn));
	printf("=================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan DeleteAllPlayer\n");
	printf("-------------------------------------------------\n\n");

	printf("  Player yang sudah ada sebelumnya akan di-delete.\n");
	printf("  Sehingga info para pemain menjadi:\n");
	Ply = First(Turn);
	do {
		PrintInfoPlayer(Ply);
		Ply = Next(Ply);
	} while(Ply != First(Turn));
	printf("=================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan InitNumPlayer\n");
	printf("-------------------------------------------------\n\n");

	printf("  Masukkan jumlah pemain yang Anda inginkan.\n");
	printf("  Jumlah pemain : "); scanf("%d", &n);
	InitNumPlayer(n);

	printf("\n  Info para pemain adalah:\n");
	Ply = First(Turn);
	do {
		printf("  Address Memory Player %c : %d\n\n", PlayerId(Ply), &Ply);
		PrintInfoPlayer(Ply);
		Ply = Next(Ply);
	} while(Ply != First(Turn));
	printf("=================================================\n\n");

	printf("=================================================\n");
	printf("- Pengecekan SearchPl dan DeletePlayer\n");
	printf("-------------------------------------------------\n\n");

	do {
		getchar();
		printf("  Masukkan ID Player yang ingin Anda cari dan ingin Anda hapus! (A, B, C, atau D)\n");
		printf("> ");
		scanf("%c", &dum);
		if(dum != 'A' && dum != 'B' && dum != 'C' && dum != 'D')
			printf("  Masukkan A, B, C, atau D.\n");
	} while(dum != 'A' && dum != 'B' && dum != 'C' && dum != 'D');
	Play = SearchPl(dum);
	if(Play == Nil)
		printf("  Tidak ada Player %c dalam permainan.\n", dum);
	else {
		printf("  Address Memory Player %c : %d\n\n", PlayerId(Play), &Play);
		PrintInfoPlayer(Play);
		deletePlayer(&Turn, Info(Play));
		printf("  Player %c telah dihapus.", dum);
		Ply = First(Turn);
		do {
			printf("  Address Memory Player %c : %d\n\n", PlayerId(Ply), &Ply);
			PrintInfoPlayer(Ply);
			Ply = Next(Ply);
		} while(Ply != First(Turn));
	}
	printf("=================================================\n\n");
	printf("----------------Pengecekan Selesai---------------\n");
	printf("=================================================\n\n");

    return 0;
}

void PrintInfoPlayer(AddressPl P1) {

	printf("  ID Player                : Player %c\n", PlayerId(P1));
	printf("  Posisi Awal              : petak ke-%d\n", Position(P1));
	printf("  Uang Awal                : %lldK\n", P1->info.money);
	printf("  Jml Kartu Free Tax       : %d buah\n", CardFreeTax(P1));
	printf("  Jml Kartu Free Prison    : %d buah\n", CardFreePrison(P1));
	printf("  Jml Kartu Off Light      : %d buah\n", CardOff(P1));
	printf("  Jml Kartu Protect        : %d buah\n", CardProtect(P1));
	printf("  Kekayaan                 : %dK\n", Kekayaan(P1));
	printf("  Dalam Penjara            : ");
	if(Jail(P1)) printf("true\n");
	else printf("false\n");
	printf("  Jalan akibat Wrld Travel : %d petak\n\n", MovWorldTravel(P1));
}
