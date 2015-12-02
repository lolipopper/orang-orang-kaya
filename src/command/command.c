#include "command.h"

void MovPlayer(TabKota *TK, ListBoard *LB)
{
    if (rolled == true) {
        printf("  Kamu tidak bisa melakukan roll dice lagi.\n\n");
    }
    else {
        if(MovWorldTravel(PTurn) != 0) {
            turnAwal = false;
            printf("  Kamu pindah sejauh %d petak akibat World Travel\n", MovWorldTravel(PTurn));
            MoveNPetak(TK, LB, MovWorldTravel(PTurn));
            MovWorldTravel(PTurn) = 0;
            rolled = true;
        }
        if (!Jail(PTurn)) {
            if (!rolled) {
                turnAwal = false;
                roll();
                printf("  %d + %d = %d\n", Dice1(D), Dice2(D), (Dice1(D) + Dice2(D)));
                MoveNPetak(TK, LB, (Dice1(D) + Dice2(D)));
                if (!reroll()) {
                    rolled = true;
                }
            }
        }
        else {
            printf("  Maaf, kamu sedang dipenjara.\n\n");
        }
    }
}

void MoveNPetak(TabKota *TK, ListBoard *LB, int N)
{
	int i, mov, j, k;
	Address P;

	i = Position(PTurn);
	P = First(*LB);
	while (i > 1) {
		P = Next(P);
		i -= 1;
	}
	mov = N;
	if(PlayerId(PTurn) == 'A')
		k = 1;
	else if(PlayerId(PTurn) == 'B')
		k = 2;
	else if(PlayerId(PTurn) == 'C')
		k = 3;
	else if(PlayerId(PTurn) == 'D')
		k = 4;
	while (mov > 0) {
		Position(PTurn) += 1;
		if (Position(PTurn) > 32) {
			Position(PTurn) -= 32;
		}
		if (Position(PTurn) == 1) {
            printf("  Kamu melewati board Start. Kamu mendapatkan bonus 300K.\n");
            Money(PTurn) += 300;
            ShowMoney();
		}
		if(PlayerId(PTurn) == whoWorldCup(*TK, idWorldCup[k])) {
			if(Position(PTurn) == 17) {
				printf("  Kamu sudah melewati World Cup, efek harga sewa kota ");
				j = 0;
				while(j < NamaKota(*TK, idWorldCup[k]).Length) {
					printf("%c", NamaKota(*TK, idWorldCup[k]).TabKata[j]);
					j++;
				}
				printf(" 2x lipat hilang.\n");
				isWorldCup(*TK, idWorldCup[k]) = false;
				whoWorldCup(*TK, idWorldCup[k]) = '0';
				idWorldCup[k] = 0;
			}
		}
		if ((Owner(*TK, Position(PTurn)) == PlayerId(PTurn)) && (LightOff(*TK, Position(PTurn)) == true)) {
            LightOff(*TK, Position(PTurn)) = false;
            printf("  Kamu melewati kotamu yang sedang mati lampu.\n");
            printf("  Kota ini hidup lampu kembali.\n\n");
		}
		P = Next(P);
		mov -=1;
	}
	PrintPos(*TK, *LB);
	if (Type(P) == 1) {
        payRent(LB, TK);
	}
	if (Type(P) == 3) {
		boardChance();
	}
	if (Type(P) == 4) {
		boardBonus();
	}
	if (Type(P) == 5) {
		boardDesertedIsland(&C);
	}
	if (Type(P) == 6) {
		boardWorldCup(*LB, TK);
	}
	if (Type(P) == 7) {
        boardWorldTravel(*LB, *TK);
	}
	if (Type(P) == 8) {
		boardTax(&C);
	}
	printf("\n");
}

void EndTurn()
{
	if (rolled) {
		printf("  Player %c mengakhiri gilirannya\n\n", PlayerId(PTurn));
		rolled = false;
		PTurn = Next(PTurn);
		turnAwal = true;
	}
	else {
		printf("  Kamu harus melakukan 'rolldice'\n\n");
	}
}

void ShowMoney()
{
	printf("  Uangmu sekarang : %lldK \n", Money(PTurn));
}

