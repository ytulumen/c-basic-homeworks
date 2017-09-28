/*##########################################################*/
/*HW05_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on March 23,2015  				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*iki aracin verilen hız ve kütle degerlerine gore			*/
/*carpisma oncesi ve sonrasini yazdiran program				*/
/*Inputs:													*/
/*	-hizlar, arac isimleri ve kütleler						*/
/*Outputs:													*/
/*	-carpisma öncesi ve sonrasinin ekrana yazdirilmasi	 	*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

#define road_length 50

typedef enum
{
	PLAY, CRASH, END 
}object_state;

void
get_info(char *object1, double *speed1,
	int *weight1, char *object2, double *speed2,
	int *weight2);
void
make_move(char *object1, double *position1, double *speed1,
	int weight1, char *object2, double *position2, double *speed2,
	int weight2, object_state *game_state);
double
car_crash_time(double position1, double position2, double speed1, double speed2);
void
print_game_state(char object1, double position1, char object2, double position2,
	object_state game_state);


int
main()
{
	char object1, object2;
	int weight1, weight2;
	double position1=0, position2=49, speed1, speed2, crash_time;
	object_state game_state = PLAY;

	/*inputlarin alinmasi icin get_info fonksiyonu cagirilacak*/
	get_info(&object1, &speed1, &weight1, &object2, &speed2, &weight2);

	/*game_state'e end atanana kadar dongu dondurulecek*/
	while(game_state != END)
	{
		crash_time = car_crash_time(position1, position2, speed1, speed2);
		print_game_state(object1, position1, object2, position2, game_state);
		make_move(&object1, &position1, &speed1, weight1, &object2, &position2, &speed2, weight2, &game_state);
	}

	return 0;
}
void
get_info(char *object1, double *speed1, int *weight1, char *object2, double *speed2, int *weight2)
{
	printf("Enter a car1 and car2 name:\n");
	scanf(" %c %c", object1, object2);

	printf("Enter a car1 speed and car2 speed:\n");
	scanf("%lf %lf", speed1, speed2);

	printf("Enter a car1 weight and car2 weight:\n");
	scanf(" %d %d", weight1, weight2);
}
void
make_move(char *object1, double *position1, double *speed1,
	int weight1, char *object2, double *position2, double *speed2,
	int weight2, object_state *game_state)
{
	double a,b;

	/*her iki arac da ters yonde hareket ediyorsa bu if ile program sonlandirilacak*/
	if(*speed1 < 0 && *speed2 > 0)
		*game_state = END;

	/*herhangi bir arac ters yone gidiyorsa o aracin hizi 0 olarak atanacak*/
	/*ve yazdirilirken hareket etmeyecek*/
	if(*speed1 < 0)
		*speed1 = 0;
	if(*speed2 > 0)
		*speed2 = 0;

	/*henuz carpisma gerceklesmediyse ve game_state play ise carpisma anina kadar bu if gerceklesecek*/
	if((*position2 - *position1) > 0 && *game_state == PLAY)
	{

		*game_state = PLAY;	
		/*carpisma anina kadar her iki aracinda pozisyonlari hizlariyla orantili olarak degistirilecek*/
		*position1 += *speed1;
		*position2 += *speed2;
	}
	/*carpismadan hemen once muhtemelen yanlizca bir defaligina bu if calisacak*/
	else if((*position2 - *position1) < 1 && *game_state == PLAY)
	{
		/*game_state'in degeri degistirilecek.dolayisiyla bu ve ustteki if bir daha calismayacak*/
		if(*speed1 > 0 && *speed2 < 0 )
			*game_state = CRASH;
		/*carpismadan sonrasi icin degisken olarak object_1 kullanilacak*/
		*object1 = 'X'; 
		/*momentum hesaplamasi icin speed2 negatiften pozitife cevriliyor.*/
		/*(abs()fonsiyonunun input parametresi int oldugu icin)*/
		*speed2 *= (-1.0);

		/*eger ikinci aracin momentumu daha buyukse bu if calisacak ve ikinci aracin pozisyon*/
		/*bilgileri kullanilarak onun yonunde hareket devam edecekler*/
		if((((double)weight1) * (*speed1)) < (((double)weight2) * (*speed2)))
			*position1 = 0.0;
		/*esnek olmayan carpismada momentumlar esitse cisimler oldugu yerde kalir*/
		else if((((double)weight1) * (*speed1)) == (((double)weight2) * (*speed2)))
		{
			/*carpisma ani yazdirilacak*/
			print_game_state(*object1, *position1, *object2, *position2, *game_state);
			*game_state = END;
		}
		/*her iki durum da gecersiz ise bu birinci aracin momentumu daha buyuk oldugu anlamina gelir*/
		else
			*position2 = 0.0;

		/*birlikte hareket edecekleri hiz hesaplanacak*/
		*speed1 = (((double)weight1 * (*speed1)) + ((double)weight2 * (*speed2))) / ((double)(weight1 + weight2));
		/*hiz integera cast edilecek ara degerlerin olusmamasi icin*/
		/*speed1 = (int)*speed1;*/		
	}
	else if((*game_state) == CRASH)
	{
		/*birinci aracin momentumu daha buyukse sag tarafa dogru hareket edecekler*/
		if((*position2) == 0.0)
		{
			(*position1) += (*speed1);
			/*eger yolun siniri asilirsa program bitirilecek*/
			if((*position1) >= ((double)road_length ))
				(*game_state) = END;
		}
		/*ikinci aracin momentumu daha buyukse sol tarafa dogru hareket edecekler*/
		else if((*position1) == 0.0) 
		{	
			(*position2) -= (*speed1);
			/*eger yolun siniri asilirsa program bitirilecek*/
			if(((*position2) <= 0.0))
				(*game_state) = END;
		}
	}
}
double
car_crash_time(double position1, double position2, double speed1, double speed2)
{
	double crash_time;
	/*carpisma zamani hesaplanacak*/
	crash_time = (position2 - position1) / speed1 + (speed2*(-1));

	return crash_time;
}
void
print_game_state(char object1, double position1, char object2, double position2,
	object_state game_state)
{
	int i=0, j=0, a=1 /*a degiskeni ayni satiri iki defa yazdirmamak icin tutulacak*/;
	int space1, space2, space3 ;
	/*carpismadan once bu if yapilacak*/
	if(game_state == PLAY)
	{
		if(position2 - position1 > 0)
		{
			a=0;
			/*ilk aractan onceki bosluklar bu dongude basilacak*/
			for(space1=0; space1<position1 ; ++space1)
			{
				printf("_");
			}
			printf("%c", object1);
			/*iki arac arasindaki bosluk bu dongude basilacak*/
			for(space2=(position1+1); space2<position2 ; ++space2)
			{
				printf("_");
			}
			printf("%c", object2);
			/*ikinci aractan sonraki bosluk bu dongude basilacak*/
			for(space3=(position2+1); space3<road_length ; ++space3)
			{
				printf("_");
			}
			printf("\n");
		}
	}
	else if(game_state == CRASH)
	{
		a=0;
		/*eger ikinci aracin momentumu daha buyukse bu if calisacak*/
		if(position1==0.0)
		{
			/*carpismadan onceki bosluklar icin bu dongu kullanilacak*/
			for(space1=0 ; space1 < position2 ; ++space1)
				printf("_");
			printf("%c", object1);
			/*carpismadan sonraki bosluklar icin bu dongu kullanilacak*/
			for(space2 = position2+1; space2 < road_length ; ++space2)
				printf("_");
		}
		/*eger ilk aracin momentumu daha buyukse bu if calisacak*/
		else if(position2==0.0)
		{	
			/*carpismadan onceki bosluklar icin bu dongu kullanilacak*/
			for(space1=0 ; space1 < position1 ; ++space1)
				printf("_");
			printf("%c", object1);
			/*carpismadan sonraki bosluklar icin bu dongu kullanilacak*/
			for(space2=position1+1 ; space2 < road_length ; ++space2)
				printf("_");

		}
		/*eger momentumlar esitse bu if ile son durum basilacak*/
		else
		{
			/*carpismadan onceki bosluklar icin bu dongu kullanilacak*/
			for(space1=0 ; space1 < position1-1 ; ++space1)
				printf("_");
			printf("%c", object1);
			/*carpismadan sonraki bosluklar icin bu dongu kullanilacak*/
			for(space2=position1 ; space2 < road_length ; ++space2)
				printf("_");
		}
		printf("\n");
	}

		
	if(a==0)
	{
		/*bu dongude rakamlar basilacak.bu sayede hareket yazdirilmasinin dogrulugu kontrol edilecek*/
		for(j=0 ; j<road_length ; ++j)
		{
			if(i > 9)
				i=0;
			printf("%d", i);
			++i;
		}
		printf("\n");
	}
	a=1;
}
/*##########################################################*/
/*		End of HW05_Yasin_Tulumen_121044020_part1.c			*/
/*##########################################################*/
















