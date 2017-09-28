/*##########################################################*/
/*HW07_Yasin_Tulumen_121044020_part3.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 14,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>
#define COL_SIZE 5

typedef enum 
	{notavailable, available, right_down} Grid_t;
typedef	enum 
	{FALSE, TRUE} BOOL;

void
read_table(FILE *input_file, Grid_t table[][COL_SIZE]);
void
print_path(char path[][COL_SIZE], int n);
BOOL
find_path(Grid_t table[][COL_SIZE], char path[][COL_SIZE], int size, 
	int location_x, int location_y);

int
main()
{
	Grid_t table[10][COL_SIZE];
	char path[10][COL_SIZE] = {65};
	FILE *input_file;
	int i,j;

	for(i=0 ; i<5 ; ++i)
		for(j=0 ; j<COL_SIZE ; ++j)
			path[i][j] = '#';
		
	

	read_table(input_file, table);
	find_path(table, path, 5, 0, 0);
	print_path(path, 5);
}

void
read_table(FILE *input_file, Grid_t table[][COL_SIZE])
{
	int i,j,k;

	input_file = fopen("table.txt","r");

	for(i=0 ; i<5 ; ++i)
	{
		for(j=0 ; j<COL_SIZE ; ++j)
		{
			fscanf(input_file,"%d",&k);
			table[i][j] = k;
			printf("%d", table[i][j]);
		}
		printf("\n");
	}

}
void
print_path(char path[][COL_SIZE], int n)
{
	int i, j;

	for(i=0 ; i<n ; ++i)
	{
		for(j=0 ; j<COL_SIZE ; ++j)
			printf("%c", path[i][j]);
		printf("\n");
	}

}
BOOL
find_path(Grid_t table[][COL_SIZE], char path[][COL_SIZE], int size,
			int location_x, int location_y)
{
	int i=location_x, j=location_y, k1, k2 ;
	char ch1='*', ch2='#';

	while(i<size)
	{
		while(j<COL_SIZE)
		{

			path[i][j] = ch2;
			if(table[i][j] == available)
			{
				path[i][j] = ch1;
				if(table[i+1][j] == available  && i+1 <size)
				{
					if(table[i][j+1] == available  && j+1 <COL_SIZE)
					{
						k1=i;
						k2=j+1;
					}
					++i;
				}
				else if(table[i][j+1] == available  && j+1 <COL_SIZE)
				{


					++j;
				}
				else if((i+1 < size && j+1 < COL_SIZE) && (table[i][j+1] == notavailable && table[i+1][j] == notavailable))
				{
					i=k1;
					j=k2;
				}
				else
					++i;
			}
			else if((table[i][j] == right_down) && (i+1<size && j+1<COL_SIZE))
			{
				++i;
				++j;
			}
			else
			{
				return FALSE;
			}
		}
printf("qwe\n");
	}
	return TRUE;

}
/*##########################################################*/
/*		End of HW07_Yasin_Tulumen_121044020_part3			*/
/*##########################################################*/
