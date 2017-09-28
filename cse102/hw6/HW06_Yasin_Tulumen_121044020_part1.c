/*##########################################################*/
/*HW06_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 07,2015					*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*enerji durumlarina gore calisanlara is verilmesi			*/
/*Inputs:													*/
/*	-dosyadan okunan gunluk yapilmasi gereken isler			*/
/*Outputs:													*/
/*	-dosyaya gunluk ve haftalik en cok calisan kisilerin	*/
/*	-belirlenmesi											*/
/*	-gunluk is dagilimlarinin yazilmasi						*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

/*	-hocam create_work_plan fonksiyonunda arrayde yanlis yerlere	*/
/*	-giriyorum.2 gun ugrastim sorunu cozemedim						*/
/*	-dolayisiyla diger fonksiyonlara gecemedim						*/
/*	-yorum satiri yazmadim											*/

#include <stdio.h>
#define NUM_EMPLOYEES 4
#define NUM_DAYS 7

typedef enum
{
	ALI, AYSE, FATMA, MEHMET
}employee;
typedef enum 
{
	MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY	
}day;


void
read_matrix(const char* file_name, int m[NUM_EMPLOYEES][NUM_DAYS]);
void
create_work_plan(int job_schedule[NUM_EMPLOYEES][NUM_DAYS], int m[NUM_EMPLOYEES][NUM_DAYS]);
employee
find_the_employer_of_the_day(int work_schedule[NUM_EMPLOYEES][NUM_DAYS], day day_name);
employee
find_the_employer_of_the_week(int work_schedule[NUM_EMPLOYEES][NUM_DAYS]);
void
report(const char* file_name, int job_scheduling[NUM_EMPLOYEES][NUM_DAYS]);
int
find_min(int total, int s, int f);
int
find_max(int total, int s, int f);



int
main()
{
	int job_energies[NUM_EMPLOYEES][NUM_DAYS], i, j;	
	int schedule[NUM_EMPLOYEES][NUM_DAYS];

	read_matrix("energies.txt", job_energies);
	create_work_plan(schedule, job_energies);

	for(j=0 ; j<NUM_DAYS ; ++j)
	{
		for(i=0 ; i<NUM_EMPLOYEES ; ++i)
			printf("%d ", schedule[i][j]);
		printf("\n");
	}
	for(j=0 ; j<NUM_DAYS ; ++j)
	{
		for(i=0 ; i<NUM_EMPLOYEES ; ++i)
			printf("%d ", job_energies[i][j]);
		printf("\n");
	}
}
void
read_matrix(const char* file_name, int m[NUM_EMPLOYEES][NUM_DAYS])
{
	int i, j;
	FILE *infile;
	infile = fopen(file_name, "r");

	for(j=0 ; j<NUM_DAYS ; ++j)
		for(i=0 ; i<NUM_EMPLOYEES ; ++i)
			fscanf(infile, "%d", &m[i][j]);

	

}
void
create_work_plan(int job_schedule[NUM_EMPLOYEES][NUM_DAYS], int m[NUM_EMPLOYEES][NUM_DAYS])
{
	int i=0, j=0, total[NUM_EMPLOYEES], min[NUM_EMPLOYEES], index3[NUM_EMPLOYEES] = {0}, index[NUM_EMPLOYEES]={0}, index2=0, n=0, k=0, l=0, count;
	
	job_schedule[0][0]=m[0][0];
	job_schedule[1][0]=m[1][0];
	job_schedule[2][0]=m[3][0];
	job_schedule[3][0]=m[2][0];
	for(j=1 ; j<NUM_DAYS ; ++j)
	{
		for(n=0 ; n<NUM_EMPLOYEES ; ++n)
		{
			total[n] = 0;
			min[n] = 0;
			index[n] = 0;
			index3[n] = 0;
		}
		for(i=0 ; i<NUM_EMPLOYEES ; ++i)
		{
			for(k=0 ; k<j ; ++k)
			{
				total[i] += job_schedule[i][k];
				printf("a %d\n", job_schedule[i][k]);
			}
			printf("total (%d)\n",total[i]);
			min[i] = m[i][j];
		}
count=0;
		for(k=0 ; k<NUM_EMPLOYEES ; ++k)
		{
			index2 = total[k];
			index[count] = k;
			
			for(l=0 ; l<NUM_EMPLOYEES ; ++l)
			{
				if(index2 < total[l])
				{
					index2 = total[l];
					index[count] = l;
				}
			}
			++count;
		}
printf("i1 %d %d %d %d\n",index[0], index[1], index[2], index[3] );
count=0;
		for(k=0 ; k<NUM_EMPLOYEES ; ++k)
		{
			index2 = min[k];
			index3[count] = k;
			
			for(l=0 ; l<NUM_EMPLOYEES ; ++l)
			{
				if(index2 > min[l])
				{
					index2 = min[l];
					index3[count] = l;
				}
			}
			++count;
		}
printf("i3 %d %d %d %d\n",index3[0], index3[1], index3[2], index3[3] );
		for(k=0 ; k<NUM_EMPLOYEES ; ++k)
		{
			job_schedule[index[k]][j] = min[index3[k]]; 
		}
	}
}
employee find_the_employer_of_the_day(int work_schedule[NUM_EMPLOYEES][NUM_DAYS], day day_name)
{


}
employee find_the_employer_of_the_week(int work_schedule[NUM_EMPLOYEES][NUM_DAYS])
{



}
void report(const char* file_name, int job_scheduling[NUM_EMPLOYEES][NUM_DAYS])
{

}
/*##########################################################*/
/*		End of HW06_Yasin_Tulumen_121044020_part2			*/
/*##########################################################*/






































