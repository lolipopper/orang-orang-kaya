#include "../header/kota.h"

void buy(Player *P, Kota *K)
{
	Money(*P)-=Price(*K);
	Kekayaan(*P)+=Price(*K);
	Owner(*K)=*P;
	Level(*K)++;
}

void payRent(Player *P,Kota K)
{
	Money(*P)-=Price(K);
	Kekayaan(*P)-=Price(K);
	Money(Owner(K))+=Price(K);
	Kekayaan(Owner(K))+=Price(K);
}

void upgrade(Kota *K)
{
	Money(Owner(*K))-=UpgradePrice(*K);
	Level(*K)++;
}

int UpgradePrice(Kota K)
{
	return Price(K);
}