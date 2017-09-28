/*##########################################################*/
/*HW07_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 14,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

int
find_size(const char *string);
int
char_number(const char *string, const char *wish_to_find);


int
main()
{
	char string[30], wish_to_find[30];	


	scanf("%s", string);
	printf("%d\n", find_size(string));

	scanf("%s", wish_to_find);
	printf("%d\n", char_number(string, wish_to_find));

	return 0;




}
int
find_size(const char *string)
{
	if(string[0] != '\0')
		return 1 + find_size(&string[1]);
	else
		return 0;
}
int
char_number(const char *string, const char *wish_to_find)
{
}
/*##########################################################*/
/*		End of HW07_Yasin_Tulumen_121044020_part1			*/
/*##########################################################*/
