#include "save.h"

void Save (ListBoard LB, TabKota TK, SKata K)
{
    FILE *fosave;
    Address p = First(LB);
    SKata SaveFName;
    strcpy(SaveFName,K);
    strcat(SaveFName,".txt");
    //strcat("SaveFiles/",SaveFName);
    fosave = fopen(SaveFName,"w");
    int i;

    //SAVE BOARD
    while (p != Last(LB))
    {
        fprintf(fosave, "%d\n",Type(p));
        if (Type(p) == 1){
            fprintf(fosave,"%s",NamaKota(TK,Id(p)));
            fprintf(fosave,"%d\n",Price(TK,Id(p)));
            fprintf(fosave,"%d\n",isRekreasi(TK,Id(p)));
            fprintf(fosave,"%d\n",Block(TK,Id(p)));
            fprintf(fosave,"%d\n",Level(TK,Id(p)));
            fprintf(fosave,"%d\n",Owner(TK,Id(p)));
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
        fprintf(fosave,"%d\n",Owner(TK,Id(p)));
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

    fclose(fosave);

    printf("File telah disave dalam file %s\n",SaveFName);
}

boolean Load (ListBoard *LB,TabKota *TK, SKata K)
{
    FILE *fisave;
    Address p;
    int i;
	Petak ipt;
	int dummy;
    SKata LoadFName;

    strcpy(LoadFName,K);
    strcat(LoadFName,".txt");
    //strcat("SaveFiles/",LoadFName);
	i=1;
    p = First(*LB);
	fisave = fopen(LoadFName,"r");
	if (fisave){
        fscanf(fisave,"%d\n", &ipt.type);
        CreateList(LB);
        while (ipt.type != ValUndef)
        {
            //printf("load\n");
            ipt.id = i;
            InsVLast(LB,ipt);
            //printf("\n");
            //printf("First= %d\n",Info(First(*LB)).type);
            //printf("IsEmpty = %d\n",IsListEmpty(*LB));
            //printf("type: %d\n",ipt.type);
            //printf("id  : %d\n",ipt.id);
            if (ipt.type == 1){
                //printf("masukn\n");
                fgets(TK->TK[i].name.TabKata, NMax, fisave);
                //printf("nama : %s",TK->TK[i].name);
                fscanf(fisave,"%d\n",&(Price(*TK,i)));
                //printf("harga: %d\n",TK->TK[i].price);
                fscanf(fisave,"%d\n",&(isRekreasi(*TK,i)));
                //printf("rekreasi: %d\n",TK->TK[i].rekreasi);
                fscanf(fisave,"%d\n",&(Block(*TK,i)));
                //printf("block: %d\n",TK->TK[i].block);
                fscanf(fisave,"%d\n",&(Level(*TK,i)));
                //printf("level: %d\n",Level(*TK,i));
                fscanf(fisave,"%d\n",&(Owner(*TK,i)));
                //printf("owner: %d\n",Owner(*TK,i));
                fscanf(fisave,"%d\n",&(TK->TK[i].name.Length));
            }
            //fscanf(fisave,"\n");
            i++;
            //scanf("%d",&dummy);
            fscanf(fisave,"\n");
            fscanf(fisave,"%d\n", &ipt.type);
        }
        AddressPl plyr;
        //printf("Reading Jumlah Player\n");
        fscanf(fisave,"%d\n",&jumlahPemain);
        DeleteAllPlayer();
        InitNumPlayer(jumlahPemain);

        plyr = First(Turn);
        printf("Reading INfo player\n");
        for (i=1;i<=jumlahPemain;i++)
        {
            //printf("Read %d\n",i);
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
        printf("File %s telah diload\n",LoadFName);
        return true;
	}else{
        printf("Nama file tidak ditemukan!\n");
        return false;
	}
	fclose(fisave);
}
