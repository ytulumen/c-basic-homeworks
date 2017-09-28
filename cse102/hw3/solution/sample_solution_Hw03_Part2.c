/*##########################################################################*/
/*          HW03_Meltem_Cetiner_part2.c                                     */
/*_________________________________                                         */
/*                      Author    Meltem Çetiner                            */
/*                                                                          */
/*Descriptions:                                                             */
/*___________                                                               */
/*C program for “Evaluating the vertical distance of the bouncing ball”.    */
/*									    */
/*Inputs:                                                                   */
/*  - Generates a random number between 10 to 40 as the initial height of   */
/*the ball in feet (name  the variable as “first_height”)                   */
/*  – Generates a random number between 0.4 to 0.8 (name the variable as    */
/*“ratio”)								    */
/* 									    */
/*Outputs:                                                                  */
/* The program print the vertical distance at the end of the execution      */
/*  – Output the result both to						    */
/*		1.Console (in any format)				    */
/*              2.A text file named “Result_Table.txt” (numeric value only  */
/* in default precision, i.e. no output formatting                          */
/*##########################################################################*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*                         Includes                                         */
/*--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_HEIGHT 40
#define MIN_HEIGHT 10
#define MAX_RATIO 8
#define MIN_RATIO 4

#define file "Result_Table.txt"
/*--------------------------------------------------------------------------*/
/*                        Prototypes                                        */
/*--------------------------------------------------------------------------*/

double generate(int t1,int t2,int t3);
double calculate_the_new_height (double height, double ratio);
int count_the_number(double height, int counter);
double calculate_the_vertical_distance (double height, double distance);
void report( FILE *inp, int number, double rebounching_height, double total_distance,int start);



/*----------------------------------MAIN ----------------------------------------------------------*/
int main (void)
{
        double first_height, ratio , height,rebounching_height, total_distance;
	int number, counter = 0;
	FILE *inp;
	inp=fopen(file, "w");
		
	first_height = generate(40,10,1);
	ratio =  generate(8,4,10);
	printf("%f",ratio);
	total_distance = first_height;
	rebounching_height = calculate_the_new_height(first_height,ratio);
	number = count_the_number(first_height, counter);
	
	report(inp, number, first_height, total_distance,1);
	total_distance = calculate_the_vertical_distance(rebounching_height, total_distance);

	while( rebounching_height > 1)
	{
		number += count_the_number(rebounching_height, counter);
		if(rebounching_height > 1)
		        report(inp, number, rebounching_height, total_distance,0);

		rebounching_height = calculate_the_new_height(rebounching_height,ratio);
		total_distance = calculate_the_vertical_distance(rebounching_height, total_distance );	
	}
	
	printf("\nThe bouncing is stopped and the task completed...\n\n");
        fprintf(inp,"\nThe bouncing is stopped and the task completed...\n\n");

	return 0;
/*--------------------------------END_OF_MAIN-----------------------------------------------------*/
}

/*--------------------------------------------------------------------------*/
/*                        Implementations                                   */
/*--------------------------------------------------------------------------*/
/* To generate the random number*/
double generate(int t1,int t2,int t3)
{
    srand(time(NULL));
    return (double)(((rand()%(t1-t2)) + t2)/(double)t3);
    
}

/* calculates new height by mulriping height by ratio */
double calculate_the_new_height (double height, double ratio)
{
	return (height*ratio);
}

int count_the_number(double height, int counter)
{
       if(height > 1){
		counter++;
	}
	return counter;
}

/* calculates vertical distance by adding every new height over it */
double calculate_the_vertical_distance (double height, double distance)
{
	distance+=height*2;
	return distance;	
}

/*prints a report about number , the Rebounching Height , and the Total vertical Distance respectively */
void report( FILE *inp, int number, double rebounching_height, double total_distance,int start){
        if(start==1)
	{
	        printf("\nNo   The Rebounching Height   The Total vertical Distance\n");
		fprintf(inp,"\nNo   The Rebounching Height   The Total vertical Distance\n");
	}	
	
        printf("%d\t%.3f\t\t\t %.3f\n", number, rebounching_height, total_distance);
	fprintf(inp, "%d\t\t\t%.3f\t\t\t%.3f\n", number, rebounching_height, total_distance );

}
/*##########################################################################*/
/*                   End of sample code part1                               */
/*##########################################################################*/