void PrintPos(TabKota Kota, ListBoard LB)
{
	int length;
	int i;
	Address Petak;

	Petak = First(LB);
	printf("  Player %c sampai di ", PlayerId(PTurn));
	i = Position(PTurn);
	while (i > 1) {
		Petak = Next(Petak);
		i -= 1;
	}
	if (Type(Petak) == 2) {
		printf("board Start");
	}
	if (Type(Petak) == 3) {
		printf("board Chance");
	}
	if (Type(Petak) == 4) {
		printf("board Bonus");
	}
	if (Type(Petak) == 5) {
		printf("board Deserted Island");
	}
	if (Type(Petak) == 6) {
		printf("board World Cup");
	}
	if (Type(Petak) == 7) {
		printf("board World Travel");
	}
	if (Type(Petak) == 8) {
		printf("board Tax");
	}
	if (Type(Petak) == 1) {
		length = (NamaKota(Kota, Position(PTurn)).Length);
		for(i = 0; i < length; i++)
			printf("%c", Kota.TK[Position(PTurn)].name.TabKata[i]);
	}
	printf("\n");
}

void buy(TabKota *Kota, ListBoard *LB)
{
    int pos;
    Address P;
    AddressPl Pl;

    pos = Position(PTurn);
    P = First(*LB);
    while (pos != Id(P)) {
        P = Next(P);
    }
    if (turnAwal == false) {
        if (Type(P) == 1) {
            if (Owner(*Kota,pos) != PlayerId(PTurn)) {
                if (isRekreasi(*Kota,pos) == true) {
                    if (Owner(*Kota,pos) == '0') {
                        if (Money(PTurn) < priceCity((*Kota).TK[pos])) {
                            printf("  Uangmu tidak cukup untuk membeli tempat rekreasi ini.\n\n");
                        }
                        else {
                            Money(PTurn) -= priceCity((*Kota).TK[pos]);
                            Kekayaan(PTurn) += priceCity((*Kota).TK[pos]);
                            Owner(*Kota,pos) = PlayerId(PTurn);
                            Level(*Kota,pos)++;
                            printf("  Selamat, tempat rekreasi ini menjadi milikmu!\n");
                            ShowMoney();
                            printf("\n");
                        }
                    }
                    else {
                        printf("  Kamu tidak bisa membeli petak rekreasi milik player lain.\n\n");
                    }
                }
                else {
                    if (Level(*Kota,pos) == 3) {
                        printf("  Kota ini telah menjadi landmark. Landmark tidak bisa dibeli.\n\n");
                    }
                    else {
                        if (Money(PTurn) < priceCity((*Kota).TK[pos])) {
                            printf("  Uangmu tidak cukup untuk membeli kota ini.\n\n");
                        }
                        else {
                            Money(PTurn) -= priceCity((*Kota).TK[pos]);
                            Kekayaan(PTurn) += priceCity((*Kota).TK[pos]);
                            if (Owner(*Kota,pos) != '0') {
                                Pl = First(Turn);
                                while (PlayerId(Pl) != Owner(*Kota,pos)) {
                                    Pl = Next(Pl);
                                }
                                Kekayaan(Pl) -= priceCity((*Kota).TK[pos]);
                                Money(Pl) += priceCity((*Kota).TK[pos]);
                            }
                            Owner(*Kota,pos) = PlayerId(PTurn);
                            if (Level(*Kota,pos) == 0) {
                                Level(*Kota,pos)++;
                            }
                            isOffered(*Kota,pos) = false;
                            printf("  Selamat, kota ini menjadi milikmu!\n");
                            printf("  Level bangunan %d\n", Level(*Kota,pos));
                            ShowMoney();
                            printf("\n");
                            buyupgrade = true;
                        }
                    }
                }
            }
            else {
                printf("  Kota ini milik kamu. Kamu tidak bisa membeli kotamu sendiri.\n\n");
            }
        }
        else {
            printf("  Board ini tidak bisa dibeli.\n\n");
        }
    }
    else {
        printf("  Kamu harus melakukan roll dice terlebih dahulu.\n\n");
    }
}

