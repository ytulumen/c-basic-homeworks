#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int app_id;
	int patient_id;
	int hour;
}Appointment_t;

void a();

int main()
{
	Appointment_t app[5];
	FILE *binf;
	int i, j=5, k = 13, l=12;
	binf=fopen("Records.bin","wb");
	
	for(i=0 ; i<5 ; ++i)
	{
		app[i].app_id=i+j;
		app[i].patient_id=i+k;
		app[i].hour=i+l;
		fwrite(&app[i], 1, sizeof(Appointment_t), binf);
	}
	fclose(binf);
	return 0;
}
/*void a()
{
	
	Appointment_t *x;
	int status=0, i=0, j=0, size=5;
	FILE *abin, *xml;
	xml=fopen("Patients.xml", "w");
	abin=fopen("Records.bin","rb");
	x = (Appointment_t*) calloc(size, sizeof(Appointment_t));

	for(status = fread(&x[i],1, sizeof(Appointment_t), abin);
		status != 0 ;
		status = fread(&x[i], 1, sizeof(Appointment_t), abin))
		++i;

	fprintf(xml, "<Size>%d</Size>\n", size);
	fprintf(xml, "<Records>\n");
	for(j=0 ; j<i; ++j)
	{
		fprintf(xml, "\t<Appointment>\n");
		fprintf(xml, "\t\t<app_id>%d</app_id>\n", x[j].app_id);
		fprintf(xml, "\t\t<patient_id>%d</patient_id>\n", x[j].patient_id);
		fprintf(xml, "\t\t<hour>%d</hour>\n", x[j].hour);
		fprintf(xml, "\t</Appointment>\n");
	}
	fprintf(xml, "</Records>\n");
}*/