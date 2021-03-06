#include "../board/board.h"
#include "../chance/chance.h"
#include "../command/command.h"

int main()
{
	ListBoard LB;
	TabKota TK;
	
	
	printf("==============");
	printf("DRIVER COMMAND");
	printf("==============\n\n");
	
	makeChance(&C);
	initBoard(&LB, &TK);
	InitNumPlayer(4);
	
	Save(LB, TK, "new");
	
	//Player A
	printf("Cek ShowMoney:\n");
	ShowMoney();
	PTurn = Next(PTurn);
	printf("\n-----------------------------------------------------\n");
	
	//Player B
	printf("Cek PrintPos (pada type petak yang berbeda-beda, ketik pay jika ke penjara):\n");
	printf("  Type START:\n");
	PrintPos(TK, LB);
	printf("\n");
	printf("  Type Kota:\n");
	MoveNPetak(&TK, &LB, 1);
	printf("  Type Bonus:\n");
	MoveNPetak(&TK, &LB, 1);
	printf("  Type Penjara:\n");
	MoveNPetak(&TK, &LB, 6);
	printf("  Type Chance:\n");
	MoveNPetak(&TK, &LB, 4);
	printf("  Type World Cup:\n");
	MoveNPetak(&TK, &LB, 4);
	printf("  Type World Travel:\n");
	MoveNPetak(&TK, &LB, 8);
	
	PTurn = Next(PTurn);
	printf("\n-----------------------------------------------------\n");
	
	//Player C
	printf("Cek buy :\n");
	printf("  Beli START:\n");
	printf("> buy:\n");
	buy(&TK, &LB);
	buyupgrade = true;
	printf("  Beli Beijing:\n");
	MoveNPetak(&TK, &LB, 1);
	printf("> buy:\n");
	buy(&TK, &LB);
	buyupgrade = true;
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek upgrade :\n");
	printf("  Beijing (sudah dimiliki)\n");
	upgrade(&TK, &LB);
	buyupgrade = true;
	printf("  Bonus\n");
	MoveNPetak(&TK, &LB, 1);
	upgrade(&TK, &LB);
	buyupgrade = true;
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek sell:\n");
	printf("  sell Beijing\n");
	sell(NamaKota(TK, 2), &TK);
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek showOffered:\n");
	showOffered(TK);
	PTurn = Next(PTurn);
	printf("\n-----------------------------------------------------\n");
	
	//Player D
	printf("Cek payRent (terdapat pada prosedur MoveNPetak):\n");
	MoveNPetak(&TK, &LB, 1);
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek buyoffered:\n");
	printf("> buyOffered Beijing\n");
	buyoffered(NamaKota(TK, 2), &TK);
	buyupgrade = true;
	printf("> buyOffered Tokyo (belum dimiliki)\n");
	buyoffered(NamaKota(TK, 11), &TK);
	buyupgrade = true;
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek sellbank:\n");
	printf("> sellbank Beijing\n");
	sellbank(NamaKota(TK, 2), &TK);
	printf("> sellbank Tokyo (belum dimiliki)\n");
	sellbank(NamaKota(TK, 11), &TK);
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek EndTurn:\n");
	EndTurn();
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek Save (dengan nama testc):\n");
	Save(LB, TK, "testc");
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek Load (meload testc):\n");
	ShowBoard(LB, TK);
	Load(&LB, &TK, "testc");
	ShowBoard(LB, TK);
	printf("\n-----------------------------------------------------\n");
		
	printf("Cek isWinTour:\n");
	if (isWinTour(TK))
		printf("True\n");
	else
		printf("False\n");
	printf("\n-----------------------------------------------------\n");
	
	printf("Cek isWinBlock:\n");
	if (isWinBlock(TK))
		printf("True\n");
	else
		printf("False\n");
	printf("\n-----------------------------------------------------\n");
	return 0;
}