void upgrade(TabKota *Kota, ListBoard *LB)
{
    int pos;
    Address P;

    pos = Position(PTurn);
    P = First(*LB);
    while (pos != Id(P)) {
        P = Next(P);
    }
    if (Type(P) == 1) {
        if (buyupgrade == false) {
            if (Owner(*Kota,pos) == PlayerId(PTurn)) {
                if (isRekreasi(*Kota,pos) == true) {
                    printf("  Maaf, board rekreasi tidak bisa diupgrade lagi.\n\n");
                }
                else {
                    if (Level(*Kota,pos) == 3) {
                        printf("  Kota ini telah menjadi landmark. Landmark tidak bisa upgrade.\n\n");
                    }
                    else {
                        if (Money(PTurn) < priceUpgrade((*Kota).TK[pos])) {
                            printf("  Uangmu tidak cukup untuk mengupgrade kota ini.\n\n");
                        }
                        else {
                            Money(PTurn) -= priceUpgrade((*Kota).TK[pos]);
                            Kekayaan(PTurn) += priceUpgrade((*Kota).TK[pos]);
                            Level(*Kota,pos)++;
                            printf("  Selamat, level kota ini naik menjadi %d\n", Level(*Kota,pos));
                            ShowMoney();
                            printf("\n");
                            buyupgrade = true;
                        }
                    }
                }
            }
            else {
                printf("  Kota ini bukan milik kamu. Kamu hanya bisa mengupgrade kota milikmu.\n\n");
            }
        }
        else {
            printf("  Kamu hanya bisa melakukan buy dan upgrade sekali setiap turn.\n\n");
        }
    }
    else {
        printf("  Board ini tidak bisa diupgrade.\n\n");
    }
}

void payRent(ListBoard *LB, TabKota *Kota)
{
    int pos;
    long long sewa;
    AddressPl Pl;
    pos = Position(PTurn);
    Pl = First(Turn);

    if (Owner(*Kota,pos) != '0') {
        while (PlayerId(Pl) != Owner(*Kota,pos)) {
            Pl = Next(Pl);
        }
        if (PlayerId(Pl) != PlayerId(PTurn)) {
            if (LightOff(*Kota,pos)) {
                printf("  Karena sedang terjadi mati lamput pada petak ini, maka biaya sewa menjadi 0K.\n");
                sewa = 0;
            }
            else {
                if(idWorldCup[1] == pos) {
                    printf("  Karena petak ini adalah host World Cup, biaya sewa menjadi 2x lipat.\n");
                    sewa = 2*priceCity((*Kota).TK[pos]);
                }
                else if(idWorldCup[2] == pos) {
                    printf("  Karena petak ini adalah host World Cup, biaya sewa menjadi 2x lipat.\n");
                    sewa = 2*priceCity((*Kota).TK[pos]);
                }
                else if(idWorldCup[3] == pos) {
                    printf("  Karena petak ini adalah host World Cup, biaya sewa menjadi 2x lipat.\n");
                    sewa = 2*priceCity((*Kota).TK[pos]);
                }
                else if(idWorldCup[4] == pos) {
                    printf("  Karena petak ini adalah host World Cup, biaya sewa menjadi 2x lipat.\n");
                    sewa = 2*priceCity((*Kota).TK[pos]);
                }
                else {
                    sewa = priceCity((*Kota).TK[pos]);
                }
            }
            printf("  Kamu harus membayar sewa ke pemilik kota ini sebanyak %dK\n", sewa);
            Money(PTurn) -= sewa;
            Money(Pl) += sewa;
            if (Money(PTurn)<0)
                bangkrut(Info(PTurn),Kota,&Turn);
            else
                ShowMoney();
        }
    }
}

void showLeaderBoard()
{
    long long kekayaan[jumlahPemain - 1];
    char player[jumlahPemain - 1];
    AddressPl Pl;
    int i;

    Pl = First(Turn);
    i = 0;
    do {
        player[i] = PlayerId(Pl);
        kekayaan[i] = Money(Pl) + Kekayaan(Pl);
        Pl = Next(Pl);
        i++;
    } while (i<=jumlahPemain-1);
    quicksort(kekayaan, player, 0, jumlahPemain-1);
    for (i=jumlahPemain-1; i>=0; i--) {
        printf("  Player %c %lldK\n", player[i], kekayaan[i]);
    }
    printf("\n");
}

