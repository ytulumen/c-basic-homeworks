/*##########################################################*/
/*HW10_Yasin_Tulumen_121044020_Part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on May 24,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/
#include "hw10.1.h"

extern const char *records_file = "Records.bin";
extern const char *parameters_file = "Parameters.txt";
extern const char *delete_file = "Delete.txt";
extern const char *patients_file = "Patients.xml";
extern const char *readable_records_file = "Records.xml";
extern const char *accepted_appo_file = "appointments.csv";


Appointment_t *getRequests(const Files_t *files, int *size)
{
	FILE *inp ;
	Appointment_t *x ;
	int status = 0 ;
	inp = fopen(files->records_file_n,"rb") ;
	x = (Appointment_t*) calloc(MAX, sizeof(Appointment_t));

	for(status = fread(&x[*size],1, sizeof(Appointment_t), inp);
		status != 0 ;
		status = fread(&x[*size],1, sizeof(Appointment_t), inp))
		++(*size);

	return x;
}
void write_appointments(Appointment_t appointments[], int size, const Files_t* files)
{
	int i;
	FILE *outf;
	outf = fopen(files->patients_file_n,"w");

	fprintf(outf, "<Size>%d</Size>\n", size);
	fprintf(outf, "<Records>\n");
	for(i=0 ; i<size; ++i)
	{
		fprintf(outf, "\t<Appointment>\n");
		fprintf(outf, "\t\t<app_id>%d</app_id>\n", appointments[i].app_id);
		fprintf(outf, "\t\t<patient_id>%d</patient_id>\n", appointments[i].patient_id);
		fprintf(outf, "\t\t<hour>%d</hour>\n", appointments[i].hour);
		fprintf(outf, "\t</Appointment>\n");
	}
	fprintf(outf, "</Records>\n");	

}
void get_main_arguments(int argc, char* argv[], Working_hours_t* hours, Files_t* files)
{

}
void print_parameters(const Files_t* files, const Working_hours_t* hours)
{

}
/*##########################################################*/
/*		HW10_Yasin_Tulumen_121044020_Part1.c        		*/
/*##########################################################*/