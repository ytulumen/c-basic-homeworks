/*##########################################################*/
/*HW08_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 20,2015					*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*bir doktorun randevularinin ayarlanmasi programi			*/
/*Inputs:													*/
/*	-dosyadan randevu tarihleri ve kimlik bilgileri			*/
/*Outputs:													*/
/*	-elde edilen verilere gore aynı tarihte olmayan ve 		*/
/*	-sirali randevularin dosyaya yazdirilmasi				*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>
#include <string.h>

typedef enum 
{
	MALE, FEMALE
}Gender_t;

typedef enum 
{
	FREE, JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
	JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
}Months_t;

typedef struct 
{
	int first_half, second_half;
}TCId_no_t;

typedef struct 
{
	TCId_no_t id_no;
	char name[30], surname[30];
	Gender_t gender;
}People_t;

typedef struct 
{
	int hour, minute;
}Time_t;

typedef struct 
{
	int year, day;
	Months_t month;
	Time_t time;
}Date_t;

typedef struct 
{
	People_t people;
	Date_t date;
}Appointment_t;

int
get_people(const char *file_name, People_t people[], int max_size);
int
get_appointments(const char *file_name, Appointment_t appointments[], int max_size);
void
write_names(Appointment_t appointments[], int size_app, const People_t people[], int size_people);
int
check_appointments(Appointment_t appointments[], int size);
void
sort_appointments(Appointment_t appointments[], int size);
void
write_appointments(const char *file_name, Appointment_t appointments[], int size);

int
main()
{
	Appointment_t appointments[10];
	People_t people[10];
	int max_size=0, getap;

	max_size = get_people("People.txt", people, max_size);
	getap = get_appointments("AppointmentReqs.txt", appointments, max_size);
	write_names(appointments, getap, people, max_size);
	getap = check_appointments(appointments, getap);
	sort_appointments(appointments, getap);
	write_appointments("Appointments.txt", appointments, getap);
}
/*dosyadan kisi verilerinin elde edilmesi*/
int
get_people(const char *file_name, People_t people[], int max_size)
{
	char ch;
	int i;
	FILE *infile;
	infile = fopen(file_name, "r");
	do
	{

		fscanf(infile,"%6d%5d", &people[max_size].id_no.first_half, 
				&people[max_size].id_no.second_half);
		fscanf(infile,"%s %s", people[max_size].name, people[max_size].surname);
		fscanf(infile," %c", &ch);

		if(ch=='M')
			people[max_size].gender = 0;
		else
			people[max_size].gender = 1;
		
		++max_size;
	}while(EOF != fscanf(infile, "%c", &ch));
	fclose(infile);

	return max_size;
}
/*randevu taleplerinin elde edilmesi*/
int
get_appointments(const char *file_name, Appointment_t appointments[], int max_size)
{
	int i;
	char ch;
	FILE *infile;
	infile = fopen(file_name, "r");

	for(i=0 ; i<max_size ; ++i)
		fscanf(infile,"%6d%5d %d %d %d %d%c%d", &appointments[i].people.id_no.first_half, 
			&appointments[i].people.id_no.second_half, &appointments[i].date.year, 
			&appointments[i].date.month, &appointments[i].date.day,
			&appointments[i].date.time.hour, 
			&ch, &appointments[i].date.time.minute);
	fclose(infile);
	return i;
}
/*kimlik bilgilerine gore randevu taleplerinin isim soyisim ve cinsiyet ile eslestirilmesi*/
void
write_names(Appointment_t appointments[], int size_app, const People_t people[], int size_people)
{
	int i, j;

	for(i=0 ; i<size_people ; ++i)
	{
		for(j=0 ; j<size_app ; ++j)
		{
			if((appointments[j].people.id_no.first_half == people[i].id_no.first_half) && 
				(appointments[j].people.id_no.second_half == people[i].id_no.second_half))
			{
				strcpy(appointments[j].people.name, people[i].name);
				strcpy(appointments[j].people.surname, people[i].surname);
				appointments[j].people.gender = people[i].gender;
			}
		}
	}
}
/*eger ayni tarihli randevu var ise sonradan talep edilenin iptal edilmesi*/
int
check_appointments(Appointment_t appointments[], int size)
{
	int i, j;

	for(i=0 ; i<size ; ++i)
	{
		for(j=i+1 ; j<size ; ++j)
		{
			if((appointments[i].date.year == appointments[j].date.year) &&
				(appointments[i].date.day == appointments[j].date.day) &&
				(appointments[i].date.month == appointments[j].date.month) &&
				(appointments[i].date.time.hour == appointments[j].date.time.hour) &&
				(appointments[i].date.time.minute == appointments[j].date.time.minute))
			{
				appointments[j] = appointments[size-1];
				--size;
				--j;
			}
		}
	}
	return size;
}
/*randevularin tarihe gore siralanmasi.yil-ay-gun-saat-dakika seklinde*/
void
sort_appointments(Appointment_t appointments[], int size)
{
	int i, j;
	Appointment_t temp;

	for(i=0 ; i<size ; ++i)
	{
		for(j=i+1 ; j<size ; ++j)
		{
			if(appointments[i].date.year > appointments[j].date.year)
			{
				temp = appointments[i];
				appointments[i] = appointments[j];
				appointments[j] = temp;
			}
		}
	}
	for(i=0 ; i<size ; ++i)
	{
		for(j=i+1 ; j<size ; ++j)
		{
			if(appointments[i].date.month > appointments[j].date.month)
			{
				temp = appointments[i];
				appointments[i] = appointments[j];
				appointments[j] = temp;
			}
		}
	}
	for(i=0 ; i<size ; ++i)
	{
		for(j=i+1 ; j<size ; ++j)
		{
			if(appointments[i].date.day > appointments[j].date.day)
			{
				temp = appointments[i];
				appointments[i] = appointments[j];
				appointments[j] = temp;
			}
		}
	}
	for(i=0 ; i<size ; ++i)
	{
		for(j=i+1 ; j<size ; ++j)
		{
			if(appointments[i].date.time.hour > appointments[j].date.time.hour)
			{
				temp = appointments[i];
				appointments[i] = appointments[j];
				appointments[j] = temp;
			}
		}
	}
	for(i=0 ; i<size ; ++i)
	{
		for(j=i+1 ; j<size ; ++j)
		{
			if(appointments[i].date.time.minute > appointments[j].date.time.minute)
			{
				temp = appointments[i];
				appointments[i] = appointments[j];
				appointments[j] = temp;
			}
		}
	}
}
/*son halin dosyaya yazdirilmasi*/
void
write_appointments(const char *file_name, Appointment_t appointments[], int size)
{
	int i;
	FILE *outfile;
	outfile = fopen(file_name, "w");

	for(i=0 ; i<size ; ++i)
	{
		fprintf(outfile, "%d %d %d %d:%d %d%d %s %s",
		appointments[i].date.year, appointments[i].date.month, appointments[i].date.day,
		appointments[i].date.time.hour, appointments[i].date.time.minute,
		appointments[i].people.id_no.first_half, appointments[i].people.id_no.second_half,
		appointments[i].people.name, appointments[i].people.surname );

		if(appointments[i].people.gender == 0)
			fprintf(outfile, " M\n");
		else
			fprintf(outfile, " F\n");
	}
	fclose(outfile);
}
/*##########################################################*/
/*		End of HW08_Yasin_Tulumen_121044020_part2			*/
/*##########################################################*/