void printKekayaan()
{
    char player[jumlahPemain-1];
    long long kekayaan[jumlahPemain - 1];
    long long money[jumlahPemain -1];
    AddressPl Pl;
    int i;

    Pl = First(Turn);
    i = 0;
    do {
        player[i] = PlayerId(Pl);
        kekayaan[i] = Kekayaan(Pl);
        money[i] = Money(Pl);
        Pl = Next(Pl);
        i++;
    } while (i<=jumlahPemain-1);
    printf("  Player %c, Money = %lldK -> Kekayaan = %lldK\n", player[0], money[0], kekayaan[0]);
    printf("  Player %c, Money = %lldK -> Kekayaan = %lldK\n", player[1], money[1], kekayaan[1]);
    if (jumlahPemain > 2) {
        printf("  Player %c, Money = %lldK -> Kekayaan = %lldK\n", player[2], money[2], kekayaan[2]);
        if (jumlahPemain > 3) {
            printf("  Player %c, Money = %lldK -> Kekayaan = %lldK\n", player[3], money[3], kekayaan[3]);
        }
    }
    printf("\n");
}

void sell(Kata K, TabKota *TK)
{
    int id;

    id = SearchKota(K,*TK);
    if (id <= 32){
        if (Owner(*TK,id) == PlayerId(PTurn)){
            isOffered(*TK,id) = true;
            printf("  Kota anda telah ditambahkan ke dalam List Offered\n");
            printf("  Kepemilikan kota ini akan berpindah setelah ada player yang membeli kotamu\n\n");
        }else{
            printf("  Kota ini bukan milikmu!\n\n");
        }
    }else{
        printf("  Tidak ada kota dengan nama itu!\n\n");
    }
}

void sellbank(Kata K, TabKota *TK)
{
    int id,hargajualbank;

    id = SearchKota(K,*TK);
    if (id <= 32){
        if (Owner(*TK,id) == PlayerId(PTurn)){
            hargajualbank = priceSell(City(*TK,id)) * 0.75;
            Money(PTurn) += hargajualbank;
            Kekayaan(PTurn) -= priceCity(City(*TK,id));
            Owner(*TK,id) = '0';
            isOffered(*TK,id) = false;
            printf("  Kota dijual ke bank seharga %d\n",hargajualbank);
            printf("  Uangmu sekarang %d\n\n",Money(PTurn));
        }else{
            printf("  Kota ini bukan milikmu!\n\n");
        }
    }else{
        printf("  Tidak ada kota dengan nama itu!\n\n");
    }
}

void showOffered (TabKota TK)
{
    int i,cnt;
    cnt = 0;
    for (i=1;i<=32;i++)
    {
        if (isOffered(TK,i) == true){
            cnt ++;
        }
    }
    if (cnt > 0){
        printf("  Kota-kota yang ada dalam List Offered:\n\n");
        for (i=1; i<=32; i++)
        {
            if (isOffered(TK,i) == true){
                PrintInfoKota(TK,i);
            }
        }
    }else{
        printf("  Tidak ada kota dalam List Offered\n\n");
    }
}

void buyoffered (Kata K, TabKota *TK)
{
    int id;
    long long hargabeli;
    AddressPl Plyr;

    id = SearchKota(K,*TK);
    if (id <= 32){
        if (isOffered(*TK,id) == true){
            hargabeli = priceSell(City(*TK,id));
            if (Money(PTurn) >= hargabeli){
                Money(PTurn) -= hargabeli;
                Kekayaan(PTurn) += priceCity(City(*TK,id));
                Plyr = First(Turn);
                while (Owner(*TK,id) != PlayerId(Plyr)){
                    Plyr = Next(Plyr);
                }
                Money(Plyr) += hargabeli;
                Kekayaan(Plyr) -= priceCity(City(*TK,id));
                Owner(*TK,id) = PlayerId(PTurn);
                isOffered(*TK,id) = false;
                printf("  Kota ini anda beli dengan harga %lld\n",hargabeli);
                printf("  Uangmu sekarang %d\n\n",Money(PTurn));
            }else{
                printf("  Uangmu tidak cukup!\n\n");
            }
        }else{
            printf("  Kota ini tidak ada di List Offered!\n\n");
        }
    }else{
        printf("  Tidak ada kota dengan nama itu!\n\n");
    }
}

void quicksort(long long x[3], char y[3], int first, int last)
{
    int i, j, k;
    long long temp;

    if (first < last) {
        k = first;
        i = first;
        j = last;
        while (i < j){
            while ((x[i] <= x[k]) && (i < last)) {
                i++;
            }
            while (x[j] > x[k]) {
                j--;
            }
            if (i < j){
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
                temp = y[i];
                y[i] = y[j];
                y[j] = temp;
             }
         }
         temp = x[k];
         x[k] = x[j];
         x[j] = temp;
         temp = y[k];
         y[k] = y[j];
         y[j] = temp;
         quicksort(x, y, first, j-1);
         quicksort(x, y, j+1, last);
    }
}

