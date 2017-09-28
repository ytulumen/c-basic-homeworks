/*##########################################################*/
/*HW05_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on March 23,2015  				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*tanimlanan bir arrayin en buyuk, en buyuk ikinci,			*/
/*toplam degeri, tanimlanan sayilarin sayisi,				*/
/*ve aranan sayilarin kontrol bilgisi						*/
/*Inputs:													*/
/*	-array, size ve value degerleri							*/
/*Outputs:													*/
/*	-arrayin en buyuk, en buyuk ikinci, toplam degeri	 	*/
/*	-tanimlanan sayilarin sayisi ve aranan sayilarin		*/
/*	-kontrolu bilgileri										*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

typedef enum
	{TRUE=1, FALSE=0} BOOL;

int
max_array(int array[], int n);
int
second_max_array(int array[], int n);
int
sum_all_array(int array[], int n);
int
count_array(int array[], int n, int value);
BOOL
search_array(int array[], int n, int value);

int
main()
{
	int array[]={6,8,3,3,12,8,3,8,2}, size=9;
	int max, nd_max, sum_ar, co_ar, value=8 ;

	max = max_array(array, size);
	printf("\n++++++++++++++++++++++\n");
	printf("Maksimum array is %d\n", max);

	nd_max =second_max_array(array, size);
	printf("++++++++++++++++++++++\n");
	printf("Maksimum second array is %d\n", nd_max);

	sum_ar = sum_all_array(array, size);
	printf("++++++++++++++++++++++\n");
	printf("Sum of all array is %d\n", sum_ar);

	co_ar = count_array(array, size, value=6);
	printf("++++++++++++++++++++++\n");
	printf("Count of value %d is %d\n",value, co_ar);
	co_ar = count_array(array, size, value=8);
	printf("Count of value %d is %d\n",value, co_ar);
	co_ar = count_array(array, size, value=3);
	printf("Count of value %d is %d\n",value, co_ar);

	printf("++++++++++++++++++++++\n");
	if(FALSE==search_array(array, size, value=2))
		printf("%d did not in array\n", value);
	if(FALSE==search_array(array, size, value=8))
		printf("%d did not in array\n", value);
	if(FALSE==search_array(array, size, value=12))
		printf("%d did not in array\n", value);

	printf("++++++++++++++++++++++\n");
	return 0;
}
int
max_array(int array[], int n)
{
	int i, max = array[0];

	/*arrayi ilk elemanından itibaren kontrol edecek*/
	for(i=1 ; i < n; ++i)
		/*if statement ile en buyuk eleman bulunacak*/
		if(array[i] > max )
			max = array[i];
	return max;
}
int
second_max_array(int array[], int n)
{
	int i, max, nd_max = array[0];

	/*max_array fonksiyonu ile en buyuk eleman bulunacak*/
	max = max_array(array, n);

	for(i=1 ; i < n ; ++i)
	{
		/*en buyuk eleman ile arasinda en az fark bulunan*/
		/*ve en buyuk elemana esit olmayan sayi ikinci en buyuktur*/
		if((max - array[i]) < (max - nd_max))
			if(max != array[i])
				nd_max = array[i];
	}
	return nd_max;
}
int
sum_all_array(int array[], int n)
{
	int i, sum=0;

	/*arrayin tum elemanlari sum icinde tek tek toplanacak*/
	for(i=0 ; i < n ; ++i)
		sum += array[i];
	return sum;
}
int
count_array(int array[], int n, int value)
{
	int i, counter=0;

	/*arrayin tum elemanlari kontrol edilecek*/
	/*eger value'ye esit ise counter artirilacak*/
	for(i=0 ; i < n ; ++i)
		if(array[i] == value)
			++counter;
	return counter;
}
BOOL
search_array(int array[], int n, int value)
{
	int i;

	/*arrayinn tum elemanlari kontrol edilecek*/
	/*istenen degere esit olan varsa return edilecek*/
	for(i=0 ; i < n ; ++i)
	{
		if(array[i] == value)
		{
			printf("%d is at [%d]\n", value, i);
			return TRUE;
		}
	}
	return FALSE;
}
/*##########################################################*/
/*		End of HW05_Yasin_Tulumen_121044020_part2.c			*/
/*##########################################################*/











