/*##########################################################*/
/*HW09_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 28,2015					*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*bir universitenin yillik personel zamlarini gerceklestiren*/
/*uygulama													*/
/*Inputs:													*/
/*	-.txt dosyasindan kisi bilgilerinin okunmasi			*/
/*Outputs:													*/
/*	-binary dosyaya maaslarin zam almis halleriyle			*/
/*	-kisisel bilgilerin yazilmasi							*/
/*	-ekrana basilmasi										*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20], surname[20], department[20];
	char class1[10], class2[10];
	double salary;
}type_I;
typedef struct
{
	char name[20], surname[20], deg;
	double salary;	
}type_E;
typedef union
{
	type_E employee;
	type_I instructor;

}type_union;
typedef struct 
{
	char x;
	type_union y;
}combine_type;

combine_type
salary_rise(combine_type person_info);
void 
read_write_file(void);

int
main()
{
	read_write_file();
}
void 
read_write_file(void)
{
	int i=0;
	char ch, str[20];
	combine_type person_info;
	FILE *intext, *outbin;

	intext = fopen("persin.txt","r");
	outbin = fopen("persout.bin","w");

	do{
		fscanf(intext, "%s", str);
		if(strcmp(str,"Instructor")==0)
		{
			person_info.x = 'i';
			fscanf(intext, "%s %s %s %s %s %lf", person_info.y.instructor.name,
												person_info.y.instructor.surname,
												person_info.y.instructor.department,
												person_info.y.instructor.class1,
												person_info.y.instructor.class2,
												&person_info.y.instructor.salary);
		}
		else if(strcmp(str,"Employee")==0)
		{
			person_info.x = 'e';
			fscanf(intext, "%s %s %lf %c", person_info.y.employee.name,
											person_info.y.employee.surname,
											&person_info.y.employee.salary,
											&person_info.y.employee.deg);
		}
		person_info = salary_rise(person_info);
		
		fwrite(&person_info, 1, sizeof(person_info), outbin);
		fread(&person_info, 1, sizeof(person_info), outbin);
		if(person_info.x == 'i')
		{
			printf("%s %s %s %s %s %f \n", person_info.y.instructor.name,
												person_info.y.instructor.surname,
												person_info.y.instructor.department,
												person_info.y.instructor.class1,
												person_info.y.instructor.class2,
												person_info.y.instructor.salary);
		}
		else if(person_info.x == 'e')
		{
			printf("%s %s %f %c \n", person_info.y.employee.name,
											person_info.y.employee.surname,
											person_info.y.employee.salary,
											person_info.y.employee.deg);
		}
	}while(EOF != fscanf(intext, "%c", &ch));

}


combine_type
salary_rise(combine_type person_info)
{
	double total;

	if(person_info.x == 'i')
	{
		person_info.y.instructor.salary += (person_info.y.instructor.salary * 10.565) / 100;
	}
	else if(person_info.x == 'e')
	{
		if(person_info.y.employee.deg == 'a')
			person_info.y.employee.salary += (person_info.y.employee.salary * 17.5) / 100;
		else if(person_info.y.employee.deg == 'b')
			person_info.y.employee.salary += (person_info.y.employee.salary * 12) / 100;
		else if(person_info.y.employee.deg == 'c')
			person_info.y.employee.salary += (person_info.y.employee.salary * 9) / 100;
	}
	return person_info;
}
/*##########################################################*/
/*		End of HW09_Yasin_Tulumen_121044020_part1			*/
/*##########################################################*/