void Save (ListBoard LB, TabKota TK, SKata K)
{
    FILE *fosave;
    Address p = First(LB);
    SKata SaveFName;
    strcpy(SaveFName,K);
    strcat(SaveFName,".txt");
    fosave = fopen(SaveFName,"w");
    int i;

    while (p != Last(LB))
    {
        fprintf(fosave, "%d\n",Type(p));
        if (Type(p) == 1){
            fprintf(fosave,"%s",NamaKota(TK,Id(p)));
            fprintf(fosave,"%d\n",Price(TK,Id(p)));
            fprintf(fosave,"%d\n",isRekreasi(TK,Id(p)));
            fprintf(fosave,"%d\n",Block(TK,Id(p)));
            fprintf(fosave,"%d\n",Level(TK,Id(p)));
            fprintf(fosave,"%c\n",Owner(TK,Id(p)));
            fprintf(fosave,"%d\n",isOffered(TK,Id(p)));
            fprintf(fosave,"%d\n",NamaKota(TK,Id(p)).Length);
        }
        fprintf(fosave,"\n");
        p = Next(p);
    }
    fprintf(fosave, "%d\n",Type(p));
    if (Type(p) == 1){
        fprintf(fosave,"%s",NamaKota(TK,Id(p)));
        fprintf(fosave,"%d\n",Price(TK,Id(p)));
        fprintf(fosave,"%d\n",isRekreasi(TK,Id(p)));
        fprintf(fosave,"%d\n",Block(TK,Id(p)));
        fprintf(fosave,"%d\n",Level(TK,Id(p)));
        fprintf(fosave,"%c\n",Owner(TK,Id(p)));
        fprintf(fosave,"%d\n",isOffered(TK,Id(p)));
        fprintf(fosave,"%d\n",NamaKota(TK,Id(p)).Length);
    }
    fprintf(fosave,"\n");
    fprintf(fosave, "%d\n",ValUndef);
    fprintf(fosave,"\n");
    //SAVE PEMAIN
    fprintf(fosave, "%d\n",jumlahPemain);
    fprintf(fosave,"\n");
    AddressPl plyr;
    plyr = First(Turn);
    for (i=1; i<=jumlahPemain; i++)
    {
        fprintf(fosave,"%d\n",Position(plyr));
        fprintf(fosave,"%lld\n",Money(plyr));
        fprintf(fosave,"%lld\n",Kekayaan(plyr));
        fprintf(fosave,"%d\n",CardFreePrison(plyr));
        fprintf(fosave,"%d\n",CardFreeTax(plyr));
        fprintf(fosave,"%d\n",CardProtect(plyr));
        fprintf(fosave,"%d\n",CardOff(plyr));
        fprintf(fosave,"%c\n",PlayerId(plyr));
        fprintf(fosave,"%d\n",Jail(plyr));
        fprintf(fosave,"%d\n",MovWorldTravel(plyr));
        fprintf(fosave,"\n");
        plyr = Next(plyr);
    }
    //SAVE TURN
    fprintf(fosave,"%c\n",PlayerId(PTurn));
    fprintf(fosave,"\n");
    //SAVE CHANCE
    for (i=0;i<=4;i++)
    {
        fprintf(fosave,"%d\n",C.el[i]);
    }
    fclose(fosave);
    printf("File telah disave dalam file %s\n\n",SaveFName);
}

