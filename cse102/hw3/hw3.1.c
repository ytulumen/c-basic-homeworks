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
	int guess, number, var, get=1;
	char cont;

	printf("\nWelcome to Guessing An Integer Number game!\n");
	printf("***Please enter a number between 1 to 10***\n");

	/*bilgisayar tarafindan belirlenen sayilarin number degiskenine atanmasi*/
	number = rng();

	while(get)
	{
		/*kullanicidan sayinin alinmasi*/
		scanf("%d",&guess);

		/*eger sayi belirtilen araliklar disindaysa hata mesaji basilmasi*/
		/*ve cikilmasi*/
		while(guess < 1 || guess > 10)
		{	
			printf("You have entered unacceptable number !\n");
			printf("Try again:\n");
			scanf("%d",&guess);
		}
		
		/*aradaki farkin bulunup sonucun var degiskenine atanmasi*/
		var = CalculateTheDifference(number, guess);
	
		if(var!=0)
		{
			printf("You lose...\n");
			printf("Do you want to play again? if your answer is yes enter 'P' or 'p'.\n");
			printf("if you do not want to play again enter 'e' or 'E'\n");
			scanf(" %c", &cont);
			if(cont == 'P' || cont == 'p')
			{
				get = 1;
				printf("Please enter a number between 1 to 10\n");
			}
			else if(cont == 'E' || cont == 'e')
			{
				get = 0;
			}
			else
			{
				printf("You have entered unacceptable character !\n");
				printf("Game terminating\n");
				return 0;
			}
		}
		else
		{
			printf("Do you want to play again? if your answer is yes enter 'P' or 'p'.\n");
			printf("if you do not want to play again enter 'e' or 'E'\n");
			scanf(" %c", &cont);
			if(cont == 'P' || cont == 'p')
			{
				number = rng();
				get = 1;
				printf("Please enter a number between 1 to 10\n");
			}
			else if(cont == 'E' || cont == 'e')
			{
				get = 0;
			}
			else
			{
				printf("You have entered unacceptable character !\n");
				printf("Game terminating\n");
				return 0;
			}
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