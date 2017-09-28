/*##########################################################*/
/*HW10_Yasin_Tulumen_121044020_Test1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on May 24,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include "hw10.1.h"

int
main()
{
	int size = 0 ;
	Appointment_t *x;
	Files_t files;
	files.records_file_n = records_file;
	files.patients_file_n = patients_file;
	files.delete_file_n = delete_file;
	files.readable_records_file_n = readable_records_file;
	files.accepted_appo_file_n = accepted_appo_file;
	files.parameters_file_n = parameters_file;

	x = getRequests(&files, &size);

	write_appointments(x, size, &files);
	return 0;
}

/*##########################################################*/
/*		End of HW10_Yasin_Tulumen_121044020_Test1.c 		*/
/*##########################################################*/