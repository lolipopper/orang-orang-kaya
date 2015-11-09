#include "mesinkarakter.h"

extern void START(FILE *fi) {
/* 	I.S. sembarang
	F.S. CC adalah karakter pertama pita (stdin)
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
	fscanf(fi,"%c",&CC);
	printf("Masuk\n");
}

extern void ADV(FILE *fi) {
/*	I.S. CC!=mark
	F.S. CC adalah karakter berikutnya yang dapat diakuisisi
		 contoh untuk pita "IF", bila CC menunjuk 'I', maka CC berikutnya adalah 'F'
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
	//ALGORITMA
	if (!EOP())
		fscanf(fi,"%c",&CC);
}

extern boolean EOP() {
/*	true jika CC==mark */
	return (CC==mark);
}
