#include <stdio.h>
#include <stdlib.h>

#define MIN_HEI 1

double calculate_the_new_height(double new_height, double ratio);
double calculate_the_vertical_distance(double old_distance, double new_height);
int count_the_number(int count);
void report(double new_height, double old_distance, FILE*outfile, int count);


int
main()
{
	int first_height, count = 0;
	double ratio, new_height, old_distance;

	FILE *outfile;
	outfile = fopen("Result_Table.txt","w");

	srand(time(NULL));
	first_height = rand() % 30 + 10;
	first_height = 10;
	old_distance = (double)first_height;
	new_height = old_distance;

	srand(time(NULL));
	ratio = (double)rand() / (double)RAND_MAX;	

	while((ratio < 0.4) || (ratio > 0.8))
	{
		srand(time(NULL));
		ratio = (double)rand() / (double)RAND_MAX;
	}
	ratio = 0.75;
	fprintf(outfile, "No - The Rebouncing Height -- The Total Vertical Distance\n" );
	while(new_height > MIN_HEI)
	{
		count = count_the_number(count);
		report(new_height, old_distance, outfile, count);
		new_height = calculate_the_new_height(new_height, ratio);
		old_distance = calculate_the_vertical_distance(old_distance, new_height);
		
	}
	fprintf(outfile, "\nThe bouncing is stopped and the task completed\n" );

	return 0;
}
double
calculate_the_new_height(double new_height, double ratio)
{
	new_height = new_height * ratio;

	return new_height;
}
double
calculate_the_vertical_distance(double old_distance, double new_height)
{
	old_distance = old_distance + 2*new_height;

	return old_distance;
}
int count_the_number(int count)
{
	count++;
	return count;
}
void report(double new_height, double old_distance, FILE*outfile, int count)
{
	if(new_height > MIN_HEI)
		fprintf(outfile, "%d 			%.3f 					%.3f 			\n", count, new_height, old_distance );
}












