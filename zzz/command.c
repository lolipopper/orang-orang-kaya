#include "command.h"
#include "action.h"
#include "action.c"
#include "petakBoard.c"
#include "mesinkata.c"
#include "mesinkarakter.c"

Kata rolldice    = {"roll dice",     9};
Kata Buy         = {"buy",           3};
Kata showoffered = {"show offered", 12};
Kata upgrade     = {"upgrade",       7};
Kata board       = {"board",         5};
Kata leaderboard = {"leaderboard",  11};
Kata endturn     = {"end turn",      8};
Kata FreeMe      = {"free me",       7};
Kata FreeTax     = {"free tax",      8};

Kata infopetak   = {"info",          4};
Kata sellpetak   = {"sell",          4};
Kata sellbank    = {"sell bank",     9};
Kata buyoffered  = {"buy offered",  11};
Kata hostkota    = {"host",          4};
Kata travelkota  = {"travel",        6};
Kata Off         = {"off",           3};
Kata Protect     = {"protect",       7};
Kata saving      = {"save",          4};
Kata loading     = {"load",          4};

void PetakToDo(Address P) {
    if(Id(P) == 1) {
        //DoKota();
    }
    else if(Id(P) == 2) {
        //DoStart();
    }
    else if(Id(P) == 3) {
        //DoChance();
    }
    else if(Id(P) == 4) {
        //DoBonus();
    }
    else if(Id(P) == 5) {
        //DoDesertedIsland();
    }
    else if(Id(P) == 6) {
        //DoWorldCup();
    }
    else if(Id(P) == 7) {
        //DoWorldTravel();
    }
    else if(Id(P) == 8) {
        //DoTax();
    }
}

void BacaCommand(Kata *K) {
/*KAMUS*/
 //   int i;
/*ALGORITMA*/
//    i = 0;
//    STARTKATA();
    ADVKATA();
    *K = CKata;
}

void DoCommand(Kata K, ListBoard LB, TabKota Kota, Player *P) {
/*KAMUS*/
    Kata Command;
    Kata Objek;
    int i, j;
    Address B;
/*ALGORITMA*/
    if     (IsKataSama(K, rolldice)   ) {}//RollDice();
    else if(IsKataSama(K, Buy)        ) {}//buy();
    else if(IsKataSama(K, showoffered)) {}//ShowOffered();
    else if(IsKataSama(K, upgrade)    ) {}//Upgrade();
    else if(IsKataSama(K, board)      ) ShowBoard(LB, Kota);
    else if(IsKataSama(K, leaderboard)) {}//leaderBoard();
    else if(IsKataSama(K, endturn)    ) {}//EndTurn();
    else if(IsKataSama(K, FreeMe)     ) {}//freeme(P);
    else if(IsKataSama(K, FreeTax)    ) {}//freetax(P);
    else {
        i = 0;
        while(K.TabKata[i] != ' ') {
            Command.TabKata[i] = K.TabKata[i];
            i++;
        }
        j = 0;
        i++;
        if(K.TabKata[i] >= 0x61 && K.TabKata[i] <= 0x7A) {
            Command.TabKata[i-1] = ' ';
            while(K.TabKata[i] != ' ') {
                Command.TabKata[i] = K.TabKata[i];
                i++;
            }
            i++;
        }
        while(i < K.Length) {
            Objek.TabKata[j] = K.TabKata[i];
            j++;
            i++;
        }
        Objek.Length = j-1;
        B = SearchKota(LB, Kota, Objek);
        if     (IsKataSama(Command, infopetak) ) PrintInfoKota(Kota, Id(B));
        else if(IsKataSama(Command, sellpetak) ) {}//SellKota();
        else if(IsKataSama(Command, sellbank)  ) {}//SellBank();
        else if(IsKataSama(Command, buyoffered)) {}//BuyOffered();
        else if(IsKataSama(Command, hostkota)  ) {}//HostKota();
        else if(IsKataSama(Command, travelkota)) {}//TravelKota();
        else if(IsKataSama(Command, Off)       ) {}//off();
        else if(IsKataSama(Command, Protect)   ) {}//protect();
        else if(IsKataSama(Command, saving)    ) {}//Save(LB, Kota);
        else if(IsKataSama(Command, loading)   ) {}//Load(&LB, &Kota);
        else {
            printf("Error: Wrong Command\n");
        }
    }
}
