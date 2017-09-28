/*##########################################################*/
/*HW02_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on February 26,2015				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*bilgisayarin tuttugu sayinin kullanici tarafindan 		*/
/*tahmin edilmesi oyunu										*/
/*Inputs:													*/
/*	-kullanici tarafindan tahmin edilen sayi				*/
/*Outputs:													*/
/*	-max 3 defa oynanmasi sonunda kazanilip kazanilmama		*/
/*	-sonucu													*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>

/*tutulan sayiyla girilen sayinin yakinligi*/
#define TOOFAR 5
#define FAR 3
#define CLOSE 2
#define EQUAL 0

/*tutulan sayinin olusturulmasi*/
int rng();
/*aradaki farkin hesaplanmasi*/
int CalculateTheDifference(int number, int guess);
/*aradaki farka gore kullanicinin uyarilmasi*/
int WarnThePlayer(int diff);

int
main()
{
	int guess, number, var;

	printf("\nWelcome to Guessing An Integer Number game!\n");
	printf("***Please enter a number between 1 to 10***\n");

	/*kullanicidan sayinin alinmasi*/
	scanf("%d",&guess);

	/*eger sayi belirtilen araliklar disindaysa hata mesaji basilmasi*/
	/*ve cikilmasi*/
	if(guess < 1 || guess > 10)
	{
		printf("You have entered unacceptable number !\n");
		printf("Program terminating !\n");
		return 0;
	}

	/*bilgisayar tarafindan belirlenen sayilarin number degiskenine atanmasi*/
	number = rng();
	/*aradaki farkin bulunup sonucun var degiskenine atanmasi*/
	var = CalculateTheDifference(number, guess);

	/*eger aradaki fark 0'dan farkli ise kullaniciya ikinci hakkin verilmesi*/
	if (var != 0)
	{
		printf("Please try again:\n");
		scanf("%d", &guess);
		var = CalculateTheDifference(number, guess);
		
		/*fark yine 0'dan farkli ise kullaniciya bir sansin daha verilmesi*/
		if (var != 0)
		{
			printf("Please try again:\n");
			scanf("%d", &guess);
			var = CalculateTheDifference(number, guess);
		}
	}

	printf("program terminating.see you soon...\n\n");
	return 0;
}

int rng()
{
	int number;

	/*her defasinda farkli sayilarin tutulmasi icin*/
	/*bilgisayar saatinin random fonksiyonu degiskenine atanmasi*/
	srand(time(NULL));
	/*9'a gore modun alinip 1 eklenerek 1-10 arasinda sayilarin secilmesi*/
	number = rand() % 9 + 1;

	return number;
}
int CalculateTheDifference(int number, int guess)
{
	int diff, warn;

	/*aradaki farkin bulunmasi ve eger fark negatif ise mutlak degerinin alinmasi islemi*/
	diff = number - guess;
	diff = abs(diff);
	
	/*warntheplayer fonksiyonuna aradaki fark gonderilerek buna gore uyarinin olusturulmasi*/
	warn = WarnThePlayer(diff);

	return warn;

}
int WarnThePlayer(int diff)
{
	/*eger aradaki fark 0 ise oyunun kazanildigi anlamina gelir*/
	if(diff == EQUAL)
	{
		printf("Congratulations.You WIN !\n");
		return 0;
	}
	/*fark 5'ten buyuk ise bu islem yapilacak*/
	/*once 3'ten degilde 5'ten buyuklugun kontrol edilme sebebi*/
	/*eger fark 6 ise ve biz once 3'ten buyuklugu kontrol edersek*/
	/*if-else if yapisiyla yazdigimiz icin 5'ten buyuklugu kontrol etmeyecektir*/
	else if(diff >= TOOFAR)
	{
		printf("You are too far from the number.\n");
		return 1;
	}
	else if(diff >= FAR)
	{
		printf("You are far from the number.\n");
		return 1;
	}
	else if(diff <= CLOSE)
	{
		printf("You are close to the number\n");
		return 1;
	}
	else
		return 1;
	/*sifir disindaki butun return degerleri oyunun kazanilmadigi ve tekrar hak verilmesini*/
	/* veya sonlandirilmasini belirtir*/
}
/*##########################################################*/
/*		End of HW02_Yasin_Tulumen_121044020_part1			*/
/*##########################################################*/