boolean Load (ListBoard *LB,TabKota *TK, SKata K)
{
    FILE *fisave;
    Address p;
    int i;
	Petak ipt;
	int dummy;
    SKata LoadFName;

    jumRek = 0;
    strcpy(LoadFName,K);
    strcat(LoadFName,".txt");
	i=1;
    p = First(*LB);
	fisave = fopen(LoadFName,"r");
	if (fisave){
        fscanf(fisave,"%d\n", &ipt.type);
        CreateList(LB);
        //LOAD BOARD
        while (ipt.type != ValUndef)
        {
            ipt.id = i;
            InsVLast(LB,ipt);
            if (ipt.type == 1){
                fgets(TK->TK[i].name.TabKata, NMax, fisave);
                fscanf(fisave,"%d\n",&(Price(*TK,i)));
                fscanf(fisave,"%d\n",&(isRekreasi(*TK,i)));
                fscanf(fisave,"%d\n",&(Block(*TK,i)));
                fscanf(fisave,"%d\n",&(Level(*TK,i)));
                fscanf(fisave,"%c\n",&(Owner(*TK,i)));
                fscanf(fisave,"%d\n",&(isOffered(*TK,i)));
                fscanf(fisave,"%d\n",&(TK->TK[i].name.Length));
                if (isRekreasi(*TK,i) == true){
                    jumRek++;
                }
            }
            i++;
            fscanf(fisave,"\n");
            fscanf(fisave,"%d\n", &ipt.type);
        }
        //LOAD PLAYER
        AddressPl plyr;
        fscanf(fisave,"%d\n",&jumlahPemain);
        DeleteAllPlayer();
        InitNumPlayer(jumlahPemain);

        plyr = First(Turn);
        for (i=1;i<=jumlahPemain;i++)
        {
            fscanf(fisave,"%d\n",&Position(plyr));
            fscanf(fisave,"%d\n",&Money(plyr));
            fscanf(fisave,"%d\n",&Kekayaan(plyr));
            fscanf(fisave,"%d\n",&CardFreePrison(plyr));
            fscanf(fisave,"%d\n",&CardFreeTax(plyr));
            fscanf(fisave,"%d\n",&CardProtect(plyr));
            fscanf(fisave,"%d\n",&CardOff(plyr));
            fscanf(fisave,"%c\n",&PlayerId(plyr));
            fscanf(fisave,"%d\n",&Jail(plyr));
            fscanf(fisave,"%d\n",&MovWorldTravel(plyr));
            plyr = Next(plyr);
        }
        //LOAD TURN
        char CTurn;
        fscanf(fisave,"%c\n",&CTurn);
        PTurn = First(Turn);
        while (CTurn != PlayerId(PTurn))
        {
            PTurn = Next(PTurn);
        }
        //LOAD CHANCE
        for (i=0;i<=4;i++)
        {
            fscanf(fisave,"%d\n",&C.el[i]);
        }

        printf("File %s telah diload\n",LoadFName);
        return true;
	}else{
        printf("Nama file tidak ditemukan!\n");
        return false;
	}
	fclose(fisave);
}

void removeOffered(TabKota *TK,Player P)
{
    int id;
    for (id=1;id<=32;id++) {
        if (isOffered(*TK,id) && Owner(*TK,id)==P.playerId){
            isOffered(*TK,id) = false;
        }
    }
}

boolean isWinTour(TabKota Kota)
{
    boolean valid = false;
    int jumRekPl,j,i;
    AddressPl Plyr;
    Plyr = First(Turn);
    i=1;
    while ((i<=jumlahPemain) && (valid == false))
    {
        jumRekPl = 0;
        for (j=1; j<=jumPetak; j++){
            if ((isRekreasi(Kota,j) == true) && (Owner(Kota,j) == PlayerId(Plyr))){
                jumRekPl ++;
            }
        }
        if (jumRekPl == jumRek){
            valid = true;
            printf("  Player %c memenangkan game karena Tour\n",PlayerId(Plyr));
        }
        Plyr = Next(Plyr);
        i++;
    }
    return valid;
}

boolean isWinBlock(TabKota Kota)
{
    boolean valid = false;
    int jumBlockPl,k,j,i,temp;
    AddressPl Plyr = First(Turn);
    i = 1;
    while ((i <= 1) && (valid == false))
    {
        jumBlockPl = 0;
        for (j=1; j<=3; j++){
            temp = 0;
            for (k=1; k<=jumPetak; k++){
                if ((Block(Kota,k) == j) && (Owner(Kota,k) == PlayerId(Plyr))){
                    temp ++;
                }
            }
            temp /= 3;
            jumBlockPl += temp;
        }
        if (jumBlockPl >= 3){
            valid = true;
            printf("  Player %c memenangkan game karena Triple Monopoly\n",PlayerId(Plyr));
        }
        i++;
        Plyr = Next(Plyr);
    }
    return valid;
}

void bangkrut(Player P,TabKota *TK,ListPlayer *Turn)
{
    printf("  Anda Bangkrut!\n");
    returnCards(P,&C);
    removeOffered(TK,P);
    DeleteAllOwnedBuildings(TK,P);
    deletePlayer(Turn,P);
    jumlahPemain--;
    rolled=true;
    EndTurn();
}
