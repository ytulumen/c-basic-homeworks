/************************************************************************/
/*                            bonusPart.c				*/
/*----------------------------------------------------------------------*/
/*written by Ahmet Durna in 10.03.2015					*/ 
/*									*/
/*Description								*/
/*-----------								*/
/*     The program uses the fuction that draws a vertical diagram of a  */
/*   bouncing ball..                                			*/
/*Inputs:								*/
/*  -the first height of the ball					*/
/*  -the height of one feet						*/
/*  -the character used to draw the peak points of the ball		*/
/*  -the character used to draw the path points of the ball		*/
/*Outputs:								*/
/*  -Output the result and and the total number of the character used	*/
/*######################################################################*/
/*									*/
/*----------------------------------------------------------------------*/
/*				Includes				*/
/*----------------------------------------------------------------------*/
#include <stdio.h>

/*---------------------------------------------------------------------------------------------------*/
/*                        Prototypes                                                                 */
/*---------------------------------------------------------------------------------------------------*/
int draw_hor_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point);
int draw_diag_step(int, int height, int feet_height, char the_peak_point, char the_road_point);
int finish_diag(int, int);

int main()
{
	int i,first_height,feet_height,total;
	char the_peak_point,the_path_point;

	printf("please insert first height, feet height, the peak point and the path point:");
	scanf("%d %d %c %c",&first_height,&feet_height,&the_peak_point,&the_path_point);
	printf("\n^\n");
	total=draw_hor_diag_of_bb(first_height,feet_height,the_peak_point,the_path_point);
	i=finish_diag(first_height,feet_height);
	printf("\nThe total number of the character used:%d\n",total);
	return 0;
}

/*----------------------------------------------------------------------------------------------------*/
/*                        Implementations                                                             */
/*----------------------------------------------------------------------------------------------------*/

int draw_hor_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point)
{
	int i=0,j=0,k=0,total=0;
	printf("|");

        /*Top peak point .....................................*/
	for (j=0;j<first_height;j++)              /*Space Block*/
		printf(" ");
	printf("%c\n",the_peak_point);            /* Peak line */
	total+=1;
 
        /*The loop is starting at this part....................*/
	for (i=1;i<=first_height;i++)
	{
		for (j=0;j<feet_height;j++)
		{
			printf("|");
			for (k=0;k<i;k++)
				total+=draw_diag_step(i,first_height, k, the_peak_point, the_road_point);     /*Step part*/
			if(j==(feet_height-1)&&(i!=first_height))
			{       /*If there is a peak......................................*/
				for (k=0;k<(first_height-i);k++)             /*Space Block*/
					printf(" ");
				printf("%c",the_peak_point);                 /* Peak line */             
				total+=1;
			}
			printf("\n");
		}
	}

	return total;
}

int draw_diag_step(int sira, int height, int tur, char the_peak_point, char the_road_point)
{
	int j=0,total=0;
	for (j=0;j<(height-sira);j++)
	{
		printf(" ");
	}
	printf("%c",the_road_point);
	total+=1;
	for (j=0;j<(2*sira-1-(2*tur));j++)
	{
		printf(" ");
	}
	printf("%c",the_road_point);
	total+=1;
	for (j=0;j<(height-sira);j++)
	{
		printf(" ");
	}
	return total;
}


int finish_diag(int first_height,int feet_height)
{
	int i=0,count=0;
	printf("|");
	for (i=1;i<=first_height;i++)
		count+=first_height;
	count=count*2+first_height;
	for (i=0;i<count;i++)
		printf("-");
	
	printf(">\n");

	if(first_height>0)
                return 1;
        else   return 0;
}
