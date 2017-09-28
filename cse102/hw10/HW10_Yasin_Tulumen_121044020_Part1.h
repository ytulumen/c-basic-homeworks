/*##########################################################*/
/*HW10_Yasin_Tulumen_121044020_Part1.h              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on May 24,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

extern const char *records_file;
extern const char *parameters_file;
extern const char *delete_file;
extern const char *patients_file;
extern const char *readable_records_file;
extern const char *accepted_appo_file;

typedef struct 
{
	int app_id;
	int patient_id;
	int hour;
} Appointment_t ;
typedef struct 
{
	int start;
	int end;
} Working_hours_t ;
typedef struct 
{
	const char *records_file_n;
	const char *patients_file_n;
	const char *delete_file_n;
	const char *readable_records_file_n;
	const char *accepted_appo_file_n;
	const char *parameters_file_n;
}Files_t;
typedef struct 
{
	int app_id, patient_id, hour;
	char name[50];
	char* history;
/*	node_t* next; */
}node_t;


Appointment_t* getRequests(const Files_t* files, int* size);
void write_appointments(Appointment_t appointments[], int size, const Files_t* files);
void get_main_arguments(int argc, char* argv[], Working_hours_t* hours, Files_t* files);
void print_parameters(const Files_t* files, const Working_hours_t* hours);

/*##########################################################*/
/*		End of HW10_Yasin_Tulumen_121044020_Part1.h 		*/
/*##########################################################*/
