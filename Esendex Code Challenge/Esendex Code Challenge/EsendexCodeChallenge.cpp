// EsendexCodingChallenge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Esendex_Code_Challenge.h"

int main()
{
	double overallTotal;
	ECC* checkout = new ECC("pricingRules");

	checkout->ScanItems();
	overallTotal = checkout->CalculateTotalPrice();
	system("pause");

	return 0;
}


